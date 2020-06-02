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
  SingleSearcherBase::SingleSearcherBase(EvaluationFunction *eval_fun, int max_depth, int max_quiescence_depth) :
    _M_evaluation_function(eval_fun),
    _M_move_pairs(new MovePair[MAX_MOVE_COUNT * (max_depth + max_quiescence_depth)]),
    _M_stack(new SearchStackElement[max_depth + max_quiescence_depth + 1]),
    _M_max_quiescence_depth(max_quiescence_depth),
    _M_move_order(max_depth + max_quiescence_depth + 1),
    _M_nodes(0),
    _M_searching_stop_flag(false),
    _M_thinking_stop_flag(false),
    _M_non_stop_flag(false)
  {
    for(int i = 0; i < max_depth + max_quiescence_depth; i++) {
      _M_stack[i].pv_line.set_moves(new Move[max_depth + max_quiescence_depth - i]);
    }
  }
 
  SingleSearcherBase::~SingleSearcherBase() {}

  void SingleSearcherBase::set_board(const Board &board)
  { _M_stack[0].board = board; }

  void SingleSearcherBase::set_time(unsigned ms)
  { _M_stop_time = chrono::high_resolution_clock::now() + chrono::milliseconds(ms); }
    
  void SingleSearcherBase::clear()
  {
    _M_move_order.clear();
    _M_thinking_stop_flag.store(false);
    _M_searching_stop_flag.store(false);
  }

  void SingleSearcherBase::stop_thinking()
  { _M_thinking_stop_flag.store(true); }

  void SingleSearcherBase::stop_searching()
  { _M_searching_stop_flag.store(true); }

  void SingleSearcherBase::set_non_stop_flag(bool flag)
  { _M_non_stop_flag = flag; }

  const PVLine &SingleSearcherBase::pv_line() const
  { return _M_stack[0].pv_line; }

  std::uint64_t SingleSearcherBase::nodes() const
  { return _M_nodes; }

  unsigned SingleSearcherBase::thread_count() const
  { return 1; }

  void SingleSearcherBase::check_stop()
  {
    if(!_M_non_stop_flag) {
      auto now = chrono::high_resolution_clock::now();
      if(now >= _M_stop_time || _M_thinking_stop_flag.load()) throw ThinkingStopException();
    }
    if(_M_searching_stop_flag) throw SearchingStopException();
  }

  int SingleSearcherBase::quiescence_search(int alpha, int beta, int depth, int ply)
  {
    _M_stack[ply].pv_line.clear();
    _M_nodes++;
    check_stop_for_nodes();
    if(_M_stack[ply].board.halfmove_clock() >= 100) return 0;
    if(depth <= 0) {
      return (*_M_evaluation_function)(_M_stack[ply].board);
    } else {
      int eval_value = (*_M_evaluation_function)(_M_stack[ply].board);
      if(eval_value >= beta) return eval_value;
      if(eval_value > alpha) alpha = eval_value;
      if(ply == 0) {
        _M_stack[ply].move_pairs = MovePairList(_M_move_pairs.get(), 0);
      } else
        _M_stack[ply].move_pairs = _M_stack[ply - 1].move_pairs.to_next_list();
      _M_stack[ply].board.generate_pseudolegal_good_moves(_M_stack[ply].move_pairs);
      _M_move_order.set_move_scores(_M_stack[ply].move_pairs, ply, _M_stack[ply].board, _M_evaluation_function, nullptr);
      int best_value = eval_value;
      for(size_t i = 0; i < _M_stack[ply].move_pairs.length(); i++) {
        _M_stack[ply].move_pairs.select_sort_move(i);
        Move move = _M_stack[ply].move_pairs[i].move;
        if(_M_stack[ply].board.make_move(move, _M_stack[ply + 1].board)) {
          int value = -quiescence_search(-beta, -alpha, depth - 1, ply + 1);
          if(value > best_value) {
            best_value = value;
            _M_stack[ply].pv_line.update(move, _M_stack[ply + 1].pv_line);
            if(best_value > alpha) {
              alpha = best_value;
              if(best_value >= beta) return best_value;
            }
          }
        }
      }
      return best_value;
    }
  }
}
