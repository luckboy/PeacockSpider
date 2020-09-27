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
    Tournament::Tournament(int player_count) :
      _M_result(player_count), _M_tournament_output_function([](int iter, int player1, int player2, int match_game_index, Result result) {}) {}
  
    Tournament::~Tournament() {}
  
    function<void (int, int, int, int, Result)> Tournament::tournament_output_function() const
    { return _M_tournament_output_function; }

    void Tournament::set_tournament_output_function(function<void (int, int, int, int, Result)> fun)
    { _M_tournament_output_function = fun; }
  }
}

