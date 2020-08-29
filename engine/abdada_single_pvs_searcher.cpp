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
#include "search.hpp"

using namespace std;

namespace peacockspider
{
  namespace
  {
    const int R = 3;
  }
  
  ABDADASinglePVSSearcher::ABDADASinglePVSSearcher(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, const vector<ABDADAThread> &threads, int max_depth, int max_quiescence_depth) :
    ABDADASingleSearcherBase(eval_fun, transpos_table, threads, max_depth, max_quiescence_depth) {}

  ABDADASinglePVSSearcher::~ABDADASinglePVSSearcher() {}
  
  int ABDADASinglePVSSearcher::search_from_root(int alpha, int beta, int depth, const vector<Move> *search_moves, Move &best_move, const vector<Board> &boards, const Board *last_board)
  {
    _M_stack[0].pv_line.clear();
    _M_nodes.store(0);
    try {
      check_stop_for_nodes();
    } catch(SearchingStopException &e) {
      return 0;
    }
    _M_nodes++;
    _M_stack[0].move_pairs = MovePairList(_M_move_pairs.get(), 0);
    _M_stack[0].board.generate_pseudolegal_moves(_M_stack[0].move_pairs);
    _M_move_order.set_move_scores(_M_stack[0].move_pairs, 0, _M_stack[0].board, _M_evaluation_function, nullptr);
    int best_value = MIN_VALUE;
    Move tmp_best_move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
    bool is_all_done = false;
    try {
      for(int iter = 0; iter < 2 && alpha < beta && !is_all_done; iter++) {
        bool is_first = true;
        is_all_done = true;
        for(size_t i = 0; i < _M_stack[0].move_pairs.length(); i++) {
          if(iter == 0) _M_stack[0].move_pairs.select_sort_move(i);
          Move move = _M_stack[0].move_pairs[i].move;
          if(search_moves != nullptr ? find(search_moves->begin(), search_moves->end(), move) != search_moves->end() : true) {
            if(_M_stack[0].board.make_move(move, _M_stack[1].board)) {
              bool is_exclusive = (iter == 0 && !is_first);
              int value;
              if(repetitions(_M_stack[1].board, boards, last_board) >= 1) {
                value = 0;
              } else {
                if(is_first) {
                  value = -search(-beta, -alpha, depth - 1, 1, true, is_exclusive);
                } else {
                  value = -search(-(alpha + 1), -alpha, depth - 1, 1, true, is_exclusive);
                  if(value != -VALUE_ON_EVALUATION && value > alpha && value < beta)
                    value = -search(-beta, -alpha, depth - 1, 1, true, is_exclusive);
                }
              }
              if(value == -VALUE_ON_EVALUATION) {
                is_all_done = false;
              } else if(value > best_value) {
                _M_stack[0].pv_line.update(move, _M_stack[1].pv_line);
                tmp_best_move = move;
                best_value = value;
                if(best_value > alpha) {
                  alpha = value;
                  if(best_value >= beta) {
                    _M_move_order.increase_history_for_cutoff(_M_stack[0].board.side(), move.from(), move.to(), depth);
                    best_move = tmp_best_move;
                    return best_value;
                  }
                  _M_move_order.increase_history_for_alpha(_M_stack[0].board.side(), move.from(), move.to(), depth);
                }
              }
              is_first = false;
            }
          }
        }
      }
    } catch(SearchingStopException &e) {
      return 0;
    }
    best_move = tmp_best_move;
    return best_value;
  }

  bool ABDADASinglePVSSearcher::before(int &alpha, int &beta, int depth, int ply, int &best_value, Move &best_move, bool is_exclusive) 
  { return _M_transposition_table->retrieve_for_abdada(_M_stack[ply].board.hash_key(), alpha, beta, depth, best_value, best_move, is_exclusive); }

  void ABDADASinglePVSSearcher::after(int alpha, int beta, int depth, int ply, int best_value, Move best_move)
  { _M_transposition_table->store(_M_stack[ply].board.hash_key(), alpha, beta, depth, best_value, best_move); }

  void ABDADASinglePVSSearcher::cutoff(int alpha, int beta, int depth, int ply, int best_value, Move best_move)
  { _M_transposition_table->store(_M_stack[ply].board.hash_key(), alpha, beta, depth, best_value, best_move); }

