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
#include "eval.hpp"

namespace peacockspider
{
  int default_evaluation_parameters[MAX_EVALUATION_PARAMETER_COUNT] = {
    300,  // EVALUATION_PARAMETER_KNIGHT_MATERIAL
    300,  // EVALUATION_PARAMETER_BISHOP_MATERIAL
    500,  // EVALUATION_PARAMETER_ROOK_MATERIAL
    900,  // EVALUATION_PARAMETER_QUEEN_MATERIAL
    5,    // EVALUATION_PARAMETER_PAWN_ADVANCE
    2,    // EVALUATION_PARAMETER_PAWN_CENTER
    5,    // EVALUATION_PARAMETER_KNIGHT_CENTER
    5,    // EVALUATION_PARAMETER_BISHOP_CENTER
    0,    // EVALUATION_PARAMETER_ROOK_CENTER
    10,   // EVALUATION_PARAMETER_ROOK_CASTLING
    0,    // EVALUATION_PARAMETER_QUEEN_CENTER
    -50,  // EVALUATION_PARAMETER_KING_UNSAFETY
    10,   // EVALUATION_PARAMETER_KING_CASTLING
    5,    // EVALUATION_PARAMETER_KING_CENTER
    2800, // EVALUATION_PARAMETER_ENDGAME_MATERIAL
    -10,  // EVALUATION_PARAMETER_ISOLATED_PAWN
    -10,  // EVALUATION_PARAMETER_DOUBLED_PAWN
    2,    // EVALUATION_PARAMETER_PAWN_MOBILITY
    3,    // EVALUATION_PARAMETER_KNIGHT_MOBILITY
    2,    // EVALUATION_PARAMETER_BISHOP_MOBILITY
    2,    // EVALUATION_PARAMETER_ROOK_MOBILITY
    2,    // EVALUATION_PARAMETER_QUEEN_MOBILITY
    1,    // EVALUATION_PARAMETER_KING_MOBILITY
    2,    // EVALUATION_PARAMETER_PAWN_DEFENCE
    2,    // EVALUATION_PARAMETER_KNIGHT_DEFENCE
    2,    // EVALUATION_PARAMETER_BISHOP_DEFENCE
    2,    // EVALUATION_PARAMETER_ROOK_DEFENCE
    2    // EVALUATION_PARAMETER_QUEEN_DEFENCE
  };
}

