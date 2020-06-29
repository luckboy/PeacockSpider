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
#ifndef _THINKER_TESTS_HPP
#define _THINKER_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "search.hpp"

namespace peacockspider
{
  namespace test
  {
    class ThinkerTests : public CppUnit::TestFixture
    {
      CPPUNIT_TEST_SUITE(ThinkerTests);
      CPPUNIT_TEST(test_thinker_thinks);
      CPPUNIT_TEST(test_thinker_ponders);
      CPPUNIT_TEST(test_thinker_thinks_after_pondering_with_move_hitting);
      CPPUNIT_TEST(test_thinker_thinks_after_pondering_without_move_hitting);
      CPPUNIT_TEST(test_thinker_ponders_without_pondering_move);
      CPPUNIT_TEST_SUITE_END();

      EvaluationFunction *_M_evaluation_function;
      Searcher *_M_searcher;
      Thinker *_M_thinker;
    public:
      void setUp();

      void tearDown();

      void test_thinker_thinks();
      void test_thinker_ponders();
      void test_thinker_thinks_after_pondering_with_move_hitting();
      void test_thinker_thinks_after_pondering_without_move_hitting();
      void test_thinker_ponders_without_pondering_move();
    };
  }
}

#endif
