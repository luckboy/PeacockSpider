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
  bool MovePairList::contain_move(Move move) const
  {
    for(size_t i = 0; i < _M_length; i++) {
      if(_M_move_pairs[i].move == move) return true;
    }
    return false;
  }

  void MovePairList::select_sort_move(size_t i)
  {
    size_t k = i;
    for(size_t j = i + 1; j < _M_length; j++) {
      if(_M_move_pairs[j].score > _M_move_pairs[k].score) k = j; 
    }
    if(k != i) {
      MovePair tmp_move_pair = _M_move_pairs[i];
      _M_move_pairs[i] = _M_move_pairs[k];
      _M_move_pairs[k] = tmp_move_pair;
    }
  }
}

