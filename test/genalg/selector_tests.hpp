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
      class SelectorTests : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(SelectorTests);
        CPPUNIT_TEST(test_selector_selects_best_individual_for_empty_excluded_index_set);
        CPPUNIT_TEST(test_selector_selects_best_individual_for_excluded_index_set);
        CPPUNIT_TEST(test_selector_does_not_select_best_individual_for_full_excluded_index_set);
        CPPUNIT_TEST(test_selector_selects_individual_for_empty_excluded_index_set);
        CPPUNIT_TEST(test_selector_selects_individual_for_excluded_index_set);
        CPPUNIT_TEST(test_selector_does_not_select_individual_for_full_excluded_index_set);
        CPPUNIT_TEST(test_selector_selects_best_individuals);
        CPPUNIT_TEST(test_selector_does_not_select_best_individuals_for_best_individuals_greater_than_population);
        CPPUNIT_TEST(test_selector_selects_parents_for_even_number_of_children);
        CPPUNIT_TEST(test_selector_selects_parents_for_odd_number_of_children);
        CPPUNIT_TEST_SUITE_END();
      protected:
        TestTableResults *_M_results;
        Tournament *_M_tournament;
        FitnessFunction *_M_fitness_function;
        Selector *_M_selector;
      public:
        void test_selector_selects_best_individual_for_empty_excluded_index_set();
        void test_selector_selects_best_individual_for_excluded_index_set();
        void test_selector_does_not_select_best_individual_for_full_excluded_index_set();
        void test_selector_selects_individual_for_empty_excluded_index_set();
        void test_selector_selects_individual_for_excluded_index_set();
        void test_selector_does_not_select_individual_for_full_excluded_index_set();
        void test_selector_selects_best_individuals();
        void test_selector_does_not_select_best_individuals_for_best_individuals_greater_than_population();
        void test_selector_selects_parents_for_even_number_of_children();
        void test_selector_selects_parents_for_odd_number_of_children();
      };
    }
  }
}

#endif
