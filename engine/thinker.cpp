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
#include <algorithm>
#include <limits>
#include "search.hpp"

using namespace std;

namespace peacockspider
{
  namespace
  {
    const int VALUE_WINDOW = 100;
  }

  Thinker::Thinker(Searcher *searcher) :
    _M_searcher(searcher), _M_move_pairs(new MovePair[MAX_MOVE_COUNT])
  {
    clear();
    unset_hint_move();
    unset_next_hint_move();
  }

  void Thinker::clear()
  {
    _M_searcher->clear_for_new_game();
    _M_searcher->clear_thinking_stop_flag();
    _M_searcher->clear_pondering_stop_flag();
    _M_searcher->clear_searching_stop_flag();
    _M_must_continue = false;
    _M_has_best_move = false;
    _M_has_pondering = false;
    _M_has_pondering_move = false;
  }

  bool Thinker::think(int max_depth, unsigned ms, const vector<Move> *search_moves, uint64_t nodes, int checkmate_move_count, Move &best_move, const vector<Board> &boards, const Board *last_board, function<void (int, int, unsigned, const Searcher *)> fun)
  {
    if(!_M_must_continue) {
      _M_searcher->clear();
      if(last_board != nullptr) {
        _M_searcher->set_board(*last_board);
      } else {
        if(!boards.empty())
          _M_searcher->set_board(boards.back());
        else
          return false;
      }
      _M_depth = 1;
      _M_alpha = MIN_VALUE;
      _M_beta = MAX_VALUE;
      _M_value = 0;
      _M_has_second_search = false;
    } else {
      if(_M_has_best_move)
        best_move = _M_best_move;
      else
        return false;
      _M_has_hint_move = _M_has_next_hint_move;
      _M_hint_move = _M_next_hint_move;
    }
    _M_searcher->set_pondering_flag(_M_has_pondering);
    if(ms != numeric_limits<unsigned>::max())
      _M_searcher->set_time(ms);
    else
      _M_searcher->unset_stop_time();
    if(nodes != numeric_limits<int64_t>::max())
      _M_searcher->set_stop_nodes(nodes);
    else
      _M_searcher->unset_stop_nodes();
    for(; _M_depth <= max_depth; _M_depth++) {
      Move tmp_best_move;
      if(checkmate_move_count > 0 ? _M_value >= MAX_VALUE - MAX_DEPTH && MAX_VALUE - _M_value <= checkmate_move_count * 2 : false) break;
      bool is_tmp_hint_move = false;
      Move tmp_hint_move;
      if(!_M_has_second_search) {
        _M_has_second_search = false;
        if(!_M_has_pondering) {
          is_tmp_hint_move = _M_has_hint_move;
          tmp_hint_move = _M_hint_move;
        } else {
          is_tmp_hint_move = _M_has_next_hint_move;
          tmp_hint_move = _M_next_hint_move;
        }
        if(!search(_M_alpha, _M_beta, search_moves, tmp_best_move, boards, last_board, fun)) break;
        if(!_M_has_pondering) {
          bool is_tmp_hint_move2 = _M_has_hint_move;
          Move tmp_hint_move2 = _M_hint_move;
          _M_has_hint_move = is_tmp_hint_move;
          _M_hint_move = tmp_hint_move;
          is_tmp_hint_move = is_tmp_hint_move2;
          tmp_hint_move = tmp_hint_move2;
        } else {
          bool is_tmp_hint_move2 = _M_has_next_hint_move;
          Move tmp_hint_move2 = _M_next_hint_move;
          _M_has_next_hint_move = is_tmp_hint_move;
          _M_next_hint_move = tmp_hint_move;
          is_tmp_hint_move = is_tmp_hint_move2;
          tmp_hint_move = tmp_hint_move2;
        }
      }
      if(_M_value <= _M_alpha || _M_value >= _M_beta) {
        _M_has_second_search = true;
        if(!search(MIN_VALUE, MAX_VALUE, search_moves, best_move, boards, last_board, fun)) break;
      } else {
        best_move = tmp_best_move;
        if(!_M_has_pondering) {
          _M_has_hint_move = is_tmp_hint_move;
          _M_hint_move = tmp_hint_move;
        } else {
          _M_has_next_hint_move = is_tmp_hint_move;
          _M_next_hint_move = tmp_hint_move;
        }
      }
      _M_has_second_search = false;
      _M_alpha = max(_M_value - VALUE_WINDOW, MIN_VALUE);
      _M_beta = min(_M_value + VALUE_WINDOW, MAX_VALUE);
    }
    _M_must_continue = false;
    return true;
  }

  bool Thinker::ponder(int max_depth, const vector<Move> *search_moves, uint64_t nodes, int checkmate_move_count, const vector<Board> &boards, function<void (int, int, unsigned, const Searcher *)> fun, bool is_pondering_move)
  {
    _M_must_continue = false;
    _M_has_pondering = true;
    if(is_pondering_move) {
      if(boards.empty()) {
        _M_has_pondering = false;
        return false;
      }
      Board tmp_board;
      if(_M_has_pondering_move) {
        if(!boards.back().make_move(_M_pondering_move, tmp_board)) {
          _M_has_pondering = false;
          return false;
        }
      } else {
        _M_has_pondering = false;
        return false;
      }
      MovePairList move_pairs(_M_move_pairs.get(), 0);
      if(tmp_board.in_checkmate(move_pairs) || tmp_board.in_stalemate(move_pairs)) {
        _M_has_best_move = false;
        _M_has_pondering = false;
        return false;
      }
      if(!think(max_depth, numeric_limits<unsigned>::max(), search_moves, nodes, checkmate_move_count, _M_best_move, boards, &tmp_board, fun)) {
        _M_has_pondering = false;
        return false;
      }
    } else {
      if(!think(max_depth, numeric_limits<unsigned>::max(), search_moves, nodes, checkmate_move_count, _M_best_move, boards, nullptr, fun)) {
        _M_has_pondering = false;
        return false;
      }
    }
    _M_has_best_move = (_M_best_move.to() != -1);
    _M_must_continue = true;
    _M_has_pondering = false;
    return true;
  }

  bool Thinker::search(int alpha, int beta, const vector<Move> *search_moves, Move &best_move, const vector<Board> &boards, const Board *last_board, function<void (int, int, unsigned, const Searcher *)> fun)
  {
    auto start_search_time = chrono::high_resolution_clock::now();
    _M_searcher->set_non_stop_flag(_M_depth == 1);
    try {
      _M_value = _M_searcher->search_from_root(alpha, beta, _M_depth, search_moves, best_move, boards, last_board);
    } catch(ThinkingStopException &e) {
      return false;
    } catch(PonderingStopException &e) {
      return false;
    }
    auto end_search_time = chrono::high_resolution_clock::now();
    auto diff = end_search_time - start_search_time;
    auto diff_ms = chrono::duration_cast<chrono::milliseconds>(diff);
    fun(_M_depth, _M_value, diff_ms.count(), _M_searcher);
    _M_searcher->set_previous_pv_line(_M_searcher->pv_line());
    if(_M_searcher->pv_line().length() >= 2) {
      if(!_M_has_pondering) {
        _M_has_hint_move = true;
        _M_hint_move = _M_searcher->pv_line()[1];
      } else {
        _M_has_next_hint_move = true;
        _M_next_hint_move = _M_searcher->pv_line()[1];
      }
    } else {
      if(!_M_has_pondering)
        _M_has_hint_move = false;
      else
        _M_has_next_hint_move = false;
    }
    return true;
  }
}
