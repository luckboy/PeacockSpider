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
#include "tables.hpp"

namespace peacockspider
{
  Square mailbox[120] = {
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1, 000, 001, 002, 003, 004, 005, 006, 007,  -1,
    -1, 010, 011, 012, 013, 014, 015, 016, 017,  -1,
    -1, 020, 021, 022, 023, 024, 025, 026, 027,  -1,
    -1, 030, 031, 032, 033, 034, 035, 036, 037,  -1,
    -1, 040, 041, 042, 043, 044, 045, 046, 047,  -1,
    -1, 050, 051, 052, 053, 054, 055, 056, 057,  -1,
    -1, 060, 061, 062, 063, 064, 065, 066, 067,  -1,
    -1, 070, 071, 072, 073, 074, 075, 076, 077,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
    -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1
  };

  int mailbox64[64] = {
     21, 22, 23, 24, 25, 26, 27, 28,
     31, 32, 33, 34, 35, 36, 37, 38,
     41, 42, 43, 44, 45, 46, 47, 48,
     51, 52, 53, 54, 55, 56, 57, 58,
     61, 62, 63, 64, 65, 66, 67, 68,
     71, 72, 73, 74, 75, 76, 77, 78,
     81, 82, 83, 84, 85, 86, 87, 88,
     91, 92, 93, 94, 95, 96, 97, 98
  };
  
  int tab_pawn_capture_steps120[2][2] = {
    { 11, 9 },
    { -9, -11 }
  };

  int tab_knight_steps120[8] = {
    21, 19, 12, 8, -8, -12, -19, -21
  };

  int tab_bishop_steps120[4] = {
    11, 9, -9, -11
  };

  int tab_rook_steps120[4] = {
    10, 1, -1, -10
  };
  
  int tab_queen_steps120[8] = {
    11, 10, 9, 1, -1, -9, -10, -11
  };

  int tab_king_steps120[8] = {
    11, 10, 9, 1, -1, -9, -10, -11
  };
  
  int tab_first_zone_steps120[9] = {
    11, 10, 9, 1, 0, -1, -9, -10, -11
  };

  int tab_second_zone_steps120[12] = {
    21, 20, 19, 12, 8, 2, -2, -8, -12, -19, -20, -21 
  };

  Bitboard tab_pawn_capture_bitboards[2][64];
  Bitboard tab_knight_bitboards[64];
  Bitboard tab_king_bitboards[64];

  int tab_pawn_capture_square_counts[2][64];
  Square8 tab_pawn_capture_squares[2][64][2];
  int tab_pawn_square_counts[2][64];
  Square8 tab_pawn_squares[2][64][2];
  int tab_knight_square_counts[64];
  Square8 tab_knight_squares[64][8];
  int tab_king_square_counts[64];
  Square8 tab_king_squares[64][8];
  
  int tab_bishop_square_counts[64][4];
  Square8 tab_bishop_squares[64][4][8];
  int tab_rook_square_counts[64][4];
  Square8 tab_rook_squares[64][4][8];
  int tab_queen_square_counts[64][8];
  Square8 tab_queen_squares[64][8][8];
  
  int tab_square_offset_counts[16];
  Square8 tab_square_offsets[16][4];

  Bitboard tab_column_bitboards[8];
  Bitboard tab_neighbour_column_bitboards[8];

  int tab_first_zone_square_counts[64];
  Square8 tab_first_zone_squares[64][16];
  int tab_second_zone_square_counts[64];
  Square8 tab_second_zone_squares[64][16];

