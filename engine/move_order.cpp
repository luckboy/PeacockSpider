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
  int MoveOrder::move_score(Move move, int ply, const Board &board, const EvaluationFunction *eval_fun, Move *best_move) const
  {
    if(static_cast<size_t>(ply) < _M_previous_pv_line.length() && move == _M_previous_pv_line[ply]) {
      return MOVE_SCORE_PV;
    } else if(best_move != nullptr && move == *best_move) {
      return MOVE_SCORE_BEST_MOVE;
    } else {
      bool is_cap = move.is_capture(board);
      if(is_cap || move.promotion_piece() != PromotionPiece::NONE) {
        int score = MOVE_SCORE_GOOD_MOVE;
        if(is_cap) score += eval_fun->material_piece_value(board.piece(move.to()));
        if(move.promotion_piece() != PromotionPiece::NONE) {
          score -= eval_fun->material_piece_value(Piece::PAWN);
          score += eval_fun->meterial_promotion_piece_value(move.promotion_piece());
        }
        return score;
      } else if(_M_history[side_to_index(board.side())][move.from()][move.to()] > 0) {
        return MOVE_SCORE_HISTORY + _M_history[side_to_index(board.side())][move.from()][move.to()];
      } else
        return board.side() == Side::WHITE ? move.from() * 64 + move.to() : (63 - move.from()) * 64 + (63 - move.to());
    }
  }

  void MoveOrder::set_move_scores(MovePairList &move_pairs, int ply, const Board &board, const EvaluationFunction *eval_fun, Move *best_move) const
  {
    for(size_t i = 0; i < move_pairs.length(); i++) {
      move_pairs[i].score = move_score(move_pairs[i].move, ply, board, eval_fun, best_move);
    }
  }

  void MoveOrder::clear()
  {
    for(int side = 0; side < 2; side++) {
      for(Square from = 0; from < 64; from++) {
        for(Square to = 0; to < 64; to++) {
          _M_history[side][from][to] = 0;
        }
      }
    }
    _M_previous_pv_line.clear();
  }

  void MoveOrder::set_previous_pv_line(const PVLine &pv_line)
  { _M_previous_pv_line = pv_line; }
}
