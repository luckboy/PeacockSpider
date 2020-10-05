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
#ifndef _TEST_TABLE_HPP
#define _TEST_TABLE_HPP

#include "tournament.hpp"

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      struct TestTableResults
      {
        std::string start;
        std::vector<std::string> game_results;
      };

      class TestTable : public Table
      {
        const TestTableResults &_M_results;
      public:
        TestTable(const TestTableResults &results) :
          _M_results(results) {}

        virtual ~TestTable();

        virtual bool start_tournament(int iter);

        virtual std::pair<Result, bool> play(int iter, int round, int player1, int *params1, int player2, int *params2);
      };
    }
  }
}

#endif
