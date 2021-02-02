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
#ifndef _EVAL_HPP
#define _EVAL_HPP

#include <ios>
#include <istream>
#include <ostream>
#include "chess.hpp"

namespace peacockspider
{
  const std::size_t EVALUATION_PARAMETER_KNIGHT_MATERIAL =    0;
  const std::size_t EVALUATION_PARAMETER_BISHOP_MATERIAL =    1;
  const std::size_t EVALUATION_PARAMETER_ROOK_MATERIAL =      2;
  const std::size_t EVALUATION_PARAMETER_QUEEN_MATERIAL =     3;
  const std::size_t EVALUATION_PARAMETER_PAWN_ADVANCE =       4;
  const std::size_t EVALUATION_PARAMETER_PAWN_CENTER =        5;
  const std::size_t EVALUATION_PARAMETER_KNIGHT_CENTER =      6;
  const std::size_t EVALUATION_PARAMETER_BISHOP_CENTER =      7;
  const std::size_t EVALUATION_PARAMETER_ROOK_CENTER =        8;
  const std::size_t EVALUATION_PARAMETER_ROOK_CASTLING =      9;
  const std::size_t EVALUATION_PARAMETER_QUEEN_CENTER =       10;
  const std::size_t EVALUATION_PARAMETER_KING_UNSAFETY =      11;
  const std::size_t EVALUATION_PARAMETER_KING_CASTLING =      12;
  const std::size_t EVALUATION_PARAMETER_KING_CENTER =        13;
  const std::size_t EVALUATION_PARAMETER_ENDGAME_MATERIAL =   14;
  const std::size_t EVALUATION_PARAMETER_ISOLATED_PAWN =      15;
  const std::size_t EVALUATION_PARAMETER_DOUBLED_PAWN =       16;
  const std::size_t MAX_EVALUATION_PARAMETER_COUNT =          17;

  extern int default_evaluation_parameters[MAX_EVALUATION_PARAMETER_COUNT];
  extern int start_evaluation_parameters[MAX_EVALUATION_PARAMETER_COUNT];
  
  extern const char *evaluation_parameter_names[MAX_EVALUATION_PARAMETER_COUNT];

  struct EvaluationParameterFormat
  {
    std::size_t max_count;
    const char **names;
    
    EvaluationParameterFormat() {}
    
    EvaluationParameterFormat(std::size_t max_count, const char **names) :
      max_count(max_count), names(names) {}
  };

  const std::size_t MAX_OLD_EVALUATION_PARAMETER_FORMAT_COUNT = 2;

  extern EvaluationParameterFormat old_evaluation_parameter_formats[MAX_OLD_EVALUATION_PARAMETER_FORMAT_COUNT];
  
  struct ParentPair
  {
    int first_parent;
    int second_parent;
    
    ParentPair() {}
    
    ParentPair(int first_parent, int second_parent) :
      first_parent(first_parent), second_parent(second_parent) {}
  };

  class EvaluationFunction
  {
    int _M_piece_material[6];
    int _M_piece_square[2][6][64];
    int _M_king_square[2][64];
    int _M_king_square_for_endgame[64];
    int _M_endgame_material;
    int _M_isolated_pawn;
    int _M_doubled_pawn;
    int _M_piece_square_bits[2][6][16][16];
  public:
    EvaluationFunction()
    { set(default_evaluation_parameters); }
    
    EvaluationFunction(const int *params)
    { set(params); }
    
    void set(const int *params);

    int operator()(const Board &board) const;

    int piece_material_value(Piece piece) const;
    
    int promotion_piece_material_value(PromotionPiece piece) const;
  };

  std::istream &read_evaluation_parameters(std::istream &is, ParentPair *parent_pair, int *params, std::size_t param_count = MAX_EVALUATION_PARAMETER_COUNT);

  std::ostream &write_evaluation_parameters(std::ostream &os, const ParentPair &parent_pair, const int *params, std::size_t param_count = MAX_EVALUATION_PARAMETER_COUNT);

  std::istream &skip_evaluation_parameters(std::istream &is, std::streamoff count, std::size_t param_count = MAX_EVALUATION_PARAMETER_COUNT);
  
  std::ostream &write_default_evaluation_parameters(std::ostream &os, const int *params, const char **param_names = evaluation_parameter_names, std::size_t param_count = MAX_EVALUATION_PARAMETER_COUNT);
}

#endif