  void initialize_tables()
  {
    // Initializes pawn capture bitboards.
    for(int side = 0; side < 2; side++) {
      for(Square from = 0; from < 64; from++) {
        int from120 = mailbox64[from];
        tab_pawn_capture_bitboards[side][from] = 0;
        for(int i = 0; i < 2; i++) {
          Square to = mailbox[from120 + tab_pawn_capture_steps120[side][i]];
          if(to != -1) tab_pawn_capture_bitboards[side][from] |= static_cast<Bitboard>(1) << to;
        }
      }
    }
    // Initializes knight bitboards.
    for(Square from = 0; from < 64; from++) {
      int from120 = mailbox64[from];
      tab_knight_bitboards[from] = 0;
      for(int i = 0; i < 8; i++) {
        Square to = mailbox[from120 + tab_knight_steps120[i]];
        if(to != -1) tab_knight_bitboards[from] |= static_cast<Bitboard>(1) << to;
      }
    }
    // Initializes king bitboards.
    for(Square from = 0; from < 64; from++) {
      int from120 = mailbox64[from];
      tab_king_bitboards[from] = 0;
      for(int i = 0; i < 8; i++) {
        Square to = mailbox[from120 + tab_king_steps120[i]];
        if(to != -1) tab_king_bitboards[from] |= static_cast<Bitboard>(1) << to;
      }
    }

    // Initializes pawn capture squares.
    for(int side = 0; side < 2; side++) {
      for(Square from = 0; from < 64; from++) {
        for(int i = 0; i < 2; i++) tab_pawn_capture_squares[side][from][i] = -1;
        int from120 = mailbox64[from];
        int count = 0;
        for(int i = 0; i < 2; i++) {
          Square to = mailbox[from120 + tab_pawn_capture_steps120[side][i]];
          if(to != -1) {
            tab_pawn_capture_squares[side][from][count] = to;
            count++;
          }
        }
        tab_pawn_capture_square_counts[side][from] = count;
      }
    }
    // Initializes pawn squares.
    for(int side = 0; side < 2; side++) {
      for(Square from = 0; from < 64; from++) {
        for(int i = 0; i < 2; i++) tab_pawn_squares[side][from][i] = -1;
        int from120 = mailbox64[from];
        Square to = mailbox[from120 + (side == 0 ? 10 : -10)];
        int count = 0;
        if(to != -1) {
          tab_pawn_squares[side][from][count] = to;
          count++;
          if(from / 8 == (side == 0 ? 1 : 6)) {
            to = mailbox[from120 + (side == 0 ? 20 : -20)];
            if(to != -1) {
              tab_pawn_squares[side][from][count] = to;
              count++;
            }
          }
        }
        tab_pawn_square_counts[side][from] = count;
      }
    }
    // Initializes knight squares.
    for(Square from = 0; from < 64; from++) {
      for(int i = 0; i < 8; i++) tab_knight_squares[from][i] = -1;
      int from120 = mailbox64[from];
      int count = 0;
      for(int i = 0; i < 8; i++) {
        Square to = mailbox[from120 + tab_knight_steps120[i]];
        if(to != -1) {
          tab_knight_squares[from][count] = to;
          count++;
        }
      }
      tab_knight_square_counts[from] = count;
    }
    // Initializes king squares.
    for(Square from = 0; from < 64; from++) {
      for(int i = 0; i < 8; i++) tab_king_squares[from][i] = -1;
      int from120 = mailbox64[from];
      int count = 0;
      for(int i = 0; i < 8; i++) {
        Square to = mailbox[from120 + tab_king_steps120[i]];
        if(to != -1) {
          tab_king_squares[from][count] = to;
          count++;
        }
      }
      tab_king_square_counts[from] = count;
    }
    
    // Initializes bishop squares.
    for(Square from = 0; from < 64; from++) {
      int from120 = mailbox64[from];
      for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 8; j++) tab_bishop_squares[from][i][j] = -1;
        int prev_to120 = from120; 
        int count = 0;
        for(int j = 0; j < 7; j++) {
          Square to = mailbox[prev_to120 + tab_bishop_steps120[i]];
          if(to != -1) {
            tab_bishop_squares[from][i][count] = to;
            count++;
            prev_to120 = mailbox64[to];
          } else
            break;
        }
        tab_bishop_square_counts[from][i] = count;
      }
    }
    // Initializes rook squares.
    for(Square from = 0; from < 64; from++) {
      int from120 = mailbox64[from];
      for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 8; j++) tab_rook_squares[from][i][j] = -1;
        int prev_to120 = from120; 
        int count = 0;
        for(int j = 0; j < 7; j++) {
          Square to = mailbox[prev_to120 + tab_rook_steps120[i]];
          if(to != -1) {
            tab_rook_squares[from][i][count] = to;
            count++;
            prev_to120 = mailbox64[to];
          } else
            break;
        }
        tab_rook_square_counts[from][i] = count;
      }
    }
    // Initializes queen squares.
    for(Square from = 0; from < 64; from++) {
      int from120 = mailbox64[from];
      for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) tab_queen_squares[from][i][j] = -1;
        int prev_to120 = from120; 
        int count = 0;
        for(int j = 0; j < 7; j++) {
          Square to = mailbox[prev_to120 + tab_queen_steps120[i]];
          if(to != -1) {
            tab_queen_squares[from][i][count] = to;
            count++;
            prev_to120 = mailbox64[to];
          } else
            break;
        }
        tab_queen_square_counts[from][i] = count;
      }
    }
    
    // Initializes square offsets.
    for(unsigned bits = 0; bits < 16; bits++) {
      for(int i = 0; i < 4; i++) tab_square_offsets[bits][i] = -1;
      int count = 0;
      for(int i = 0; i < 4; i++) {
        if((bits & (1 << i)) != 0) {
          tab_square_offsets[bits][count] = i;
          count++;
        }
      }
      tab_square_offset_counts[bits] = count;
    }

    // Initializes column bitboards.
    for(Column col = 0; col < 8; col++) {
      tab_column_bitboards[col] = 0;
      for(Row row = 0; row < 8; row++) {
        tab_column_bitboards[col] |= static_cast<Bitboard>(1) << (col + (row << 3));
      }
    }
    // Initializes neighbour column bitboards.
    for(Column col = 0; col < 8; col++) {
      tab_neighbour_column_bitboards[col] = 0;
      if(col - 1 >= 0) tab_neighbour_column_bitboards[col] |= tab_column_bitboards[col - 1];
      if(col + 1 < 8) tab_neighbour_column_bitboards[col] |= tab_column_bitboards[col + 1];
    }
    
    // Initializes first zone squares.
    for(Square from = 0; from < 64; from++) {
      for(int i = 0; i < 16; i++) tab_first_zone_squares[from][i] = -1;
      int from120 = mailbox64[from];
      int count = 0;
      for(int i = 0; i < 9; i++) {
        Square to = mailbox[from120 + tab_first_zone_steps120[i]];
        if(to != -1) {
          tab_first_zone_squares[from][count] = to;
          count++;
        }
      }
      tab_first_zone_square_counts[from] = count;
    }
    // Initializes second zone squares.
    for(Square from = 0; from < 64; from++) {
      for(int i = 0; i < 16; i++) tab_second_zone_squares[from][i] = -1;
      int from120 = mailbox64[from];
      int count = 0;
      for(int i = 0; i < 12; i++) {
        Square to = mailbox[from120 + tab_second_zone_steps120[i]];
        if(to != -1) {
          tab_second_zone_squares[from][count] = to;
          count++;
        }
      }
      tab_second_zone_square_counts[from] = count;
    }
  }
}
