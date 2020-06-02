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
  PVLine::PVLine(std::size_t max_length) :
    _M_moves(new Move[max_length]), _M_length(0) {}
    
  PVLine &PVLine::operator=(const PVLine &pv_line)
  {
    for(size_t i = 0; i < pv_line._M_length; i++) {
      _M_moves[i] = pv_line._M_moves[i];
    }
    _M_length = pv_line._M_length; 
    return *this;
  }

  void PVLine::update(Move move, const PVLine &pv_line)
  {
    _M_moves[0] = move;
    for(size_t i = 0; pv_line._M_length; i++) {
      _M_moves[i + 1] = pv_line._M_moves[i];
    }
    _M_length = pv_line._M_length + 1;
  }
}