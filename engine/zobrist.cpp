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
#include <random>
#include "zobrist.hpp"

using namespace std;

namespace peacockspider
{
  HashKey zobrist[2][8][64];
  HashKey zobrist_white_side;
  HashKey zobrist_castlings[2][4];
  HashKey zobrist_en_passant_column[9];

  void initialize_zobrist(uint64_t seed)
  {
    mt19937_64 generator(seed);
    for(int side = 0; side < 2; side++) {
      for(int piece = 0; piece < 6; piece++) {
        for(Square squ = 0; squ < 64; squ++) {
          zobrist[side][piece][squ] = generator();
        }
      }
      for(int piece = 6; piece < 8; piece++) {
        for(Square squ = 0; squ < 64; squ++) {
          zobrist[side][piece][squ] = 0;
        }
      }
    }
    zobrist_white_side = generator();
    for(int side = 0; side < 2; side++) {
      for(int side_castlings = 0; side_castlings < 4; side_castlings++) {
        zobrist_castlings[side][side_castlings] = generator();
      }
    }
    for(int i = 0; i < 9; i++) {
      zobrist_en_passant_column[i] = generator();
    }
  }
}