  int ABDADASinglePVSSearcher::search(int alpha, int beta, int depth, int ply, bool can_make_null_move, bool is_exclusive_node)
  {
    if(depth <= 0) {
      return quiescence_search(alpha, beta, _M_max_quiescence_depth, ply);
    } else {
      _M_stack[ply].pv_line.clear();
      _M_nodes++;
      check_stop_for_nodes();
      if(_M_stack[ply].board.halfmove_clock() >= 100) return 0;
      int tt_best_value;
      Move tt_best_move;
      if(before(alpha, beta, depth, ply, tt_best_value, tt_best_move, is_exclusive_node)) {
        if(tt_best_move.to() != -1) {
          if(_M_stack[ply].board.has_legal_move_for_tt(tt_best_move)) {
            _M_stack[ply + 1].pv_line.clear();
            _M_stack[ply].pv_line.update(tt_best_move, _M_stack[ply + 1].pv_line);
          } else
            _M_stack[ply].pv_line.clear();
        }
        return tt_best_value;
      }
      ABDADAThreadCountDecrement dec(this, ply);
      if(ply == 0)
        _M_stack[ply].move_pairs = MovePairList(_M_move_pairs.get(), 0);
      else
        _M_stack[ply].move_pairs = _M_stack[ply - 1].move_pairs.to_next_list();
      bool in_check = _M_stack[ply].board.in_check();
      if(!in_check && can_make_null_move && ply >= 2) {
        _M_stack[ply].board.make_null_move(_M_stack[ply + 1].board);
        int value = -search(-beta, -(beta - 1), depth - R - 1, ply + 1, false, false);
        if(value >= beta) {
          cutoff(alpha, beta, depth, ply, value, Move(Piece::PAWN, -1, -1, PromotionPiece::NONE));
          return value;
        }
      }
      _M_stack[ply].board.generate_pseudolegal_moves(_M_stack[ply].move_pairs);
      _M_move_order.set_move_scores(_M_stack[ply].move_pairs, ply, _M_stack[ply].board, _M_evaluation_function, &tt_best_move);
      int best_value = MIN_VALUE;
      int old_alpha = alpha;
      Move best_move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      bool is_legal_move = false;
      bool is_all_done = false;
      for(int iter = 0; iter < 2 && alpha < beta && !is_all_done; iter++) {
        bool is_first = true;
        is_all_done = true;
        for(size_t i = 0; i < _M_stack[ply].move_pairs.length(); i++) {
          if(iter == 0) _M_stack[ply].move_pairs.select_sort_move(i);
          Move move = _M_stack[ply].move_pairs[i].move;
          if(_M_stack[ply].board.make_move(move, _M_stack[ply + 1].board)) {
            is_legal_move = true;
            bool is_exclusive = (iter == 0 && !is_first);
            int value;
            if(is_first) {
              value = -search(-beta, -alpha, depth - 1, ply + 1, can_make_null_move, is_exclusive);
            } else {
              value = -search(-(alpha + 1), -alpha, depth - 1, ply + 1, can_make_null_move, is_exclusive);
              if(value != -VALUE_ON_EVALUATION && value > alpha && value < beta)
                value = -search(-beta, -alpha, depth - 1, ply + 1, can_make_null_move, is_exclusive);
            }
            if(value == -VALUE_ON_EVALUATION) {
              is_all_done = false;
            } else if(value > best_value) {
              _M_stack[ply].pv_line.update(move, _M_stack[ply + 1].pv_line);
              best_move = move;
              best_value = value;
              if(best_value > alpha) {
                alpha = best_value;
                if(best_value >= beta) {
                  _M_move_order.increase_history_for_cutoff(_M_stack[0].board.side(), move.from(), move.to(), depth);
                  cutoff(old_alpha, beta, depth, ply, best_value, best_move);
                  return best_value;
                }
                _M_move_order.increase_history_for_alpha(_M_stack[0].board.side(), move.from(), move.to(), depth);
              }
            }
            is_first = false;
          }
        }
      }
      if(!is_legal_move) {
        best_value = in_check ? MIN_VALUE + ply : 0;
      }
      after(old_alpha, beta, depth, ply, best_value, best_move);
      return best_value;
    }
  }
}
