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
#include "gen_alg_vars.hpp"

namespace peacockspider
{
  namespace genalg
  {
    Range default_gene_ranges[MAX_EVALUATION_PARAMETER_COUNT] = {
      Range(100, 400),    // EVALUATION_PARAMETER_KNIGHT_MATERIAL
      Range(100, 400),    // EVALUATION_PARAMETER_BISHOP_MATERIAL
      Range(400, 700),    // EVALUATION_PARAMETER_ROOK_MATERIAL
      Range(700, 1200),   // EVALUATION_PARAMETER_QUEEN_MATERIAL
      Range(0, 40),       // EVALUATION_PARAMETER_PAWN_ADVANCE
      Range(0, 20),       // EVALUATION_PARAMETER_PAWN_CENTER
      Range(0, 20),       // EVALUATION_PARAMETER_KNIGHT_CENTER
      Range(0, 20),       // EVALUATION_PARAMETER_BISHOP_CENTER
      Range(0, 10),       // EVALUATION_PARAMETER_ROOK_CENTER
      Range(0, 20),       // EVALUATION_PARAMETER_ROOK_CASTLING
      Range(0, 10),       // EVALUATION_PARAMETER_QUEEN_CENTER
      Range(-100, 0),     // EVALUATION_PARAMETER_KING_UNSAFETY
      Range(0, 20),       // EVALUATION_PARAMETER_KING_CASTLING
      Range(0, 20),       // EVALUATION_PARAMETER_KING_CENTER
      Range(2000, 4000),  // EVALUATION_PARAMETER_ENDGAME_MATERIAL
      Range(-40, 0),      // EVALUATION_PARAMETER_ISOLATED_PAWN
      Range(-40, 0),      // EVALUATION_PARAMETER_DOUBLED_PAWN
      Range(0, 10),       // EVALUATION_PARAMETER_PAWN_MOBILITY
      Range(0, 10),       // EVALUATION_PARAMETER_KNIGHT_MOBILITY
      Range(0, 10),       // EVALUATION_PARAMETER_BISHOP_MOBILITY
      Range(0, 10),       // EVALUATION_PARAMETER_ROOK_MOBILITY
      Range(0, 10),       // EVALUATION_PARAMETER_QUEEN_MOBILITY
      Range(0, 10),       // EVALUATION_PARAMETER_KING_MOBILITY
      Range(0, 40),       // EVALUATION_PARAMETER_PAWN_DEFENCE
      Range(0, 40),       // EVALUATION_PARAMETER_KNIGHT_DEFENCE
      Range(0, 40),       // EVALUATION_PARAMETER_BISHOP_DEFENCE
      Range(0, 40),       // EVALUATION_PARAMETER_ROOK_DEFENCE
      Range(0, 40),       // EVALUATION_PARAMETER_QUEEN_DEFENCE
      Range(-210, 0),     // EVALUATION_PARAMETER_QUEEN_KING_PIN
      Range(-160, 0),     // EVALUATION_PARAMETER_ROOK_KING_PIN
      Range(-130, 0),     // EVALUATION_PARAMETER_BISHOP_KING_PIN
      Range(-130, 0),     // EVALUATION_PARAMETER_KNIGHT_KING_PIN
      Range(-100, 0),     // EVALUATION_PARAMETER_PAWN_KING_PIN
      Range(-150, 0),     // EVALUATION_PARAMETER_ROOK_QUEEN_PIN
      Range(-120, 0),     // EVALUATION_PARAMETER_BISHOP_QUEEN_PIN
      Range(-120, 0),     // EVALUATION_PARAMETER_KNIGHT_QUEEN_PIN
      Range(-90, 0),      // EVALUATION_PARAMETER_PAWN_QUEEN_PIN
      Range(-80, 0),      // EVALUATION_PARAMETER_BISHOP_ROOK_PIN
      Range(-80, 0),      // EVALUATION_PARAMETER_KNIGHT_ROOK_PIN
      Range(-50, 0),      // EVALUATION_PARAMETER_PAWN_ROOK_PIN
      Range(-30, 0),      // EVALUATION_PARAMETER_PAWN_BISHOP_PIN
      Range(-30, 0)       // EVALUATION_PARAMETER_PAWN_KNIGHT_PIN
    };
  }
}
