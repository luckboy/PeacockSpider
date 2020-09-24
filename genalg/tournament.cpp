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
    Tournament::Tournament(size_t player_count) :
      _M_result(player_count), _M_tournament_output_function([](int iter, size_t player1, size_t player2, size_t match_game_index, Result result) {}) {}
  
    Tournament::~Tournament() {}
  
    function<void (int, size_t, size_t, size_t, Result)> Tournament::tournament_output_function() const
    { return _M_tournament_output_function; }

    void Tournament::set_tournament_output_function(function<void (int, size_t, size_t, size_t, Result)> fun)
    { _M_tournament_output_function = fun; }

    pair<Result, bool> Tournament::play_match_game(Table *table, int iter, int round, size_t player1, int *params1, size_t player2, int *params2, std::size_t match_game_index)
    {
      if(match_game_index == 0) {
        pair<Result, bool> result_pair = table->play(iter, round, player1, params1, player2, params2);
        if(!result_pair.second) return result_pair;
        _M_result.set_game_result(player1, player2, match_game_index, result_pair.first);
        return result_pair; 
      } else {
        pair<Result, bool> result_pair = table->play(iter, round, player2, params2, player1, params1);
        if(!result_pair.second) return result_pair;
        _M_result.set_game_result(player1, player2, match_game_index, result_pair.first);
        return result_pair;
      }
    }
  }
}

