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
    class MoveTests : public CppUnit::TestFixture
    {
      CPPUNIT_TEST_SUITE(MoveTests);
      CPPUNIT_TEST(test_move_set_can_method_sets_move);
      CPPUNIT_TEST(test_move_set_can_method_sets_move_with_promotion_piece_for_knight);
      CPPUNIT_TEST(test_move_set_can_method_sets_move_with_promotion_piece_for_bishop);
      CPPUNIT_TEST(test_move_set_can_method_sets_move_with_promotion_piece_for_rook);
      CPPUNIT_TEST(test_move_set_can_method_sets_move_with_promotion_piece_for_queen);
      CPPUNIT_TEST(test_move_set_can_method_complains_on_non_existent_move_in_moves);
      CPPUNIT_TEST(test_move_set_can_method_complains_on_illegal_move);
      CPPUNIT_TEST(test_move_set_san_method_sets_move);
      CPPUNIT_TEST(test_move_set_san_method_sets_move_with_source_column);
      CPPUNIT_TEST(test_move_set_san_method_sets_move_with_source_row);
      CPPUNIT_TEST(test_move_set_san_method_sets_move_with_source_square);
      CPPUNIT_TEST(test_move_set_san_method_sets_move_with_promotion_piece_for_knight);
      CPPUNIT_TEST(test_move_set_san_method_sets_move_with_promotion_piece_for_bishop);
      CPPUNIT_TEST(test_move_set_san_method_sets_move_with_promotion_piece_for_rook);
      CPPUNIT_TEST(test_move_set_san_method_sets_move_with_promotion_piece_for_queen);
      CPPUNIT_TEST(test_move_set_san_method_sets_short_castling_for_white_side);
      CPPUNIT_TEST(test_move_set_san_method_sets_short_castling_for_black_side);
      CPPUNIT_TEST(test_move_set_san_method_sets_long_castling_for_white_side);
      CPPUNIT_TEST(test_move_set_san_method_sets_capture);
      CPPUNIT_TEST(test_move_set_san_method_sets_capture_for_white_side_and_en_passant);
      CPPUNIT_TEST(test_move_set_san_method_sets_capture_for_black_side_and_en_passant);
      CPPUNIT_TEST(test_move_set_san_method_sets_move_with_check);
      CPPUNIT_TEST(test_move_set_san_method_sets_move_with_checkmate);
      CPPUNIT_TEST(test_move_set_san_method_complains_on_non_existent_move_in_moves);
      CPPUNIT_TEST(test_move_set_san_method_complains_on_illegal_move);
      CPPUNIT_TEST(test_move_set_san_method_complains_on_ambiguous_move);
      CPPUNIT_TEST(test_move_set_san_method_complains_on_non_existent_short_castling_in_moves_for_white_side);
      CPPUNIT_TEST(test_move_set_san_method_complains_on_non_existent_short_castling_in_moves_for_black_side);
      CPPUNIT_TEST(test_move_set_san_method_complains_on_non_existent_long_castling_in_moves_for_white_side);
      CPPUNIT_TEST(test_move_set_san_method_complains_on_non_existent_long_castling_in_moves_for_black_side);
      CPPUNIT_TEST(test_move_set_san_method_complains_on_no_capture);
      CPPUNIT_TEST(test_move_set_san_method_complains_on_no_check);
      CPPUNIT_TEST(test_move_set_san_method_complains_on_no_checkmate);
      CPPUNIT_TEST(test_move_to_can_move_method_converts_move_to_can_move);
      CPPUNIT_TEST(test_move_to_can_move_method_converts_move_with_promotion_piece_to_can_move);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move_with_source_column);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move_with_source_row);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move_with_source_square);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move_with_source_row_for_three_pieces);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move_with_source_square_for_four_pieces);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move_with_source_column_for_different_columns_and_different_rows);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_pawn_capture_to_san_move_with_source_column);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move_with_promotion_piece_for_knight);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move_with_promotion_piece_for_bishop);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move_with_promotion_piece_for_rook);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move_with_promotion_piece_for_queen);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_short_castling_to_san_move_for_white_side);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_short_castling_to_san_move_for_black_side);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_long_castling_to_san_move_for_white_side);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_long_castling_to_san_move_for_black_side);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_capture_to_san_move);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_capture_to_san_move_for_white_side_and_en_passant);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_capture_to_san_move_for_black_side_and_en_passant);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move_with_check);
      CPPUNIT_TEST(test_move_to_san_move_method_converts_move_to_san_move_with_checkmate);
      CPPUNIT_TEST(test_move_to_san_move_method_does_not_set_flags_for_illegal_move);
      CPPUNIT_TEST_SUITE_END();
    public:
      void setUp();

      void tearDown();

      void test_move_set_can_method_sets_move();
      void test_move_set_can_method_sets_move_with_promotion_piece_for_knight();
      void test_move_set_can_method_sets_move_with_promotion_piece_for_bishop();
      void test_move_set_can_method_sets_move_with_promotion_piece_for_rook();
      void test_move_set_can_method_sets_move_with_promotion_piece_for_queen();
      void test_move_set_can_method_complains_on_non_existent_move_in_moves();
      void test_move_set_can_method_complains_on_illegal_move();
      void test_move_set_san_method_sets_move();
      void test_move_set_san_method_sets_move_with_source_column();
      void test_move_set_san_method_sets_move_with_source_row();
      void test_move_set_san_method_sets_move_with_source_square();
      void test_move_set_san_method_sets_move_with_promotion_piece_for_knight();
      void test_move_set_san_method_sets_move_with_promotion_piece_for_bishop();
      void test_move_set_san_method_sets_move_with_promotion_piece_for_rook();
      void test_move_set_san_method_sets_move_with_promotion_piece_for_queen();
      void test_move_set_san_method_sets_short_castling_for_white_side();
      void test_move_set_san_method_sets_short_castling_for_black_side();
      void test_move_set_san_method_sets_long_castling_for_white_side();
      void test_move_set_san_method_sets_capture();
      void test_move_set_san_method_sets_capture_for_white_side_and_en_passant();
      void test_move_set_san_method_sets_capture_for_black_side_and_en_passant();
      void test_move_set_san_method_sets_move_with_check();
      void test_move_set_san_method_sets_move_with_checkmate();
      void test_move_set_san_method_complains_on_non_existent_move_in_moves();
      void test_move_set_san_method_complains_on_illegal_move();
      void test_move_set_san_method_complains_on_ambiguous_move();
      void test_move_set_san_method_complains_on_non_existent_short_castling_in_moves_for_white_side();
      void test_move_set_san_method_complains_on_non_existent_short_castling_in_moves_for_black_side();
      void test_move_set_san_method_complains_on_non_existent_long_castling_in_moves_for_white_side();
      void test_move_set_san_method_complains_on_non_existent_long_castling_in_moves_for_black_side();
      void test_move_set_san_method_complains_on_no_capture();
      void test_move_set_san_method_complains_on_no_check();
      void test_move_set_san_method_complains_on_no_checkmate();
      void test_move_to_can_move_method_converts_move_to_can_move();
      void test_move_to_can_move_method_converts_move_with_promotion_piece_to_can_move();
      void test_move_to_san_move_method_converts_move_to_san_move();
      void test_move_to_san_move_method_converts_move_to_san_move_with_source_column();
      void test_move_to_san_move_method_converts_move_to_san_move_with_source_row();
      void test_move_to_san_move_method_converts_move_to_san_move_with_source_square();
      void test_move_to_san_move_method_converts_move_to_san_move_with_source_row_for_three_pieces();
      void test_move_to_san_move_method_converts_move_to_san_move_with_source_square_for_four_pieces();
      void test_move_to_san_move_method_converts_move_to_san_move_with_source_column_for_different_columns_and_different_rows();
      void test_move_to_san_move_method_converts_pawn_capture_to_san_move_with_source_column();
      void test_move_to_san_move_method_converts_move_to_san_move_with_promotion_piece_for_knight();
      void test_move_to_san_move_method_converts_move_to_san_move_with_promotion_piece_for_bishop();
      void test_move_to_san_move_method_converts_move_to_san_move_with_promotion_piece_for_rook();
      void test_move_to_san_move_method_converts_move_to_san_move_with_promotion_piece_for_queen();
      void test_move_to_san_move_method_converts_short_castling_to_san_move_for_white_side();
      void test_move_to_san_move_method_converts_short_castling_to_san_move_for_black_side();
      void test_move_to_san_move_method_converts_long_castling_to_san_move_for_white_side();
      void test_move_to_san_move_method_converts_long_castling_to_san_move_for_black_side();
      void test_move_to_san_move_method_converts_capture_to_san_move();
      void test_move_to_san_move_method_converts_capture_to_san_move_for_white_side_and_en_passant();
      void test_move_to_san_move_method_converts_capture_to_san_move_for_black_side_and_en_passant();
      void test_move_to_san_move_method_converts_move_to_san_move_with_check();
      void test_move_to_san_move_method_converts_move_to_san_move_with_checkmate();
      void test_move_to_san_move_method_does_not_set_flags_for_illegal_move();
    };
  }
}

#endif

