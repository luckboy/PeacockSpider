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
  SANMove::SANMove(const string &str)
  { if(!unsafely_set(str)) throw Exception("illegal move"); }
  
  bool SANMove::unsafely_set(const string &str)
  {
    auto iter = str.begin();
    set_flags(SANMoveFlags::NONE);
    if(str.length() >= 3 && string(iter, iter + 3) == "O-O") {
      *this = SANMove(true);
      iter += 3;
    } else if(str.length() >= 5 && string(iter, iter + 5) == "O-O-O") {
      *this = SANMove(false);
      iter += 3;
    } else {
      // Sets piece.
      if(iter == str.end()) return false;
      pair<Piece, bool> piece_pair = char_to_piece_pair(*iter);
      if(piece_pair.second) {
        set_piece(piece_pair.first);
        iter++;
      } else
        set_piece(Piece::PAWN);
      auto saved_iter = iter;
      // Sets source column.
      if(iter == str.end()) return false;
      Column tmp_src_col = -1;
      if(is_column_char(*iter)) {
        tmp_src_col = char_to_column(*iter);
        iter++;
      }
      // Sets source row.
      if(iter == str.end()) return false;
      Row tmp_src_row = -1;
      if(is_row_char(*iter)) {
        tmp_src_row = char_to_row(*iter);
        iter++;
      }
      if(iter == str.end() || (!is_column_char(*iter) && *iter != 'x')) {
        set_from_column(-1);
        set_from_row(-1);
        iter = saved_iter;
      } else {
        set_from_column(tmp_src_col);
        set_from_row(tmp_src_row);
      }
      // Sets flags for capture.
      if(iter == str.end()) return false;
      if(*iter == 'x') {
        set_flags(flags() | SANMoveFlags::CAPTURE);
        iter++;
      }
      // Sets destination.
      if(iter == str.end()) return false;
      if(iter + 1 == str.end()) return false;
      string dst_str(iter, iter + 2);
      Square dst = string_to_square(dst_str);
      if(dst == -1) return false;
      set_to(dst);
      iter += 2;
      // Sets promotion piece.
      bool must_promotion = false;
      if(iter != str.end()) {
        if(*iter == '=') {
          must_promotion = true;
          iter++;
        }
      }
      if(iter != str.end()) {
        PromotionPiece tmp_promotion_piece = char_to_promotion_piece(*iter);
        if(tmp_promotion_piece == PromotionPiece::NONE) {
          if(must_promotion) return false;
        } else {
          set_promotion_piece(tmp_promotion_piece);
          iter++;
        }
      } else {
        if(must_promotion) return false;
      }
    }
    // Sets flags for check and checkmate.
    if(iter != str.end()) {
      switch(*iter) {
        case '+':
          set_flags(SANMoveFlags::CHECK);
          iter++;
          break;
        case '#':
          set_flags(SANMoveFlags::CHECKMATE);
          iter++;
          break;
        default:
          break;
      }
    }
    while(iter != str.end()) {
      if(*iter != '!' && *iter != '?') break;
      iter++;
    }
    if(iter != str.end()) return false;
    return true;
  }
  
  bool SANMove::set(const string &str)
  {
    SANMove tmp_move;
    if(tmp_move.unsafely_set(str)) {
      *this = tmp_move;
      return true;
    } else
      return false;
  }
  
  string SANMove::to_string() const
  {
    string str;
    if((flags() & SANMoveFlags::SHORT_CASTLING) != SANMoveFlags::NONE) {
      str += "O-O";
    } else if((flags() & SANMoveFlags::LONG_CASTLING) != SANMoveFlags::NONE) {
      str += "O-O-O";
    } else {
      if(piece() != Piece::PAWN) str += piece_to_char(piece());
      if(from_column() != -1) str += column_to_char(from_column());
      if(from_row() != -1) str += row_to_char(from_row());
      if((flags() & SANMoveFlags::CAPTURE) != SANMoveFlags::NONE) str += 'x';
      str += square_to_string(to());
      if(promotion_piece() != PromotionPiece::NONE) {
        str += '=';
        str += promotion_piece_to_char(promotion_piece());
      }
    }
    if((flags() & SANMoveFlags::CHECK) != SANMoveFlags::NONE)
      str += '+';
    else if((flags() & SANMoveFlags::CHECK) != SANMoveFlags::NONE)
      str += '#';
    return str;
  }
}
