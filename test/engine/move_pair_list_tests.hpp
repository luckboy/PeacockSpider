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
#ifndef _MOVE_PAIR_LIST_TESTS_HPP
#define _MOVE_PAIR_LIST_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

namespace peacockspider
{
  namespace test
  {
    class MovePairListTests : public CppUnit::TestFixture
    {
      CPPUNIT_TEST_SUITE(MovePairListTests);
      CPPUNIT_TEST(test_move_pair_list_select_sort_move_method_sorts_move_for_first_index);
      CPPUNIT_TEST(test_move_pair_list_select_sort_move_method_sorts_move_for_no_better);
      CPPUNIT_TEST(test_move_pair_list_select_sort_move_method_sorts_move_for_better);
      CPPUNIT_TEST(test_move_pair_list_select_sort_move_method_sorts_move_for_better_better);
      CPPUNIT_TEST_SUITE_END();
    public:
      void setUp();

      void tearDown();

      void test_move_pair_list_select_sort_move_method_sorts_move_for_first_index();
      void test_move_pair_list_select_sort_move_method_sorts_move_for_no_better();
      void test_move_pair_list_select_sort_move_method_sorts_move_for_better();
      void test_move_pair_list_select_sort_move_method_sorts_move_for_better_better();
    };
  }
}

#endif
