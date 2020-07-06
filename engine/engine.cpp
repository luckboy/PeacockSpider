/*
 * Peacock Spider - Chess engine.
 * Copyright (C) 2020 Łukasz Szpakowski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <limits>
#include "engine.hpp"

using namespace std;

namespace peacockspider
{
  Engine::Engine(Thinker *thinker) :
    _M_thinker(thinker),
    _M_thread_command(ThreadCommand::NO_COMMAND),
    _M_mode(Mode::GAME),
    _M_previous_mode(Mode::GAME),
    _M_thinking_output_function([](int depth, int value, unsigned ms, const Searcher *searcher, const Board *board, const Move *move) {}),
    _M_move_output_function([](const Board &board, Move move, const Move *pondering_move) {}),
    _M_result_output_function([](Result result, const string &comment) {}),
    _M_board_output_function([](const Board &board) {}),
    _M_result(Result::NONE),
    _M_has_search_moves(false),
    _M_move_pairs(new MovePair[MAX_MOVE_COUNT]),
    _M_has_remaining_engine_time(false),
    _M_has_remaining_opponent_time(false),
    _M_depth(MAX_DEPTH),
    _M_time(numeric_limits<unsigned>::max()),
    _M_nodes(numeric_limits<uint64_t>::max()),
    _M_checkmate_move_count(0),
    _M_pondering_move_flag(false),
    _M_thinking_output_flag(false),
    _M_auto_pondering_flag(false),
    _M_auto_move_making_flag(true),
    _M_last_board(Board())
  {
    _M_boards.reserve(256);
    _M_boards.push_back(Board());
    _M_time_control.type = TimeControlType::NONE;
    _M_time_control.mps = 0;
    _M_time_control.base = 0;
    _M_time_control.inc = 0;
    _M_thread = thread([this]() {
      unique_lock<mutex> lock(_M_mutex);
      while(_M_thread_command != ThreadCommand::QUIT) {
        switch(_M_thread_command) {
          case ThreadCommand::THINK:
          {
            Move best_move;
            think(best_move);
            bool auto_pondering_flag = false;
            bool auto_move_making_flag = true;
            {
              unique_lock<mutex> other_mutex(_M_other_mutex);
              auto_pondering_flag = _M_auto_pondering_flag;
              auto_move_making_flag = _M_auto_move_making_flag;
            }
            if(auto_move_making_flag && _M_mode != Mode::ANALYSIS && best_move.to() != -1) {
              Board new_board;
              if(_M_boards.back().make_move(best_move, new_board)) {
                _M_boards.push_back(new_board);
                set_last_board(new_board);
                _M_board_output_function(_M_boards.back());
                unsafely_set_result_for_boards();
                if(_M_result != Result::NONE) _M_result_output_function(_M_result, _M_result_comment);
                if(auto_pondering_flag) ponder();
              }
            }
            break;
          }
          case ThreadCommand::PONDER:
            ponder();
            break;
          default:
            break;
        }
        _M_thread_command = ThreadCommand::NO_COMMAND;
        _M_condition_variable.wait(lock);
      }
    });
  }
    
  Engine::~Engine()
  {
    _M_thinker->stop_thinking();
    _M_thinker->stop_pondering();
    {
      unique_lock<mutex> lock(_M_mutex);
      _M_thread_command = ThreadCommand::QUIT;
      _M_condition_variable.notify_one();
    }
    _M_thread.join();
  }

  function<void (int, int, unsigned, const Searcher *, const Board *, const Move *)> Engine::thinking_output_function()
  {
    unique_lock<mutex> lock(_M_mutex);
    return _M_thinking_output_function;
  }
  
  void Engine::set_thinking_output_function(function<void (int, int, unsigned, const Searcher *, const Board *, const Move *)> fun)
  {
    unique_lock<mutex> lock(_M_mutex);
    _M_thinking_output_function = fun;
  }

  function<void (const Board &, Move, const Move *)> Engine::move_output_function()
  {
    unique_lock<mutex> lock(_M_mutex);
    return _M_move_output_function;
  }

  void Engine::set_move_output_function(function<void (const Board &, Move, const Move *)> fun)
  {
    unique_lock<mutex> lock(_M_mutex);
    _M_move_output_function = fun;
  }
  
  function<void (Result, const string &)> Engine::result_output_function()
  {
    unique_lock<mutex> lock(_M_mutex);
    return _M_result_output_function;
  }

  void Engine::set_result_output_function(function<void (Result, const string &)> fun)
  {
    unique_lock<mutex> lock(_M_mutex);
    _M_result_output_function = fun;
  }
  
  function<void (const Board &)> Engine::board_output_function()
  {
    unique_lock<mutex> lock(_M_mutex);
    return _M_board_output_function;
  }

  void Engine::set_board_output_function(function<void (const Board &)> fun)
  {
    unique_lock<mutex> lock(_M_mutex);
    _M_board_output_function = fun;
  }
  
  void Engine::new_game()
  {
    _M_thinker->stop_pondering();
    unique_lock<mutex> lock(_M_mutex);
    _M_mode = Mode::GAME;
    unsafely_pre_set_board();
    _M_boards.clear();
    _M_boards.push_back(Board());
    set_last_board(Board());
    _M_board_output_function(_M_boards.back());
    _M_result = Result::NONE;
    _M_result_comment = "";
  }

  void Engine::set_level(unsigned mps, unsigned base, unsigned inc)
  {
    unique_lock<mutex> lock(_M_limit_mutex);
    _M_time_control.type = (mps != 0 ? TimeControlType::CLASSICAL : TimeControlType::INCREMENTAL);
    _M_time_control.mps = mps;
    _M_time_control.base = base;
    _M_time_control.inc = inc;
  }

  void Engine::set_time(unsigned time)
  {
    unique_lock<mutex> lock(_M_limit_mutex);
    _M_time_control.type = TimeControlType::FIXED_MAX;
    _M_time_control.mps = 0;
    _M_time_control.base = 0;
    _M_time_control.time = time;
  }
  
  void Engine::set_depth(int depth)
  {
    unique_lock<mutex> lock(_M_limit_mutex);
    _M_depth = depth;
  }

  void Engine::set_remaining_engine_time(unsigned time)
  {
    unique_lock<mutex> lock(_M_limit_mutex);
    _M_has_remaining_engine_time = true;
    _M_remaining_engine_time = time;
  }

  void Engine::set_remaining_opponent_time(unsigned time)
  {
    unique_lock<mutex> lock(_M_limit_mutex);
    _M_has_remaining_opponent_time = true;
    _M_remaining_opponent_time = time;
  }

  void Engine::unset_remaining_engine_time()
  {
    unique_lock<mutex> lock(_M_limit_mutex);
    _M_has_remaining_engine_time = false;
  }

  void Engine::unset_remaining_opponent_time()
  {
    unique_lock<mutex> lock(_M_limit_mutex);
    _M_has_remaining_opponent_time = false;
  }

  bool Engine::make_move(function<bool (const Board &, Move &)> fun, bool must_stop_thinking)
  {
    if(must_stop_thinking) _M_thinker->stop_thinking();
    _M_thinker->stop_pondering();
    unique_lock<mutex> lock(_M_mutex);
    Move move;
    if(_M_result != Result::NONE) return false;
    if(!fun(_M_boards.back(), move)) return false;
    Board new_board;
    if(!_M_boards.back().make_move(move, new_board)) return false;
    _M_boards.push_back(new_board);
    set_last_board(new_board);
    _M_board_output_function(_M_boards.back());
    unsafely_set_result_for_boards();
    if(_M_result == Result::NONE) {
      if(must_stop_thinking && _M_mode == Mode::ANALYSIS) {
        _M_thinker->discard_hint_move();
        unsafely_go(false, false);
      } else if(_M_mode != Mode::FORCE) {
        bool is_hint_move = false;
        Move hint_move;
        {
          unique_lock<mutex> hint_move_lock(_M_hint_move_mutex);
          is_hint_move = _M_thinker->has_hint_move();
          hint_move = _M_thinker->hint_move();
        }
        if(is_hint_move ? move != hint_move : true) _M_thinker->discard_hint_move();
        unsafely_go(false, true);
      }
    } else
      _M_result_output_function(_M_result, _M_result_comment);
    return true;
  }
  
  bool Engine::undo(bool must_stop_thinking)
  {
    if(must_stop_thinking) _M_thinker->stop_thinking();
    _M_thinker->stop_pondering();
    unique_lock<mutex> lock(_M_mutex);
    if(_M_boards.size() >= 2) {
      unsafely_pre_set_board();
      _M_boards.pop_back();
      set_last_board(_M_boards.back());
      if(must_stop_thinking && _M_mode == Mode::ANALYSIS) unsafely_go(false, false);
      return true;
    } else
      return false;
  }

  bool Engine::remove()
  {
    _M_thinker->stop_pondering();
    unique_lock<mutex> lock(_M_mutex);
    if(_M_boards.size() >= 3) {
      unsafely_pre_set_board();
      _M_boards.pop_back();
      _M_boards.pop_back();
      set_last_board(_M_boards.back());
      return true;
    } else
      return false;
  }

  bool Engine::set_board(function<bool (const Board &, Board &)> fun, bool must_stop_thinking)
  {
    if(must_stop_thinking) _M_thinker->stop_thinking();
    _M_thinker->stop_pondering();
    unique_lock<mutex> lock(_M_mutex);
    unsafely_pre_set_board();
    Board new_board;
    if(!fun(_M_boards.back(), new_board)) return false;
    _M_boards.clear();
    _M_boards.push_back(new_board);
    set_last_board(new_board);
    _M_board_output_function(_M_boards.back());
    unsafely_set_result_for_boards();
    if(_M_result == Result::NONE) {
      if(must_stop_thinking && _M_mode == Mode::ANALYSIS) unsafely_go(false, false);
    }
    return true;
  }

  void Engine::set_force_mode()
  {
    _M_thinker->stop_thinking();
    _M_thinker->stop_pondering();
    unique_lock<mutex> lock(_M_mutex);
    _M_mode = Mode::FORCE;
  }

  void Engine::analyze()
  {
    _M_thinker->stop_pondering();
    unique_lock<mutex> lock(_M_mutex);
    _M_previous_mode = _M_mode;
    _M_mode = Mode::ANALYSIS;
    if(_M_result != Result::NONE) return;
    _M_thinker->discard_hint_move();
    unsafely_go(false, false);
  }

  void Engine::quit_from_analysis()
  {
    _M_thinker->stop_thinking();
    unique_lock<mutex> lock(_M_mutex);
    _M_mode = _M_previous_mode;
  }

  void Engine::play_other()
  {
    bool auto_pondering_flag = false;
    _M_thinker->stop_pondering();
    {
      unique_lock<mutex> other_lock(_M_other_mutex);
      auto_pondering_flag = _M_auto_pondering_flag;
    }
    unique_lock<mutex> lock(_M_mutex);
    _M_mode = Mode::GAME;
    if(auto_pondering_flag) unsafely_go(true, false);
  }

  void Engine::go()
  {
    _M_thinker->stop_pondering();
    unique_lock<mutex> lock(_M_mutex);
    _M_mode = Mode::GAME;
    if(_M_result != Result::NONE) return;
    _M_thinker->discard_hint_move();
    unsafely_go(false, true);
  }

  void Engine::stop_thinking()
  { _M_thinker->stop_thinking(); }
  
  void Engine::stop_pondering()
  { _M_thinker->stop_pondering(); }

  pair<Move, bool> Engine::hint_move_pair()
  {
    unique_lock<mutex> lock(_M_hint_move_mutex);
    if(_M_thinker->has_hint_move())
      return make_pair(_M_thinker->hint_move(), true);
    else
      return make_pair(Move(), false);
  }

  bool Engine::get_hint_move(Move &move)
  {
    unique_lock<mutex> lock(_M_hint_move_mutex);
    if(_M_thinker->has_hint_move()) return false;
    move = _M_thinker->hint_move();
    return true;
  }

  void Engine::set_result(Result result, const string &comment)
  {
    unique_lock<mutex> lock(_M_mutex);
    _M_result = result;
    _M_result_comment = comment;
  }

  void Engine::set_thinking_output_flag(bool flag)
  {
    unique_lock<mutex> lock(_M_other_mutex);
    _M_thinking_output_flag = flag;
  }

  void Engine::set_auto_pondering_flag(bool flag)
  {
    unique_lock<mutex> lock(_M_other_mutex);
    _M_auto_pondering_flag = flag;
  }

  void Engine::set_auto_move_making_flag(bool flag)
  {
    unique_lock<mutex> lock(_M_other_mutex);
    _M_auto_move_making_flag = flag;
  }

  bool Engine::set_board_and_make_moves(function<bool (const Board &, Board &, vector<Move> &)> fun)
  {
    vector<Move> moves;
    _M_thinker->stop_pondering();
    unique_lock<mutex> lock(_M_mutex);
    unsafely_pre_set_board();
    Board new_board;
    if(!fun(_M_boards.back(), new_board, moves)) return false;
    _M_boards.clear();
    _M_boards.push_back(new_board);
    set_last_board(new_board);
    unsafely_set_result_for_boards();
    for(Move move : moves) {
      if(_M_result != Result::NONE) {
        _M_board_output_function(_M_boards.back());
        return false;
      }
      if(!_M_boards.back().make_move(move, new_board)) {
        _M_board_output_function(_M_boards.back());
        return false;
      }
      _M_boards.push_back(new_board);
      set_last_board(new_board);
      unsafely_set_result_for_boards();
    }
    _M_board_output_function(_M_boards.back());
    return true;
  }
  
  void Engine::go(const vector<Move> *search_moves, unsigned white_time, unsigned black_time, unsigned moves_to_go, int depth, uint64_t nodes, int checkmate_move_count, unsigned move_time, bool is_pondering)
  {
    unique_lock<mutex> lock(_M_mutex);
    if(_M_result != Result::NONE) return;
    _M_thinker->discard_hint_move();
    {
      unique_lock<mutex> limit_lock(_M_limit_mutex);
      if(move_time == numeric_limits<unsigned>::max()) {
        if(_M_boards.back().side() == Side::WHITE) {
          if(white_time != numeric_limits<unsigned>::max()) {
            _M_has_remaining_engine_time = true;
            _M_remaining_engine_time = white_time;
          } else
            _M_has_remaining_engine_time = false;
          if(black_time != numeric_limits<unsigned>::max()) {
            _M_has_remaining_opponent_time = true;
            _M_remaining_opponent_time = black_time;
          } else
            _M_has_remaining_opponent_time = false;
        } else {
          if(white_time != numeric_limits<unsigned>::max()) {
            _M_has_remaining_opponent_time = true;
            _M_remaining_opponent_time = white_time;
          } else
            _M_has_remaining_engine_time = false;
          if(black_time != numeric_limits<unsigned>::max()) {
            _M_has_remaining_engine_time = true;
            _M_remaining_engine_time = black_time;
          } else
            _M_has_remaining_engine_time = false;
        }
        _M_time = unsafely_calculate_time(moves_to_go);
      } else
        _M_time = move_time;
      _M_depth = depth;
      _M_nodes = nodes;
      _M_checkmate_move_count = checkmate_move_count;
      _M_pondering_move_flag = false;
    }
    _M_thread_command = (is_pondering ? ThreadCommand::PONDER : ThreadCommand::THINK);
    if(search_moves != nullptr) {
      _M_has_search_moves = true;
      _M_search_moves = *search_moves;
    } else {
      _M_has_search_moves = false;
      _M_search_moves.clear();
    }
    _M_thinker->clear_stop_flags();
    _M_condition_variable.notify_one();
  }

  void Engine::pondering_hit()
  {
    _M_thinker->stop_pondering();
    unique_lock<mutex> lock(_M_mutex);
    _M_thread_command = ThreadCommand::THINK;
    _M_thinker->clear_stop_flags();
    _M_condition_variable.notify_one();
  }

  void Engine::get_board(Board &board)
  {
    unique_lock<mutex> lock(_M_last_board_mutex);
    board = _M_last_board;
  }

  void Engine::unsafely_go(bool is_pondering, bool is_time_calculation)
  {
    {
      unique_lock<mutex> limit_lock(_M_limit_mutex);
      if(is_time_calculation)
        _M_time = unsafely_calculate_time(numeric_limits<unsigned>::max());
      else
        _M_time = numeric_limits<unsigned>::max();
      _M_nodes = numeric_limits<uint64_t>::max();
      _M_checkmate_move_count = 0;
      _M_pondering_move_flag = true;
    }
    _M_thread_command = (is_pondering ? ThreadCommand::PONDER : ThreadCommand::THINK);
    _M_has_search_moves = false;
    _M_search_moves.clear();
    _M_thinker->clear_stop_flags();
    _M_condition_variable.notify_one();
  }
  
  void Engine::unsafely_set_result_for_boards()
  {
    MovePairList move_pairs(_M_move_pairs.get(), 0);
    if(_M_boards.back().in_checkmate(move_pairs)) {
      if(_M_boards.back().side() == Side::WHITE) {
        _M_result = Result::BLACK_WIN;
        _M_result_comment = "Black mates";
      } else {
        _M_result = Result::WHITE_WIN;
        _M_result_comment = "White mates";
      }
    } else if(_M_boards.back().in_stalemate(move_pairs)) {
      _M_result = Result::DRAW;
      _M_result_comment = "Stalemate";
    } else if(_M_boards.back().halfmove_clock() >= 100) {
      _M_result = Result::DRAW;
      _M_result_comment = "Draw by 50 move rule";  
    } else if(repetitions(_M_boards.back(), _M_boards) >= 3) {
      _M_result = Result::DRAW;
      _M_result_comment = "Draw by repetition";
    } else {
      _M_result = Result::NONE;
      _M_result_comment = "";
    }
  }
  
  unsigned Engine::unsafely_calculate_time(unsigned moves_to_go)
  {
    unsigned time;
    if(_M_time_control.type == TimeControlType::CLASSICAL || 
      (_M_time_control.type == TimeControlType::NONE && moves_to_go != numeric_limits<unsigned>::max())) {
      if(moves_to_go == numeric_limits<unsigned>::max()) {
        if(_M_has_remaining_engine_time) {
          moves_to_go = (_M_boards.size() - 1) % _M_time_control.mps;
          if(moves_to_go == 0) moves_to_go = _M_time_control.mps;
        } else
          moves_to_go = _M_time_control.mps;
      }
      unsigned remaining_time = (_M_has_remaining_engine_time ? _M_remaining_engine_time : (_M_time_control.type != TimeControlType::NONE ? _M_time_control.base : 5 * 60 * 1000));
      time = remaining_time / moves_to_go;
    } else if(_M_time_control.type == TimeControlType::FIXED_MAX) {
      time = _M_time_control.time;
    } else {
      unsigned remaining_time = (_M_has_remaining_engine_time ? _M_remaining_engine_time : (_M_time_control.type != TimeControlType::NONE ? _M_time_control.base : 5 * 60 * 1000));
      time = remaining_time / 30;
    }
    return time;
  }
  
  void Engine::unsafely_pre_set_board()
  {
    _M_thinker->discard_hint_move();
    {
      unique_lock<mutex> lock(_M_hint_move_mutex);
      _M_thinker->unset_hint_move();
    }
    _M_thinker->unset_next_hint_move();
  }

  void Engine::set_last_board(const Board &board)
  {
    unique_lock<mutex> lock(_M_last_board_mutex);
    _M_last_board = board;
  }
  
  void Engine::think(Move &best_move)
  {
    vector<Move> *search_moves = (_M_has_search_moves ? &_M_search_moves : nullptr);
    int depth = MAX_DEPTH;
    unsigned time = numeric_limits<unsigned>::max();
    uint64_t nodes = numeric_limits<uint64_t>::max();
    int checkmate_move_count = 0;
    {
      unique_lock<mutex> limit_lock(_M_limit_mutex);
      depth = _M_depth;
      time = _M_time;
      nodes = _M_nodes;
      checkmate_move_count = _M_checkmate_move_count;
    }
    {
      unique_lock<mutex> hint_move_lock(_M_hint_move_mutex);
      _M_thinker->think(depth, time, search_moves, nodes, checkmate_move_count, best_move, _M_boards, [this](int depth, int value, unsigned ms, const Searcher *searcher) {
        bool thinking_output_flag = false;
        {
          unique_lock<mutex> other_lock(_M_other_mutex);
          thinking_output_flag = _M_thinking_output_flag;
        }
        if(thinking_output_flag) _M_thinking_output_function(depth, value, ms, searcher, nullptr, nullptr);
      });
    }
    if(_M_mode != Mode::ANALYSIS && best_move.to() != -1) {
      Move pondering_move = _M_thinker->hint_move();
      _M_move_output_function(_M_boards.back(), best_move, _M_thinker->has_hint_move() ? &pondering_move : nullptr);
    }
  }

  void Engine::ponder()
  {
    if(_M_result != Result::NONE) return;
    vector<Move> *search_moves = (_M_has_search_moves ? &_M_search_moves : nullptr);
    int depth = MAX_DEPTH;
    uint64_t nodes = numeric_limits<uint64_t>::max();
    int checkmate_move_count = 0;
    bool pondering_move_flag = false;
    {
      unique_lock<mutex> limit_lock(_M_limit_mutex);
      depth = _M_depth;
      nodes = _M_nodes;
      checkmate_move_count = _M_checkmate_move_count;
      pondering_move_flag = _M_pondering_move_flag;
    }
    if(pondering_move_flag) {
      unique_lock<mutex> hint_move_lock(_M_hint_move_mutex);
      if(!_M_thinker->has_hint_move()) return;
      _M_thinker->set_pondering_move();
    }
    _M_thinker->ponder(depth, search_moves, nodes, checkmate_move_count, _M_boards, [this, pondering_move_flag](int depth, int value, unsigned ms, const Searcher *searcher) {
      bool thinking_output_flag = false;
      {
        unique_lock<mutex> other_lock(_M_other_mutex);
        thinking_output_flag = _M_thinking_output_flag;
      }
      if(thinking_output_flag) {
        Move tmp_pondering_move = (pondering_move_flag ? _M_thinker->pondering_move() : Move());
        const Board *pondering_board = (pondering_move_flag ? &(_M_boards.back()) : nullptr); 
        const Move *pondering_move = (pondering_move_flag ? &tmp_pondering_move : nullptr); 
        _M_thinking_output_function(depth, value, ms, searcher, pondering_board, pondering_move);
      }
    }, pondering_move_flag);
  }
}
