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
#ifndef _CHESS_TESTS_HPP
#define _CHESS_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

namespace peacockspider
{
  namespace test
  {
    class ChessTests : public CppUnit::TestFixture
    {
      CPPUNIT_TEST_SUITE(ChessTests);
      CPPUNIT_TEST(test_repetitions_function_returns_number_of_repetirions);
      CPPUNIT_TEST(test_repetitions_function_with_last_board_returns_number_of_repetirions_without_last_board);
      CPPUNIT_TEST(test_repetitions_function_with_last_board_returns_number_of_repetirions_with_last_board);
      CPPUNIT_TEST(test_fold_squares_function_folds_squares);
      CPPUNIT_TEST(test_fold_pawn_capture_squares_function_folds_squares_for_white_side);
      CPPUNIT_TEST(test_fold_pawn_capture_squares_function_folds_squares_for_black_side);
      CPPUNIT_TEST(test_fold_pawn_squares_function_folds_squares_for_white_side_and_start_square);
      CPPUNIT_TEST(test_fold_pawn_squares_function_folds_squares_for_black_side_and_start_square);
      CPPUNIT_TEST(test_fold_pawn_squares_function_folds_squares_for_white_side_and_non_start_square);
      CPPUNIT_TEST(test_fold_pawn_squares_function_folds_squares_for_black_side_and_non_start_square);
      CPPUNIT_TEST(test_fold_knight_squares_function_folds_squares);
      CPPUNIT_TEST(test_fold_king_squares_function_folds_squares);
      CPPUNIT_TEST(test_fold_bishop_slides_function_folds_slides);
      CPPUNIT_TEST(test_fold_rook_slides_function_folds_slides);
      CPPUNIT_TEST(test_fold_queen_slides_function_folds_slides);
      CPPUNIT_TEST_SUITE_END();
    public:
      void setUp();

      void tearDown();

      void test_repetitions_function_returns_number_of_repetirions();
      void test_repetitions_function_with_last_board_returns_number_of_repetirions_without_last_board();
      void test_repetitions_function_with_last_board_returns_number_of_repetirions_with_last_board();
      void test_fold_squares_function_folds_squares();
      void test_fold_pawn_capture_squares_function_folds_squares_for_white_side();
      void test_fold_pawn_capture_squares_function_folds_squares_for_black_side();
      void test_fold_pawn_squares_function_folds_squares_for_white_side_and_start_square();
      void test_fold_pawn_squares_function_folds_squares_for_black_side_and_start_square();
      void test_fold_pawn_squares_function_folds_squares_for_white_side_and_non_start_square();
      void test_fold_pawn_squares_function_folds_squares_for_black_side_and_non_start_square();
      void test_fold_knight_squares_function_folds_squares();
      void test_fold_king_squares_function_folds_squares();
      void test_fold_bishop_slides_function_folds_slides();
      void test_fold_rook_slides_function_folds_slides();
      void test_fold_queen_slides_function_folds_slides();
    };
  }
}

#endif
