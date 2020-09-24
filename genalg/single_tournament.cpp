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
#include "tournament.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    SingleTournament::SingleTournament(size_t player_count, function<Table *()> fun) :
      Tournament(player_count), _M_table(fun()) {}

    SingleTournament::~SingleTournament() {}

    const TournamentResult &SingleTournament::play(int iter, const vector<unique_ptr<int []>> &param_list)
    {
      _M_table->start_tournament(iter);
      int round = 1;
      _M_result.clear();
      for(size_t player1 = 0; player1 < _M_result.player_count(); player1++) {
        for(size_t player2 = player1 + 1; player2 < _M_result.player_count(); player2++) {
          for(size_t match_game_index = 0; match_game_index < 2; match_game_index++) { 
            play_match_game(_M_table.get(), iter, round, player1, param_list[player1].get(), player2, param_list[player2].get(), match_game_index);
            round++;
          }
        }
      }
      _M_result.sort_player_indices();
      return _M_result;
    }
  }
}
