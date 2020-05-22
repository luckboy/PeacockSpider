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
#include <cctype>
#include "chess.hpp"

using namespace std;

namespace peacockspider
{
  CANMove::CANMove(const string &str)
  { if(!unsafely_set(str)) throw Exception("illegal move"); }

  bool CANMove::unsafely_set(const string &str)
  {
    auto iter = str.begin();
    // Sets source.
    if(iter == str.end()) return false;
    if(iter + 1 == str.end()) return false;
    string src_str(iter, iter + 2);
    Square src = string_to_square(src_str);
    if(src == -1) return false;
    set_from(src);
    iter += 2;
    // Sets destination.
    if(iter == str.end()) return false;
    if(iter + 1 == str.end()) return false;
    string dst_str(iter, iter + 2);
    Square dst = string_to_square(dst_str);
    if(dst == -1) return false;
    set_to(dst);
    iter += 2;
    // Sets promotion piece.
    if(iter != str.end()) {
      PromotionPiece tmp_promotion_piece = char_to_promotion_piece(toupper(*iter));
      if(tmp_promotion_piece == PromotionPiece::NONE) return false;
      set_promotion_piece(tmp_promotion_piece);
      iter++;
    } else
      set_promotion_piece(PromotionPiece::NONE);
    if(iter != str.end()) return false;
    return true;
  }

  bool CANMove::set(const string &str)
  {
    CANMove tmp_move;
    if(tmp_move.unsafely_set(str)) {
      *this = tmp_move;
      return true;
    } else
      return false;
  }

  string CANMove::to_string() const
  {
    string str;
    str += square_to_string(from());
    str += square_to_string(to());
    char c = promotion_piece_to_char(promotion_piece());
    if(c != 0) str += static_cast<char>(tolower(c));
    return str;
  }
}
