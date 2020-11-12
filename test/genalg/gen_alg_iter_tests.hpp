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
#ifndef _SELECTOR_TESTS_HPP
#define _SELECTOR_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "fitness.hpp"
#include "gen_alg.hpp"
#include "test_table.hpp"
#include "tournament.hpp"

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      class GeneticAlgorithmIterationTests : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(GeneticAlgorithmIterationTests);
        CPPUNIT_TEST(test_genetic_algorithm_iterate_function_iterates);
        CPPUNIT_TEST(test_genetic_algorithm_iterate_function_does_not_iterate_for_error);
        CPPUNIT_TEST_SUITE_END();
      protected:
        TestTableResults *_M_results;
        Tournament *_M_tournament;
        FitnessFunction *_M_fitness_function;
        Selector *_M_selector;
      public:
        void setUp();

        void tearDown();

        void test_genetic_algorithm_iterate_function_iterates();
        void test_genetic_algorithm_iterate_function_does_not_iterate_for_error();
      };
    }
  }
}

#endif
