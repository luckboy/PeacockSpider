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

using namespace std;

namespace peacockspider
{
  EvaluationFunction::EvaluationFunction(const EvaluationFunctionParameters &params)
  {
    // Not implemented.
  }

  int EvaluationFunction::operator()(const Board &board) const
  {
    // Not implemented.
    return 0;
  }

  int EvaluationFunction::material_piece_value(Piece piece) const
  {
    // Not implemented.
    return 0;
  }

  int EvaluationFunction::meterial_promotion_piece_value(PromotionPiece piece) const
  {
    // Not implemented.
    return 0;
  }
}
