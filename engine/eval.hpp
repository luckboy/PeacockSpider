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
#ifndef _EVAL_HPP
#define _EVAL_HPP

#include "chess.hpp"

namespace peacockspider
{
  struct EvaluationFunctionParameters
  {
    int x;
  };

  class EvaluationFunction
  {
  public:
    EvaluationFunction(const EvaluationFunctionParameters &params);

    int operator()(const Board &board) const;

    int piece_material_value(Piece piece) const;
    
    int promotion_piece_material_value(PromotionPiece piece) const;
  };
}

#endif
