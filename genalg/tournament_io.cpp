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
#include <iomanip>
#include "tournament.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    ostream &operator<<(ostream &os, const TournamentResult &result)
    {
      os << "   |    | score |";
      for(int i = 0; i < result.player_count(); i++) {
        os << " ";
        ios_base::fmtflags saved_flags = os.flags();
        streamsize saved_width = os.width();
        char saved_fill = os.fill();
        os << dec << setw(2) << setfill('0') << result.sorted_player_index(i);
        os.flags(saved_flags);
        os.width(saved_width);
        os.fill(saved_fill);
      }
      os << " |" << endl;
      os << "---+----+-------+";
      for(int i = 0; i < result.player_count(); i++) {
        os << "---";
      }
      os << "-+" << endl;
      for(int i = 0; i < result.player_count(); i++) {
        int j = result.sorted_player_index(i);
        ios_base::fmtflags saved_flags = os.flags();
        streamsize saved_width = os.width();
        char saved_fill = os.fill();
        os << dec << setw(2) << setfill(' ') << (i + 1);
        os << " | ";
        os << dec << setw(2) << setfill('0') << j;
        os << " | ";
        os << dec << setw(3) << setfill(' ') << (result.score(j) / 2);
        os << ".";
        os << dec << setw(1) << setfill('0') << ((result.score(j) % 2) * 5);
        os << " |";
        os.flags(saved_flags);
        os.width(saved_width);
        os.fill(saved_fill);
        for(int k = 0; k < result.player_count(); k++) {
          int l =  result.sorted_player_index(k);
          os << " ";
          if(j == l) {
            os << "XX";
          } else {
            for(int match_game_index = 0; match_game_index < 2; match_game_index++) {
              switch(result.crosstable_match_result(j, l).scores[match_game_index]) {
                case 2:
                  os << '1';
                  break;
                case 0:
                  os << '0';
                  break;
                default:
                  os << '=';
                  break;
              }
            }
          }
        }
        os << " |" << endl;
      }
      os << "---+----+-------+";
      for(int i = 0; i < result.player_count(); i++) {
        os << "---";
      }
      os << "-+" << endl;
      return os;
    }
  }
}
