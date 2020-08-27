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
#include "search.hpp"

using namespace std;

namespace peacockspider
{
  ABDADASearcherBase::ABDADASearcherBase(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, function<Searcher *(const EvaluationFunction *, TranspositionTable *, const vector<ABDADAThread> &, int, int)> fun, unsigned thread_count, int max_depth, int max_quiescence_depth) :
    _M_transposition_table(transpos_table)
  {
    for(unsigned i = 0; i < thread_count; i++) {
      _M_threads.push_back(ABDADAThread());
      _M_threads.back().searcher = unique_ptr<Searcher>(fun(eval_fun, transpos_table, _M_threads, max_depth + 1, max_quiescence_depth));
      _M_threads.back().command = ABDADACommand::NO_COMMAND;
      _M_threads.back().result = ABDADAResult::NO_RESULT;
    }
    _M_best_thread = &(_M_threads[0]);
    for(unsigned i = 0; i < thread_count; i++) {
      _M_threads[i].thread = thread([this, i]() {
        unique_lock<mutex> lock(_M_threads[i].mutex);
        while(true) {
          while(_M_threads[i].command == ABDADACommand::NO_COMMAND) {
            _M_threads[i].start_condition_variable.wait(lock);
          }
          if(_M_threads[i].command == ABDADACommand::QUIT) break;
          ABDADAResult result = ABDADAResult::NO_RESULT;
          int value = 0;
          Move best_move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
          if(_M_threads[i].command == ABDADACommand::SEARCH) {
            try {
              value = _M_threads[i].searcher->search_from_root(_M_alpha, _M_beta, _M_depth, _M_search_moves, best_move, *_M_boards, _M_last_board);
              result = ABDADAResult::VALUE;
            } catch(ThinkingStopException &e) {
              result = ABDADAResult::THINKING_STOP;
            } catch(PonderingStopException &e) {
              result = ABDADAResult::PONDERING_STOP;
            }
          }
          _M_threads[i].command = ABDADACommand::NO_COMMAND;
          _M_threads[i].result = result;
          _M_threads[i].value = value;
          _M_threads[i].best_move = best_move;
          _M_threads[i].stop_condition_variable.notify_one();
        }
      });
    }
  }
  
  ABDADASearcherBase::~ABDADASearcherBase()
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->stop_thinking();
      thread.searcher->stop_pondering();
    }
    for(ABDADAThread &thread : _M_threads) {
      unique_lock<mutex> lock(thread.mutex);
      thread.command = ABDADACommand::QUIT;
      thread.start_condition_variable.notify_one();
    }
    for(ABDADAThread &thread : _M_threads) {
      thread.thread.join();
    }
  }

  const Board &ABDADASearcherBase::board() const
  { return _M_threads[0].searcher->board(); }

  void ABDADASearcherBase::set_board(const Board &board)
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->set_board(board);
    }
  }

  void ABDADASearcherBase::set_stop_time(const chrono::high_resolution_clock::time_point &time)
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->set_stop_time(time);
    }
  }

  void ABDADASearcherBase::unset_stop_time()
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->unset_stop_time();
    }
  }

  void ABDADASearcherBase::set_stop_nodes(uint64_t nodes)
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->set_stop_nodes(nodes);
    }
  }

  void ABDADASearcherBase::unset_stop_nodes()
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->unset_stop_nodes();
    }
  }

  void ABDADASearcherBase::set_previous_pv_line(const PVLine &pv_line)
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->set_previous_pv_line(pv_line);
    }
  }

  void ABDADASearcherBase::clear()
  {
    _M_transposition_table->increase_age_or_clear();
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->clear();
    }
  }

  void ABDADASearcherBase::clear_for_new_game()
  {
    _M_transposition_table->clear();
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->clear();
    }
  }

  int ABDADASearcherBase::search_from_root(int alpha, int beta, int depth, const vector<Move> *search_moves, Move &best_move, const vector<Board> &boards, const Board *last_board)
  {
    _M_alpha = alpha;
    _M_beta = beta;
    _M_depth = depth;
    _M_search_moves = search_moves;
    _M_boards = &boards;
    _M_last_board = last_board;
    for(ABDADAThread &thread : _M_threads) {
      unique_lock<mutex> lock(thread.mutex);
      thread.command = ABDADACommand::SEARCH;
      thread.start_condition_variable.notify_one();
    }
    ABDADAResult result = ABDADAResult::NO_RESULT;
    for(ABDADAThread &thread : _M_threads) {
      unique_lock<mutex> lock(thread.mutex);
      while(thread.result == ABDADAResult::NO_RESULT) {
        thread.stop_condition_variable.wait(lock);
      }
      result |= thread.result;
      thread.result = ABDADAResult::NO_RESULT;
    }
    if((result & ABDADAResult::THINKING_STOP) != ABDADAResult::NO_RESULT) {
      throw ThinkingStopException();
    } else if((result & ABDADAResult::PONDERING_STOP) != ABDADAResult::NO_RESULT) {
      throw PonderingStopException();
    }
    _M_best_thread = &(_M_threads[0]);
    for(unsigned i = 1; i < _M_threads.size(); i++) {
      if(_M_best_thread->value == _M_threads[i].value ? _M_best_thread->searcher->pv_line().length() < _M_threads[i].searcher->pv_line().length() : _M_best_thread->value < _M_threads[i].value)
        _M_best_thread = &(_M_threads[i]);
    }
    best_move = _M_best_thread->best_move;
    return _M_best_thread->value;
  }

  void ABDADASearcherBase::set_pondering_flag(bool flag)
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->set_pondering_flag(flag);
    }
  }

  void ABDADASearcherBase::clear_thinking_stop_flag()
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->clear_thinking_stop_flag();
    }
  }

  void ABDADASearcherBase::clear_pondering_stop_flag()
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->clear_pondering_stop_flag();
    }
  }

  void ABDADASearcherBase::clear_searching_stop_flag()
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->clear_searching_stop_flag();
    }
  }

  void ABDADASearcherBase::stop_thinking()
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->stop_thinking();
    }
  }

  void ABDADASearcherBase::stop_pondering()
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->stop_pondering();
    }
  }

  void ABDADASearcherBase::stop_searching()
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->stop_searching();
    }
  }

  void ABDADASearcherBase::set_non_stop_flag(bool flag)
  {
    for(ABDADAThread &thread : _M_threads) {
      thread.searcher->set_non_stop_flag(flag);
    }
  }

  const PVLine &ABDADASearcherBase::pv_line() const
  { return _M_best_thread->searcher->pv_line(); }
    
  uint64_t ABDADASearcherBase::nodes() const
  { return _M_threads[0].searcher->all_nodes(); }

  unsigned ABDADASearcherBase::thread_count() const
  { return _M_threads.size(); }
    
  int ABDADASearcherBase::max_quiescence_depth() const
  { return _M_threads[0].searcher->max_quiescence_depth(); }
}
