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
#ifndef _ZOBRIST_HPP
#define _ZOBRIST_HPP

#include "types.hpp"

namespace peacockspider
{
  extern HashKey zobrist[2][8][64];
  extern HashKey zobrist_white_side;
  extern HashKey zobrist_castlings[2][4];
  extern HashKey zobrist_en_passant_column[9];

  void initialize_zobrist(std::uint64_t seed);
}

#endif
