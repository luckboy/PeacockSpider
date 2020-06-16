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
#ifndef _SEARCHER_TESTS_HPP
#define _SEARCHER_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "search.hpp"

namespace peacockspider
{
  namespace test
  {
    class SearcherTests : public CppUnit::TestFixture
    {
      CPPUNIT_TEST_SUITE(SearcherTests);
      CPPUNIT_TEST(test_searcher_finds_best_move_for_initial_board);
      CPPUNIT_TEST(test_searcher_finds_best_move_for_white_side_and_pieces);
      CPPUNIT_TEST(test_searcher_finds_best_move_for_black_side_and_pieces);
      CPPUNIT_TEST(test_searcher_finds_best_move_for_white_side_and_endgame);
      CPPUNIT_TEST(test_searcher_finds_best_move_for_black_side_and_endgame);
      CPPUNIT_TEST_SUITE_END();
    protected:
      EvaluationFunction *_M_evaluation_function;
      Searcher *_M_searcher;
    public:
      void test_searcher_finds_best_move_for_initial_board();
      void test_searcher_finds_best_move_for_white_side_and_pieces();
      void test_searcher_finds_best_move_for_black_side_and_pieces();
      void test_searcher_finds_best_move_for_white_side_and_endgame();
      void test_searcher_finds_best_move_for_black_side_and_endgame();
    };
  }
}

#endif
