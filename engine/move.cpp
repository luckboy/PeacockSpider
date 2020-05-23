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
#include "chess.hpp"

using namespace std;

namespace peacockspider
{
  Move::Move(const CANMove &move, const Board &board, MovePairList &move_pairs)
  { if(!set_can(move, board, move_pairs)) throw Exception("illegal move"); }

  Move::Move(const SANMove &move, const Board &board, MovePairList &move_pairs)
  { if(!set_san(move, board, move_pairs)) throw Exception("illegal move"); }

  Move::Move(const string &str, const Board &board, MovePairList &move_pairs, bool is_can)
  {
    if(is_can) {
      if(!set_can(str, board, move_pairs)) throw Exception("illegal move");
    } else {
      if(!set_san(str, board, move_pairs)) throw Exception("illegal move");
    }
  }
  
  bool Move::is_capture(const Board &board) const
  {
    Square en_passant_squ = (board.en_passant_column() != -1 ? board.en_passant_column() + (board.side() == Side::WHITE ? 050 : 020) : -1);
    return board.has_color(~board.side(), to()) || (piece() == Piece::PAWN ? to() == en_passant_squ : false);
  }
  
  bool Move::is_check(const Board &board) const
  {
    Board tmp_board;
    board.make_move(*this, tmp_board);
    return tmp_board.in_check();
  }
  
  bool Move::is_checkmate(const Board &board, MovePairList &move_pairs) const
  {
    Board tmp_board;
    board.make_move(*this, tmp_board);
    return tmp_board.in_checkmate(move_pairs);
  }

  bool Move::set_can(const CANMove &move, const Board &board, MovePairList &move_pairs)
  {
    board.generate_pseudolegal_moves(move_pairs);
    for(size_t i = 0; i < move_pairs.length(); i++) {
      Move tmp_move = move_pairs[i].move;
      if(board.has_legal_move(tmp_move)) {
        if(tmp_move.from() == move.from() &&
          tmp_move.to() == move.to() &&
          ::peacockspider::equal_for_promotion(tmp_move.promotion_piece(), move.promotion_piece())) {
          *this = tmp_move;
          return true;
        }
      }
    }
    return false;
  }
  
  bool Move::set_san(const SANMove &move, const Board &board, MovePairList &move_pairs)
  {
    bool is_found = false;
    Move found_move;
    board.generate_pseudolegal_moves(move_pairs);
    Square castling_src = (board.side() == Side::WHITE ? E1 : E8); 
    Square short_castling_dst = (board.side() == Side::WHITE ? G1 : G8); 
    Square long_castling_dst = (board.side() == Side::WHITE ? C1 : C8); 
    for(size_t i = 0; i < move_pairs.length(); i++) {
      Move tmp_move = move_pairs[i].move;
      if(board.has_legal_move(tmp_move)) {
        if((move.flags() & (SANMoveFlags::SHORT_CASTLING | SANMoveFlags::LONG_CASTLING)) != SANMoveFlags::NONE ?
          ((move.flags() & SANMoveFlags::SHORT_CASTLING) != SANMoveFlags::NONE && tmp_move.piece() == Piece::KING && tmp_move.from() == castling_src && tmp_move.to() == short_castling_dst && tmp_move.promotion_piece() == PromotionPiece::NONE) ||
          ((move.flags() & SANMoveFlags::LONG_CASTLING) != SANMoveFlags::NONE && tmp_move.piece() == Piece::KING && tmp_move.from() == castling_src && tmp_move.to() == long_castling_dst && tmp_move.promotion_piece() == PromotionPiece::NONE) :
          (move.from_column() != -1 ? (tmp_move.from() & 7) == move.from_column() : true) &&
          (move.from_row() != -1 ? (tmp_move.from() >> 3) == move.from_row() : true) &&
          move.to() == tmp_move.to() &&
          ::peacockspider::equal_for_promotion(move.promotion_piece(), tmp_move.promotion_piece())) {
          if(is_found) return false;
          found_move = tmp_move;
          is_found = true;
        }
      }
    }
    if(is_found) {
      if((move.flags() & SANMoveFlags::CAPTURE) != SANMoveFlags::NONE) {
        if(!found_move.is_capture(board)) return false;
      }
      if((move.flags() & SANMoveFlags::CHECK) != SANMoveFlags::NONE) {
        if(!found_move.is_check(board)) return false;
      } else if((move.flags() & SANMoveFlags::CHECKMATE) != SANMoveFlags::NONE) {
        if(!found_move.is_checkmate(board, move_pairs)) return false;
      }
      *this = found_move;
      return true;
    } else
      return false;
  }

  CANMove Move::to_can_move() const
  { return CANMove(from(), to(), promotion_piece()); }

  SANMove Move::to_san_move(const Board &board, MovePairList &move_pairs) const
  {
    SANMove move;
    bool is_found = false;
    board.generate_pseudolegal_moves(move_pairs);
    Square castling_src = (board.side() == Side::WHITE ? E1 : E8); 
    Square short_castling_dst = (board.side() == Side::WHITE ? G1 : G8); 
    Square long_castling_dst = (board.side() == Side::WHITE ? C1 : C8); 
    if(piece() == Piece::KING && from() == castling_src && (to() == short_castling_dst || to() == long_castling_dst) && promotion_piece() == PromotionPiece::NONE) {
      for(size_t i = 0; i < move_pairs.length(); i++) {
        Move tmp_move = move_pairs[i].move;
        if(board.has_legal_move(tmp_move)) {
          if(tmp_move == *this) {
            is_found = true;
            break;
          }
        }
      }
      if(to() == short_castling_dst)
        move = SANMove(true);
      else
        move = SANMove(false);
    } else {
      bool must_be_src_col = false;
      bool must_be_src_row = false;
      bool is_ambiguous = false;
      move.set_flags(SANMoveFlags::NONE);
      for(size_t i = 0; i < move_pairs.length(); i++) {
        Move tmp_move = move_pairs[i].move;
        if(board.has_legal_move(tmp_move)) {
          if(tmp_move.equal_for_promotion(*this)) {
            is_found = true;
          } else if(tmp_move.piece() == piece() && tmp_move.to() == to() &&
            ::peacockspider::equal_for_promotion(tmp_move.promotion_piece(), promotion_piece()))  {
            if((tmp_move.from() & 7) == (from() & 7)) must_be_src_row = true;
            if((tmp_move.from() >> 3) == (from() >> 3)) must_be_src_col = true;
            is_ambiguous = true;
          }
        }
      }      
      if(is_ambiguous && !must_be_src_col && !must_be_src_row) must_be_src_col = true;
      if(!must_be_src_col && !must_be_src_row && piece() == Piece::PAWN && is_capture(board)) must_be_src_col = true;
      move.set_piece(piece());
      move.set_from_column(must_be_src_col ? (from() & 7) : -1);
      move.set_from_row(must_be_src_row ? (from() >> 3) : -1);
      move.set_to(to());
      move.set_promotion_piece(promotion_piece());
      if(is_capture(board)) move.set_flags(move.flags() | SANMoveFlags::CAPTURE);
    }
    if(is_found) {
      if(is_checkmate(board, move_pairs))
        move.set_flags(move.flags() | SANMoveFlags::CHECKMATE);
      else if(is_check(board))
        move.set_flags(move.flags() | SANMoveFlags::CHECK);
    }
    return move;
  }
}
