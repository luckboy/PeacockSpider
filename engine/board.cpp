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
  bool Board::has_attack(Side side, Square squ) const
  {
    // Not implemented.
    return false;
  }

  void Board::generate_pseudo_legal_moves(MovePairList &move_pairs) const
  {
    // Not implemented.
  }

  void Board::generate_pseudo_legel_good_moves(MovePairList &move_pairs) const
  {
    // Not implemented.
  }

  bool Board::make_move(Move move, Board &board) const
  {
    // Not implemented.
    return false;
  }
}
