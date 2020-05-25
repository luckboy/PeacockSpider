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
#ifndef _SAN_MOVE_TESTS_HPP
#define _SAN_MOVE_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

namespace peacockspider
{
  namespace test
  {
    class SANMoveTests : public CppUnit::TestFixture
    {
      CPPUNIT_TEST_SUITE(SANMoveTests);
      CPPUNIT_TEST(test_san_move_set_method_sets_move);
      CPPUNIT_TEST(test_san_move_set_method_sets_move_with_piece);
      CPPUNIT_TEST(test_san_move_set_method_sets_move_with_source_column);
      CPPUNIT_TEST(test_san_move_set_method_sets_move_with_source_row);
      CPPUNIT_TEST(test_san_move_set_method_sets_move_with_source_square);
      CPPUNIT_TEST(test_san_move_set_method_sets_capture_with_piece);
      CPPUNIT_TEST(test_san_move_set_method_sets_capture_with_source_column);
      CPPUNIT_TEST(test_san_move_set_method_sets_capture_with_source_row);
      CPPUNIT_TEST(test_san_move_set_method_sets_capture_with_source_square);
      CPPUNIT_TEST(test_san_move_set_method_sets_move_with_promotion_piece);
      CPPUNIT_TEST(test_san_move_set_method_sets_capture_with_promotion_piece);
      CPPUNIT_TEST(test_san_move_set_method_sets_move_with_promotion_piece_and_eqaul_character);
      CPPUNIT_TEST(test_san_move_set_method_sets_short_castling);
      CPPUNIT_TEST(test_san_move_set_method_sets_long_castling);
      CPPUNIT_TEST(test_san_move_set_method_sets_move_with_check);
      CPPUNIT_TEST(test_san_move_set_method_sets_capture_with_check);
      CPPUNIT_TEST(test_san_move_set_method_sets_move_with_promotion_piece_and_check);
      CPPUNIT_TEST(test_san_move_set_method_sets_castling_with_check);
      CPPUNIT_TEST(test_san_move_set_method_sets_move_with_checkmate);
      CPPUNIT_TEST(test_san_move_set_method_sets_capture_with_checkmate);
      CPPUNIT_TEST(test_san_move_set_method_sets_move_with_promotion_piece_and_checkmate);
      CPPUNIT_TEST(test_san_move_set_method_sets_castling_with_checkmate);
      CPPUNIT_TEST(test_san_move_set_method_sets_move_with_question_mark_and_exclamation_mark);
      CPPUNIT_TEST(test_san_move_set_method_sets_move_with_check_and_exclamation_marks);
      CPPUNIT_TEST(test_san_move_set_method_complains_on_incorrect_piece);
      CPPUNIT_TEST(test_san_move_set_method_complains_on_incorrect_source_column_or_incorrect_source_row);
      CPPUNIT_TEST(test_san_move_set_method_complains_on_incorrect_destination_square);
      CPPUNIT_TEST(test_san_move_set_method_complains_on_move_without_promotion_piece_with_equal_character);
      CPPUNIT_TEST(test_san_move_set_method_complains_on_incorrect_promotion_piece);
      CPPUNIT_TEST(test_san_move_set_method_complains_on_incorrect_flag);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_move_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_move_with_piece_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_move_with_source_column_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_move_with_source_row_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_move_with_source_square_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_capture_with_piece_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_capture_with_source_column_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_capture_with_source_row_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_capture_with_source_square_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_move_with_promotion_piece_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_capture_with_promotion_piece_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_short_castling_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_long_castling_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_move_with_check_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_capture_with_check_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_move_with_promotion_piece_and_check_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_castling_with_check_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_move_with_checkmate_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_capture_with_checkmate_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_move_with_promotion_piece_and_checkmate_to_string);
      CPPUNIT_TEST(test_san_move_to_string_method_converts_castling_with_checkmate_to_string);
      CPPUNIT_TEST_SUITE_END();
    public:
      void setUp();

      void tearDown();

      void test_san_move_set_method_sets_move();
      void test_san_move_set_method_sets_move_with_piece();
      void test_san_move_set_method_sets_move_with_source_column();
      void test_san_move_set_method_sets_move_with_source_row();
      void test_san_move_set_method_sets_move_with_source_square();
      void test_san_move_set_method_sets_capture_with_piece();
      void test_san_move_set_method_sets_capture_with_source_column();
      void test_san_move_set_method_sets_capture_with_source_row();
      void test_san_move_set_method_sets_capture_with_source_square();
      void test_san_move_set_method_sets_move_with_promotion_piece();
      void test_san_move_set_method_sets_capture_with_promotion_piece();
      void test_san_move_set_method_sets_move_with_promotion_piece_and_eqaul_character();
      void test_san_move_set_method_sets_short_castling();
      void test_san_move_set_method_sets_long_castling();
      void test_san_move_set_method_sets_move_with_check();
      void test_san_move_set_method_sets_capture_with_check();
      void test_san_move_set_method_sets_move_with_promotion_piece_and_check();
      void test_san_move_set_method_sets_castling_with_check();
      void test_san_move_set_method_sets_move_with_checkmate();
      void test_san_move_set_method_sets_capture_with_checkmate();
      void test_san_move_set_method_sets_move_with_promotion_piece_and_checkmate();
      void test_san_move_set_method_sets_castling_with_checkmate();
      void test_san_move_set_method_sets_move_with_question_mark_and_exclamation_mark();
      void test_san_move_set_method_sets_move_with_check_and_exclamation_marks();
      void test_san_move_set_method_complains_on_incorrect_piece();
      void test_san_move_set_method_complains_on_incorrect_source_column_or_incorrect_source_row();
      void test_san_move_set_method_complains_on_incorrect_destination_square();
      void test_san_move_set_method_complains_on_move_without_promotion_piece_with_equal_character();
      void test_san_move_set_method_complains_on_incorrect_promotion_piece();
      void test_san_move_set_method_complains_on_incorrect_flag();
      void test_san_move_to_string_method_converts_move_to_string();
      void test_san_move_to_string_method_converts_move_with_piece_to_string();
      void test_san_move_to_string_method_converts_move_with_source_column_to_string();
      void test_san_move_to_string_method_converts_move_with_source_row_to_string();
      void test_san_move_to_string_method_converts_move_with_source_square_to_string();
      void test_san_move_to_string_method_converts_capture_with_piece_to_string();
      void test_san_move_to_string_method_converts_capture_with_source_column_to_string();
      void test_san_move_to_string_method_converts_capture_with_source_row_to_string();
      void test_san_move_to_string_method_converts_capture_with_source_square_to_string();
      void test_san_move_to_string_method_converts_move_with_promotion_piece_to_string();
      void test_san_move_to_string_method_converts_capture_with_promotion_piece_to_string();
      void test_san_move_to_string_method_converts_short_castling_to_string();
      void test_san_move_to_string_method_converts_long_castling_to_string();
      void test_san_move_to_string_method_converts_move_with_check_to_string();
      void test_san_move_to_string_method_converts_capture_with_check_to_string();
      void test_san_move_to_string_method_converts_move_with_promotion_piece_and_check_to_string();
      void test_san_move_to_string_method_converts_castling_with_check_to_string();
      void test_san_move_to_string_method_converts_move_with_checkmate_to_string();
      void test_san_move_to_string_method_converts_capture_with_checkmate_to_string();
      void test_san_move_to_string_method_converts_move_with_promotion_piece_and_checkmate_to_string();
      void test_san_move_to_string_method_converts_castling_with_checkmate_to_string();
    };
  }
}

#endif
