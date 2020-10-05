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
#include "test_table.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      TestTable::~TestTable() {}

      bool TestTable::start_tournament(int iter)
      { return (_M_results.start != string("e")); }

      pair<Result, bool> TestTable::play(int iter, int round, int player1, int *params1, int player2, int *params2)
      {
        switch(_M_results.game_results[player1][player2 * 2 + 1]) {
          case '1':
            return make_pair(Result::WHITE_WIN, true);
          case '0':
            return make_pair(Result::BLACK_WIN, true);
          case 'e':
            return make_pair(Result::DRAW, false);
          default:
            return make_pair(Result::DRAW, true);
        }
      }
    }
  }
}
