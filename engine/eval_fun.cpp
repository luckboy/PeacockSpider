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
#include "eval.hpp"
#include "tables.hpp"

using namespace std;

namespace peacockspider
{
  void EvaluationFunction::set(const int *params)
  {
    int i;
    // Sets piece material.
    _M_piece_material[piece_to_index(Piece::PAWN)] = 100;
    _M_piece_material[piece_to_index(Piece::KNIGHT)] = params[EVALUATION_PARAMETER_KNIGHT_MATERIAL];
    _M_piece_material[piece_to_index(Piece::BISHOP)] = params[EVALUATION_PARAMETER_BISHOP_MATERIAL];
    _M_piece_material[piece_to_index(Piece::ROOK)] = params[EVALUATION_PARAMETER_ROOK_MATERIAL];
    _M_piece_material[piece_to_index(Piece::QUEEN)] = params[EVALUATION_PARAMETER_QUEEN_MATERIAL];
    _M_piece_material[piece_to_index(Piece::KING)] = 0;
    // Sets piece/square.
    for(int side = 0; side < 2; side++) {
      // Pawns.
      if(static_cast<size_t>(side) == side_to_index(Side::WHITE)) {
        i = 0;
        for(Row row = 0; row < 8; row++) {
          for(Column col = 0; col < 8; col++) {
            _M_piece_square[side][piece_to_index(Piece::PAWN)][col + (row << 3)] = params[EVALUATION_PARAMETER_PAWN_ADVANCE] * i;
          }
          i++;
        }
      } else {
        i = 0;
        for(Row row = 7; row >= 0; row--) {
          for(Column col = 0; col < 8; col++) {
            _M_piece_square[side][piece_to_index(Piece::PAWN)][col + (row << 3)] = params[EVALUATION_PARAMETER_PAWN_ADVANCE] * i;
          }
          i++;
        }
      }
      i = 0;
      for(Column col = 0; col < 4; col++) {
        for(Row row = 0; row < 8; row++) {
          _M_piece_square[side][piece_to_index(Piece::PAWN)][col + (row << 3)] += params[EVALUATION_PARAMETER_PAWN_CENTER] * i;
          _M_piece_square[side][piece_to_index(Piece::PAWN)][(7 - col) + (row << 3)] += params[EVALUATION_PARAMETER_PAWN_CENTER] * i;
        }
        i++;
      }
      // Knights.
      i = 0;
      for(Row row = 0; row < 4; row++) {
        for(Column col = 0; col < 8; col++) {
          _M_piece_square[side][piece_to_index(Piece::KNIGHT)][col + (row << 3)] = params[EVALUATION_PARAMETER_KNIGHT_CENTER] * i;
          _M_piece_square[side][piece_to_index(Piece::KNIGHT)][col + ((7 - row) << 3)] = params[EVALUATION_PARAMETER_KNIGHT_CENTER] * i;
        }
        i++;
      }
      i = 0;
      for(Column col = 0; col < 4; col++) {
        for(Row row = 0; row < 8; row++) {
          _M_piece_square[side][piece_to_index(Piece::KNIGHT)][col + (row << 3)] += params[EVALUATION_PARAMETER_KNIGHT_CENTER] * i;
          _M_piece_square[side][piece_to_index(Piece::KNIGHT)][(7 - col) + (row << 3)] += params[EVALUATION_PARAMETER_KNIGHT_CENTER] * i;
        }
        i++;
      }
      // Bishops.
      i = 0;
      for(Row row = 0; row < 4; row++) {
        for(Column col = 0; col < 8; col++) {
          _M_piece_square[side][piece_to_index(Piece::BISHOP)][col + (row << 3)] = params[EVALUATION_PARAMETER_BISHOP_CENTER] * i;
          _M_piece_square[side][piece_to_index(Piece::BISHOP)][col + ((7 - row) << 3)] = params[EVALUATION_PARAMETER_BISHOP_CENTER] * i;
        }
        i++;
      }
      i = 0;
      for(Column col = 0; col < 4; col++) {
        for(Row row = 0; row < 8; row++) {
          _M_piece_square[side][piece_to_index(Piece::BISHOP)][col + (row << 3)] += params[EVALUATION_PARAMETER_BISHOP_CENTER] * i;
          _M_piece_square[side][piece_to_index(Piece::BISHOP)][(7 - col) + (row << 3)] += params[EVALUATION_PARAMETER_BISHOP_CENTER] * i;
        }
        i++;
      }
      // Rook.
      i = 0;
      for(Row row = 0; row < 4; row++) {
        for(Column col = 0; col < 8; col++) {
          _M_piece_square[side][piece_to_index(Piece::ROOK)][col + (row << 3)] = params[EVALUATION_PARAMETER_ROOK_CENTER] * i;
          _M_piece_square[side][piece_to_index(Piece::ROOK)][col + ((7 - row) << 3)] = params[EVALUATION_PARAMETER_ROOK_CENTER] * i;
        }
        i++;
      }
      i = 0;
      for(Column col = 0; col < 4; col++) {
        for(Row row = 0; row < 8; row++) {
          _M_piece_square[side][piece_to_index(Piece::ROOK)][col + (row << 3)] += params[EVALUATION_PARAMETER_ROOK_CENTER] * i;
          _M_piece_square[side][piece_to_index(Piece::ROOK)][(7 - col) + (row << 3)] += params[EVALUATION_PARAMETER_ROOK_CENTER] * i;
        }
        i++;
      }
      if(static_cast<size_t>(side) == side_to_index(Side::WHITE)) {
        _M_piece_square[side][piece_to_index(Piece::ROOK)][F1] += params[EVALUATION_PARAMETER_ROOK_CASTLING];
        _M_piece_square[side][piece_to_index(Piece::ROOK)][D1] += params[EVALUATION_PARAMETER_ROOK_CASTLING];
      } else {
        _M_piece_square[side][piece_to_index(Piece::ROOK)][F8] += params[EVALUATION_PARAMETER_ROOK_CASTLING];
        _M_piece_square[side][piece_to_index(Piece::ROOK)][D8] += params[EVALUATION_PARAMETER_ROOK_CASTLING];
      }
      // Queen.
      i = 0;
      for(Row row = 0; row < 4; row++) {
        for(Column col = 0; col < 8; col++) {
          _M_piece_square[side][piece_to_index(Piece::QUEEN)][col + (row << 3)] = params[EVALUATION_PARAMETER_QUEEN_CENTER] * i;
          _M_piece_square[side][piece_to_index(Piece::QUEEN)][col + ((7 - row) << 3)] = params[EVALUATION_PARAMETER_QUEEN_CENTER] * i;
        }
        i++;
      }
      i = 0;
      for(Column col = 0; col < 4; col++) {
        for(Row row = 0; row < 8; row++) {
          _M_piece_square[side][piece_to_index(Piece::QUEEN)][col + (row << 3)] += params[EVALUATION_PARAMETER_QUEEN_CENTER] * i;
          _M_piece_square[side][piece_to_index(Piece::QUEEN)][(7 - col) + (row << 3)] += params[EVALUATION_PARAMETER_QUEEN_CENTER] * i;
        }
        i++;
      }
      for(Square squ = 0; squ < 64; squ++) {
        _M_piece_square[side][piece_to_index(Piece::KING)][squ] = 0;
      }
      // King.
      if(static_cast<size_t>(side) == side_to_index(Side::WHITE)) {
        for(Square squ = 0; squ < 8; squ++) {
          _M_king_square[side][squ] = 0;
        }
        for(Square squ = 8; squ < 64; squ++) {
          _M_king_square[side][squ] = params[EVALUATION_PARAMETER_KING_UNSAFETY];
        }
        _M_king_square[side][G1] = params[EVALUATION_PARAMETER_KING_CASTLING]; 
        _M_king_square[side][C1] = params[EVALUATION_PARAMETER_KING_CASTLING]; 
      } else {
        for(Square squ = 7 * 8; squ < 64; squ++) {
          _M_king_square[side][squ] = 0;
        }
        for(Square squ = 0; squ < 7 * 8; squ++) {
          _M_king_square[side][squ] = params[EVALUATION_PARAMETER_KING_UNSAFETY];
        }
        _M_king_square[side][G8] = params[EVALUATION_PARAMETER_KING_CASTLING]; 
        _M_king_square[side][C8] = params[EVALUATION_PARAMETER_KING_CASTLING]; 
      }
    }
    // Set king/square for endgame.
    i = 0;
    for(Row row = 0; row < 4; row++) {
      for(Column col = 0; col < 8; col++) {
        _M_king_square_for_endgame[col + (row << 3)] = params[EVALUATION_PARAMETER_KING_CENTER] * i;
        _M_king_square_for_endgame[col + ((7 - row) << 3)] = params[EVALUATION_PARAMETER_KING_CENTER] * i;
      }
      i++;
    }
    i = 0;
    for(Column col = 0; col < 4; col++) {
      for(Row row = 0; row < 8; row++) {
        _M_king_square_for_endgame[col + (row << 3)] += params[EVALUATION_PARAMETER_KING_CENTER] * i;
        _M_king_square_for_endgame[(7 - col) + (row << 3)] += params[EVALUATION_PARAMETER_KING_CENTER] * i;
      }
      i++;
    }
    // Sets endgame material.
    _M_endgame_material = params[EVALUATION_PARAMETER_ENDGAME_MATERIAL];
    // Sets isolated pawn.
    _M_isolated_pawn = params[EVALUATION_PARAMETER_ISOLATED_PAWN];
    // Sets doubled pawn.
    _M_doubled_pawn = params[EVALUATION_PARAMETER_DOUBLED_PAWN];
    // Sets piece/square bits.
    for(int side = 0; side < 2; side++) {
      for(int piece = 0; piece < 6; piece++) {
        for(Square j = 0; j < 64; j += 4) {
          for(int bits = 0; bits < 16; bits++) {
            _M_piece_square_bits[side][piece][j >> 2][bits] = 0;
            for(int k = 0; k < 4; k++) {
              if((bits & (1 << k)) != 0)
                _M_piece_square_bits[side][piece][j >> 2][bits] += _M_piece_square[side][piece][j + k];
            }
          }
        }
      }
    }
    // Sets piece mobilities.
    _M_piece_mobilities[piece_to_index(Piece::PAWN)] = params[EVALUATION_PARAMETER_PAWN_MOBILITY];
    _M_piece_mobilities[piece_to_index(Piece::KNIGHT)] = params[EVALUATION_PARAMETER_KNIGHT_MOBILITY];
    _M_piece_mobilities[piece_to_index(Piece::BISHOP)] = params[EVALUATION_PARAMETER_BISHOP_MOBILITY];
    _M_piece_mobilities[piece_to_index(Piece::ROOK)] = params[EVALUATION_PARAMETER_ROOK_MOBILITY];
    _M_piece_mobilities[piece_to_index(Piece::QUEEN)] = params[EVALUATION_PARAMETER_QUEEN_MOBILITY];
    _M_piece_mobilities[piece_to_index(Piece::KING)] = params[EVALUATION_PARAMETER_KING_MOBILITY];
    // Sets piece defences.
    _M_piece_defences[piece_to_index(Piece::PAWN)] = params[EVALUATION_PARAMETER_PAWN_DEFENCE];
    _M_piece_defences[piece_to_index(Piece::KNIGHT)] = params[EVALUATION_PARAMETER_KNIGHT_DEFENCE];
    _M_piece_defences[piece_to_index(Piece::BISHOP)] = params[EVALUATION_PARAMETER_BISHOP_DEFENCE];
    _M_piece_defences[piece_to_index(Piece::ROOK)] = params[EVALUATION_PARAMETER_ROOK_DEFENCE];
    _M_piece_defences[piece_to_index(Piece::QUEEN)] = params[EVALUATION_PARAMETER_QUEEN_DEFENCE];
    _M_piece_defences[piece_to_index(Piece::KING)] = 0;
    // Sets piece/piece pins.
    for(int piece1 = 0; piece1 < 6; piece1++) {
      for(int piece2 = 0; piece2 < 6; piece2++)
        _M_piece_piece_pins[piece1][piece2] = 0;
    }
    _M_piece_piece_pins[piece_to_index(Piece::QUEEN)][piece_to_index(Piece::KING)] = params[EVALUATION_PARAMETER_QUEEN_KING_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::ROOK)][piece_to_index(Piece::KING)] = params[EVALUATION_PARAMETER_ROOK_KING_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::BISHOP)][piece_to_index(Piece::KING)] = params[EVALUATION_PARAMETER_BISHOP_KING_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::KNIGHT)][piece_to_index(Piece::KING)] = params[EVALUATION_PARAMETER_KNIGHT_KING_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::PAWN)][piece_to_index(Piece::KING)] = params[EVALUATION_PARAMETER_PAWN_KING_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::ROOK)][piece_to_index(Piece::QUEEN)] = params[EVALUATION_PARAMETER_ROOK_QUEEN_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::BISHOP)][piece_to_index(Piece::QUEEN)] = params[EVALUATION_PARAMETER_BISHOP_QUEEN_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::KNIGHT)][piece_to_index(Piece::QUEEN)] = params[EVALUATION_PARAMETER_KNIGHT_QUEEN_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::PAWN)][piece_to_index(Piece::QUEEN)] = params[EVALUATION_PARAMETER_PAWN_QUEEN_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::BISHOP)][piece_to_index(Piece::ROOK)] = params[EVALUATION_PARAMETER_BISHOP_ROOK_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::KNIGHT)][piece_to_index(Piece::ROOK)] = params[EVALUATION_PARAMETER_KNIGHT_ROOK_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::PAWN)][piece_to_index(Piece::ROOK)] = params[EVALUATION_PARAMETER_PAWN_ROOK_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::PAWN)][piece_to_index(Piece::BISHOP)] = params[EVALUATION_PARAMETER_PAWN_BISHOP_PIN];
    _M_piece_piece_pins[piece_to_index(Piece::PAWN)][piece_to_index(Piece::KNIGHT)] = params[EVALUATION_PARAMETER_PAWN_KNIGHT_PIN];
  }
  
  int EvaluationFunction::operator()(const Board &board) const
  {
    int value = 0;
    int white_material_value = 0;
    int black_material_value = 0;
    for(Square i = 0; i < 64; i += 4) {
      int bits, count;
      bits = ((board.color_bitboard(Side::WHITE) & board.piece_bitboard(Piece::PAWN)) >> i) & 0xf;
      count = tab_square_offset_counts[bits];
      white_material_value += _M_piece_material[piece_to_index(Piece::PAWN)] * count;
      bits = ((board.color_bitboard(Side::BLACK) & board.piece_bitboard(Piece::PAWN)) >> i) & 0xf;
      count = tab_square_offset_counts[bits];
      black_material_value += _M_piece_material[piece_to_index(Piece::PAWN)] * count;
      bits = ((board.color_bitboard(Side::WHITE) & board.piece_bitboard(Piece::KNIGHT)) >> i) & 0xf;
      count = tab_square_offset_counts[bits];
      white_material_value += _M_piece_material[piece_to_index(Piece::KNIGHT)] * count;
      bits = ((board.color_bitboard(Side::BLACK) & board.piece_bitboard(Piece::KNIGHT)) >> i) & 0xf;
      count = tab_square_offset_counts[bits];
      black_material_value += _M_piece_material[piece_to_index(Piece::KNIGHT)] * count;
      bits = ((board.color_bitboard(Side::WHITE) & board.piece_bitboard(Piece::BISHOP)) >> i) & 0xf;
      count = tab_square_offset_counts[bits];
      white_material_value += _M_piece_material[piece_to_index(Piece::BISHOP)] * count;
      bits = ((board.color_bitboard(Side::BLACK) & board.piece_bitboard(Piece::BISHOP)) >> i) & 0xf;
      count = tab_square_offset_counts[bits];
      black_material_value += _M_piece_material[piece_to_index(Piece::BISHOP)] * count;
      bits = ((board.color_bitboard(Side::WHITE) & board.piece_bitboard(Piece::ROOK)) >> i) & 0xf;
      count = tab_square_offset_counts[bits];
      white_material_value += _M_piece_material[piece_to_index(Piece::ROOK)] * count;
      bits = ((board.color_bitboard(Side::BLACK) & board.piece_bitboard(Piece::ROOK)) >> i) & 0xf;
      count = tab_square_offset_counts[bits];
      black_material_value += _M_piece_material[piece_to_index(Piece::ROOK)] * count;
      bits = ((board.color_bitboard(Side::WHITE) & board.piece_bitboard(Piece::QUEEN)) >> i) & 0xf;
      count = tab_square_offset_counts[bits];
      white_material_value += _M_piece_material[piece_to_index(Piece::QUEEN)] * count;
      bits = ((board.color_bitboard(Side::BLACK) & board.piece_bitboard(Piece::QUEEN)) >> i) & 0xf;
      count = tab_square_offset_counts[bits];
      black_material_value += _M_piece_material[piece_to_index(Piece::QUEEN)] * count;
      bits = ((board.color_bitboard(Side::WHITE) & board.piece_bitboard(Piece::PAWN)) >> i) & 0xf;
      value += _M_piece_square_bits[side_to_index(Side::WHITE)][piece_to_index(Piece::PAWN)][i >> 2][bits];
      bits = ((board.color_bitboard(Side::BLACK) & board.piece_bitboard(Piece::PAWN)) >> i) & 0xf;
      value -= _M_piece_square_bits[side_to_index(Side::BLACK)][piece_to_index(Piece::PAWN)][i >> 2][bits];
      bits = ((board.color_bitboard(Side::WHITE) & board.piece_bitboard(Piece::KNIGHT)) >> i) & 0xf;
      value += _M_piece_square_bits[side_to_index(Side::WHITE)][piece_to_index(Piece::KNIGHT)][i >> 2][bits];
      bits = ((board.color_bitboard(Side::BLACK) & board.piece_bitboard(Piece::KNIGHT)) >> i) & 0xf;
      value -= _M_piece_square_bits[side_to_index(Side::BLACK)][piece_to_index(Piece::KNIGHT)][i >> 2][bits];
      bits = ((board.color_bitboard(Side::WHITE) & board.piece_bitboard(Piece::BISHOP)) >> i) & 0xf;
      value += _M_piece_square_bits[side_to_index(Side::WHITE)][piece_to_index(Piece::BISHOP)][i >> 2][bits];
      bits = ((board.color_bitboard(Side::BLACK) & board.piece_bitboard(Piece::BISHOP)) >> i) & 0xf;
      value -= _M_piece_square_bits[side_to_index(Side::BLACK)][piece_to_index(Piece::BISHOP)][i >> 2][bits];
      bits = ((board.color_bitboard(Side::WHITE) & board.piece_bitboard(Piece::ROOK)) >> i) & 0xf;
      value += _M_piece_square_bits[side_to_index(Side::WHITE)][piece_to_index(Piece::ROOK)][i >> 2][bits];
      bits = ((board.color_bitboard(Side::BLACK) & board.piece_bitboard(Piece::ROOK)) >> i) & 0xf;
      value -= _M_piece_square_bits[side_to_index(Side::BLACK)][piece_to_index(Piece::ROOK)][i >> 2][bits];
      bits = ((board.color_bitboard(Side::WHITE) & board.piece_bitboard(Piece::QUEEN)) >> i) & 0xf;
      value += _M_piece_square_bits[side_to_index(Side::WHITE)][piece_to_index(Piece::QUEEN)][i >> 2][bits];
      bits = ((board.color_bitboard(Side::BLACK) & board.piece_bitboard(Piece::QUEEN)) >> i) & 0xf;
      value -= _M_piece_square_bits[side_to_index(Side::BLACK)][piece_to_index(Piece::QUEEN)][i >> 2][bits];
    }
    value += white_material_value - black_material_value;
    if(white_material_value + black_material_value > _M_endgame_material) {
      value += _M_king_square[side_to_index(Side::WHITE)][board.king_square(Side::WHITE)];
      value -= _M_king_square[side_to_index(Side::BLACK)][board.king_square(Side::BLACK)];
    } else {
      value += _M_king_square_for_endgame[board.king_square(Side::WHITE)];
      value -= _M_king_square_for_endgame[board.king_square(Side::BLACK)];
    }
    for(Column col = 0; col < 8; col++) {
      if((board.color_bitboard(Side::WHITE) & board.piece_bitboard(Piece::PAWN) & tab_column_bitboards[col]) != 0) {
        if((board.color_bitboard(Side::WHITE) & board.piece_bitboard(Piece::PAWN) & tab_neighbour_column_bitboards[col]) == 0)
          value += _M_isolated_pawn;
      }
      if((board.color_bitboard(Side::BLACK) & board.piece_bitboard(Piece::PAWN) & tab_column_bitboards[col]) != 0) {
        if((board.color_bitboard(Side::BLACK) & board.piece_bitboard(Piece::PAWN) & tab_neighbour_column_bitboards[col]) == 0)
          value -= _M_isolated_pawn;
      }
      int pawn_count = 0;
      for(Row row = 0; row < 7; row++) {
        if(board.has_color_piece(Side::WHITE, Piece::PAWN, col + (row << 3))) pawn_count++;
      }
      if(pawn_count >= 2) value += _M_doubled_pawn;
      pawn_count = 0;
      for(Row row = 7; row >= 0; row--) {
        if(board.has_color_piece(Side::WHITE, Piece::PAWN, col + (row << 3))) pawn_count++;
      }
      if(pawn_count >= 2) value -= _M_doubled_pawn;
    }
    value += fold_squares(board.color_bitboard(Side::WHITE) | board.color_bitboard(Side::BLACK), 0, [&](int sum, Square from) {
      Side side = board.has_color(Side::WHITE, from) ? Side::WHITE : Side::BLACK;
      int tmp_value;
      if(board.has_piece(Piece::PAWN, from)) {
        tmp_value = fold_pawn_capture_squares(side, from, 0, [&](int sum2, Square to) {
          Square en_passant_squ = (board.en_passant_column() != -1 ? board.en_passant_column() + (board.side() == Side::WHITE ? 050 : 020) : -1);
          if(board.has_color(~side, to) || to == en_passant_squ)
            return sum2 + _M_piece_mobilities[piece_to_index(Piece::PAWN)];
          else if(board.has_color(side, to))
            return sum2 + _M_piece_defences[piece_to_index(board.piece(to))];
          else
            return sum2;
        });
        tmp_value += fold_pawn_squares(side, from, 0, [&](int sum2, Square to) {
          if(board.has_empty(to))
            return make_pair(sum2 + _M_piece_mobilities[piece_to_index(Piece::PAWN)], true);
          else
            return make_pair(sum2, false);
        });
      } else if(board.has_piece(Piece::KNIGHT, from)) {
        tmp_value = fold_knight_squares(from, 0, [&](int sum2, Square to) {
          if(board.has_color(~side, to))
            return sum2 + _M_piece_mobilities[piece_to_index(Piece::KNIGHT)];
          else if(board.has_color(side, to))
            return sum2 + _M_piece_defences[piece_to_index(board.piece(to))];
          else
            return sum2 + _M_piece_mobilities[piece_to_index(Piece::KNIGHT)];
        });
      } else if(board.has_piece(Piece::BISHOP, from)) {
        tmp_value = fold_bishop_slides(from, 0, [&](int sum2) { return sum2; }, [&](int sum2, Square to) {
          if(board.has_color(~side, to))
            return make_pair(sum2 + _M_piece_mobilities[piece_to_index(Piece::BISHOP)], false);
          else if(board.has_color(side, to))
            return make_pair(sum2 + _M_piece_defences[piece_to_index(board.piece(to))], false);
          else
            return make_pair(sum2 + _M_piece_mobilities[piece_to_index(Piece::BISHOP)], true);
        });
      } else if(board.has_piece(Piece::ROOK, from)) {
        tmp_value = fold_rook_slides(from, 0, [&](int sum2) { return sum2; }, [&](int sum2, Square to) {
          if(board.has_color(~side, to))
            return make_pair(sum2 + _M_piece_mobilities[piece_to_index(Piece::ROOK)], false);
          else if(board.has_color(side, to))
            return make_pair(sum2 + _M_piece_defences[piece_to_index(board.piece(to))], false);
          else
            return make_pair(sum2 + _M_piece_mobilities[piece_to_index(Piece::ROOK)], true);
        });
      } else if(board.has_piece(Piece::QUEEN, from)) {
        tmp_value = fold_queen_slides(from, 0, [&](int sum2) { return sum2; }, [&](int sum2, Square to) {
          if(board.has_color(~side, to))
            return make_pair(sum2 + _M_piece_mobilities[piece_to_index(Piece::QUEEN)], false);
          else if(board.has_color(side, to))
            return make_pair(sum2 + _M_piece_defences[piece_to_index(board.piece(to))], false);
          else
            return make_pair(sum2 + _M_piece_mobilities[piece_to_index(Piece::QUEEN)], true);
        });
      } else if(board.has_piece(Piece::KING, from)) {
        tmp_value = fold_king_squares(from, 0, [&](int sum2, Square to) {
          if(board.has_color(~side, to))
            return sum2 + _M_piece_mobilities[piece_to_index(Piece::KING)];
          else if(board.has_color(side, to))
            return sum2 + _M_piece_defences[piece_to_index(board.piece(to))];
          else
            return sum2 + _M_piece_mobilities[piece_to_index(Piece::KING)];
        });
      } else
        tmp_value = 0;
      return sum + (side == Side::WHITE ? tmp_value : -tmp_value);
    });
    value += fold_squares(board.color_bitboard(Side::WHITE) | board.color_bitboard(Side::BLACK), 0, [&](int sum, Square to) {
      Side side = board.has_color(Side::WHITE, to) ? Side::WHITE : Side::BLACK;
      Piece piece1;
      Piece piece2 = board.piece(to);
      int tmp_value;
      tmp_value = fold_bishop_slides(to, make_pair(0, false), [&](pair<int, bool> tmp_pair) {
        return make_pair(tmp_pair.first, false);
      }, [&](pair<int, bool> tmp_pair, Square from) {
        if(board.has_empty(from)) {
          return make_pair(tmp_pair, true); 
        } else {
          if(!tmp_pair.second) {
            if(board.has_color(side, from)) {
              piece1 = board.piece(from);
              return make_pair(make_pair(tmp_pair.first, true), true);
            } else
              return make_pair(tmp_pair, false);
          } else {
            if(board.has_color_piece(~side, Piece::BISHOP, Piece::QUEEN, from)) {
              int pin_value = _M_piece_piece_pins[piece_to_index(piece1)][piece_to_index(piece2)];
              return make_pair(make_pair(tmp_pair.first + pin_value, tmp_pair.second), false);
            } else
              return make_pair(tmp_pair, false);
          }
        }
      }).first;
      tmp_value += fold_rook_slides(to, make_pair(0, false), [&](pair<int, bool> tmp_pair) {
        return make_pair(tmp_pair.first, false);
      }, [&](pair<int, bool> tmp_pair, Square from) {
        if(board.has_empty(from)) {
          return make_pair(tmp_pair, true); 
        } else {
          if(!tmp_pair.second) {
            if(board.has_color(side, from)) {
              piece1 = board.piece(from);
              return make_pair(make_pair(tmp_pair.first, true), true);
            } else
              return make_pair(tmp_pair, false);
          } else {
            if(board.has_color_piece(~side, Piece::ROOK, Piece::QUEEN, from)) {
              int pin_value = _M_piece_piece_pins[piece_to_index(piece1)][piece_to_index(piece2)];
              return make_pair(make_pair(tmp_pair.first + pin_value, tmp_pair.second), false);
            } else
              return make_pair(tmp_pair, false);
          }
        }
      }).first;
      return sum + (side == Side::WHITE ? tmp_value : -tmp_value);
    });
    return (board.side() == Side::WHITE ? value : -value);
  }

  int EvaluationFunction::piece_material_value(Piece piece) const
  { return _M_piece_material[piece_to_index(piece)]; }

  int EvaluationFunction::promotion_piece_material_value(PromotionPiece piece) const
  { return _M_piece_material[promotion_piece_to_index(piece)]; }
}
