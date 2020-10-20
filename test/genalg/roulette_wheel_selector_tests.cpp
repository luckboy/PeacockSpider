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
#include "roulette_wheel_selector_tests.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      CPPUNIT_TEST_SUITE_REGISTRATION(RouletteWheelSelectorTests);

      void RouletteWheelSelectorTests::setUp()
      {
        _M_results = new TestTableResults;
        _M_tournament = new SingleTournament(6, [this]() {
          return new TestTable(*_M_results);
        });
        _M_fitness_function = new FitnessFunction(_M_tournament);
        _M_selector = new RouletteWheelSelector(_M_fitness_function);
      }

      void RouletteWheelSelectorTests::tearDown()
      {
        delete _M_selector;
        delete _M_fitness_function;
        delete _M_tournament;
        delete _M_results;
      }
    }
  }
}
