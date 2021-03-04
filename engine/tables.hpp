/*
 * Peacock Spider - Chess engine.
 * Copyright (C) 2020-2021 Łukasz Szpakowski
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
#ifndef _TABLES_HPP
#define _TABLES_HPP

#include "types.hpp"

namespace peacockspider
{
  extern Square mailbox[120];
  extern int mailbox64[64];
  
  extern int tab_pawn_capture_steps120[2][2];
  extern int tab_knight_steps120[8];
  extern int tab_bishop_steps120[4];
  extern int tab_rook_steps120[4];
  extern int tab_queen_steps120[8];
  extern int tab_king_steps120[8];
  extern int tab_first_zone_steps120[9];
  extern int tab_second_zone_steps120[12];
  
  extern Bitboard tab_pawn_capture_bitboards[2][64];
  extern Bitboard tab_knight_bitboards[64];
  extern Bitboard tab_king_bitboards[64];

  extern int tab_pawn_capture_square_counts[2][64];
  extern Square8 tab_pawn_capture_squares[2][64][2];
  extern int tab_pawn_square_counts[2][64];
  extern Square8 tab_pawn_squares[2][64][2];
  extern int tab_knight_square_counts[64];
  extern Square8 tab_knight_squares[64][8];
  extern int tab_king_square_counts[64];
  extern Square8 tab_king_squares[64][8];
  
  extern int tab_bishop_square_counts[64][4];
  extern Square8 tab_bishop_squares[64][4][8];
  extern int tab_rook_square_counts[64][4];
  extern Square8 tab_rook_squares[64][4][8];
  extern int tab_queen_square_counts[64][8];
  extern Square8 tab_queen_squares[64][8][8];
  
  extern int tab_square_offset_counts[16];
  extern Square8 tab_square_offsets[16][4];

  extern Bitboard tab_column_bitboards[8];
  extern Bitboard tab_neighbour_column_bitboards[8];

  extern int tab_first_zone_square_counts[64];
  extern Square8 tab_first_zone_squares[64][16];
  extern int tab_second_zone_square_counts[64];
  extern Square8 tab_second_zone_squares[64][16];

  void initialize_tables();
}

#endif
