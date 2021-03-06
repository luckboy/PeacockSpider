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
#include "single_pvs_searcher_with_tt_tests.hpp"

using namespace std;

namespace peacockspider
{
  namespace test
  {
    CPPUNIT_TEST_SUITE_REGISTRATION(SinglePVSSearcherWithTTTests);

    void SinglePVSSearcherWithTTTests::setUp()
    {
      _M_evaluation_function = new EvaluationFunction(start_evaluation_parameters);
      _M_transposition_table = new TranspositionTable(65536);
      _M_searcher = new SinglePVSSearcherWithTT(_M_evaluation_function, _M_transposition_table);
    }

    void SinglePVSSearcherWithTTTests::tearDown()
    {
      delete _M_searcher;
      delete _M_transposition_table;
      delete _M_evaluation_function;
    }
  }
}
