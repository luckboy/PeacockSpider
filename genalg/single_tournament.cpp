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
    SingleTournament::SingleTournament(int player_count, function<Table *()> fun) :
      Tournament(player_count), _M_table(fun()) {}

    SingleTournament::~SingleTournament() {}

    bool SingleTournament::play(int iter, const vector<shared_ptr<int []>> &param_arrays)
    {
      if(!_M_table->start_tournament(iter)) return false;
      int round = 1;
      _M_result.clear();
      for(int player1 = 0; player1 < _M_result.player_count(); player1++) {
        for(int player2 = player1 + 1; player2 < _M_result.player_count(); player2++) {
          for(int match_game_index = 0; match_game_index < 2; match_game_index++) { 
            pair<Result, bool> result_pair;
            if(match_game_index == 0) 
              result_pair = _M_table->play(iter, round, player1, param_arrays[player1].get(), player2, param_arrays[player2].get());
            else
              result_pair = _M_table->play(iter, round, player2, param_arrays[player2].get(), player1, param_arrays[player1].get());
            if(!result_pair.second) return false;
            _M_result.set_game_result(player1, player2, match_game_index, result_pair.first);
            _M_tournament_output_function(iter, player1, player2, match_game_index, result_pair.first);
            round++;
          }
        }
      }
      _M_result.sort_player_indices();
      return true;
    }
  }
}
