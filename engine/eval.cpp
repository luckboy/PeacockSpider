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
#include <sstream>
#include "eval.hpp"

using namespace std;

namespace peacockspider
{
  const char *evaluation_parameter_names[MAX_EVALUATION_PARAMETER_COUNT] = {
    "EVALUATION_PARAMETER_KNIGHT_MATERIAL",
    "EVALUATION_PARAMETER_BISHOP_MATERIAL",
    "EVALUATION_PARAMETER_ROOK_MATERIAL",
    "EVALUATION_PARAMETER_QUEEN_MATERIAL",
    "EVALUATION_PARAMETER_PAWN_ADVANCE",
    "EVALUATION_PARAMETER_PAWN_CENTER",
    "EVALUATION_PARAMETER_KNIGHT_CENTER",
    "EVALUATION_PARAMETER_BISHOP_CENTER",
    "EVALUATION_PARAMETER_ROOK_CENTER",
    "EVALUATION_PARAMETER_ROOK_CASTLING",
    "EVALUATION_PARAMETER_QUEEN_CENTER",
    "EVALUATION_PARAMETER_KING_UNSAFETY",
    "EVALUATION_PARAMETER_KING_CASTLING",
    "EVALUATION_PARAMETER_KING_CENTER",
    "EVALUATION_PARAMETER_ENDGAME_MATERIAL",
    "EVALUATION_PARAMETER_ISOLATED_PAWN",
    "EVALUATION_PARAMETER_DOUBLED_PAWN",
    "EVALUATION_PARAMETER_PAWN_MOBILITY",
    "EVALUATION_PARAMETER_KNIGHT_MOBILITY",
    "EVALUATION_PARAMETER_BISHOP_MOBILITY",
    "EVALUATION_PARAMETER_ROOK_MOBILITY",
    "EVALUATION_PARAMETER_QUEEN_MOBILITY",
    "EVALUATION_PARAMETER_KING_MOBILITY",
    "EVALUATION_PARAMETER_PAWN_DEFENCE",
    "EVALUATION_PARAMETER_KNIGHT_DEFENCE",
    "EVALUATION_PARAMETER_BISHOP_DEFENCE",
    "EVALUATION_PARAMETER_ROOK_DEFENCE",
    "EVALUATION_PARAMETER_QUEEN_DEFENCE",
    "EVALUATION_PARAMETER_QUEEN_KING_PIN",
    "EVALUATION_PARAMETER_ROOK_KING_PIN",
    "EVALUATION_PARAMETER_BISHOP_KING_PIN",
    "EVALUATION_PARAMETER_KNIGHT_KING_PIN",
    "EVALUATION_PARAMETER_PAWN_KING_PIN",
    "EVALUATION_PARAMETER_ROOK_QUEEN_PIN",
    "EVALUATION_PARAMETER_BISHOP_QUEEN_PIN",
    "EVALUATION_PARAMETER_KNIGHT_QUEEN_PIN",
    "EVALUATION_PARAMETER_PAWN_QUEEN_PIN",
    "EVALUATION_PARAMETER_BISHOP_ROOK_PIN",
    "EVALUATION_PARAMETER_KNIGHT_ROOK_PIN",
    "EVALUATION_PARAMETER_PAWN_ROOK_PIN",
    "EVALUATION_PARAMETER_PAWN_BISHOP_PIN",
    "EVALUATION_PARAMETER_PAWN_KNIGHT_PIN"
  };
  
  istream &read_evaluation_parameters(istream &is, ParentPair *parent_pair, int *params, size_t param_count)
  {
    int first_parent, second_parent;
    is >> first_parent;
    if(is.fail()) return is;
    is >> second_parent;
    if(is.fail()) return is;
    if(parent_pair != nullptr) {
      parent_pair->first_parent = first_parent;
      parent_pair->second_parent = second_parent;
    }
    for(size_t i = 0; i < param_count; i++) {
      int param;
      is >> param;
      if(is.fail()) return is;
      if(params != nullptr) params[i] = param;
    }
    return is;
  }

  ostream &write_evaluation_parameters(ostream &os, const ParentPair &parent_pair, const int *params, size_t param_count)
  {
    os << parent_pair.first_parent << " " << parent_pair.second_parent << "\n";
    for(size_t i = 0; i < param_count; i++) {
      os << params[i] << "\n";
    }
    os << "\n";
    return os;
  }

  istream &skip_evaluation_parameters(istream &is, streamoff count, size_t param_count)
  {
    for(streamoff i = 0; i < count; i++) {
      read_evaluation_parameters(is, nullptr, nullptr, param_count);
      if(is.fail()) return is;
    }
    return is;
  }

  ostream &write_default_evaluation_parameters(ostream &os, const int *params, const char **param_names, size_t param_count)
  {
    os << "// THIS FILE IS GENERATED.\n";
    os << "#include \"eval.hpp\"\n";
    os << "\n";
    os << "namespace peacockspider\n";
    os << "{\n";
    os << "  int default_evaluation_parameters[MAX_EVALUATION_PARAMETER_COUNT] = {\n";
    for(size_t i = 0; i < param_count; i++) {
      ostringstream oss;
      oss << params[i];
      string str = oss.str() + (i + 1 < param_count ? "," : "");
      os << "    " << str;
      for(int j = 0; j < 6 - static_cast<int>(str.length()); j++) {
        os << " ";
      }
      os << "// " << param_names[i] << "\n";
    }
    os << "  };\n";
    os << "}\n";
    return os;
  }
}
