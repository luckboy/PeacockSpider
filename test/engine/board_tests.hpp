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
#ifndef _BOARD_TESTS_HPP
#define _BOARD_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

namespace peacockspider
{
  namespace test
  {
    class BoardTests : public CppUnit::TestFixture
    {
      CPPUNIT_TEST_SUITE(BoardTests);
      CPPUNIT_TEST(test_board_constructor_initializes_members);
      CPPUNIT_TEST(test_board_set_method_sets_colors_and_pieces);
      CPPUNIT_TEST(test_board_set_method_sets_king_squares);
      CPPUNIT_TEST(test_board_set_method_sets_side_for_white_side);
      CPPUNIT_TEST(test_board_set_method_sets_side_for_black_side);
      CPPUNIT_TEST(test_board_set_method_sets_castlings_for_all_castlings);
      CPPUNIT_TEST(test_board_set_method_sets_castlings_for_some_castlings);
      CPPUNIT_TEST(test_board_set_method_sets_castlings_for_no_castlings);
      CPPUNIT_TEST(test_board_set_method_sets_en_passant_column_for_white_side);
      CPPUNIT_TEST(test_board_set_method_sets_en_passant_column_for_black_side);
      CPPUNIT_TEST(test_board_set_method_sets_en_passant_column_for_white_side_and_no_pawns);
      CPPUNIT_TEST(test_board_set_method_sets_en_passant_column_for_black_side_and_no_pawns);
      CPPUNIT_TEST(test_board_set_method_sets_en_passant_column_for_no_en_passant_square);
      CPPUNIT_TEST(test_board_set_method_sets_halfmove_clock);
      CPPUNIT_TEST(test_board_set_method_sets_fullmove_number);
      CPPUNIT_TEST(test_board_to_string_method_converts_board_to_string);
      CPPUNIT_TEST(test_board_to_string_method_converts_board_to_string_for_white_side_and_en_passant);
      CPPUNIT_TEST(test_board_to_string_method_converts_board_to_string_for_black_side_and_en_passant);
      CPPUNIT_TEST(test_board_has_attack_method_returns_true_for_white_side_pawn_attack);
      CPPUNIT_TEST(test_board_has_attack_method_returns_true_for_black_side_pawn_attack);
      CPPUNIT_TEST(test_board_has_attack_method_returns_true_for_knight_attack);
      CPPUNIT_TEST(test_board_has_attack_method_returns_true_for_king_attack);
      CPPUNIT_TEST(test_board_has_attack_method_returns_true_for_bishop_attack);
      CPPUNIT_TEST(test_board_has_attack_method_returns_true_for_rook_attack);
      CPPUNIT_TEST(test_board_has_attack_method_returns_true_for_queen_attack_as_bishop_attack);
      CPPUNIT_TEST(test_board_has_attack_method_returns_true_for_queen_attack_as_rook_attack);
      CPPUNIT_TEST(test_board_has_attack_method_retruns_false_for_barriers);
      CPPUNIT_TEST(test_board_has_attack_method_returns_false_for_no_barriers);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_initial_board);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_pawns);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_pawns);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_does_not_generate_moves_for_white_side_and_pawns_and_barriers);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_does_not_generate_moves_for_black_side_and_pawns_and_barriers);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_captures_for_white_side_and_pawns);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_captures_for_black_side_and_pawns);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_does_not_generate_captures_for_white_side_and_pawns);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_does_not_generate_captures_for_black_side_and_pawns);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_captures_for_white_side_and_en_passant);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_captures_for_black_side_and_en_passant);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_promotions);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_promotions);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_knights);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_knights);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_bishops);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_bishops);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_rooks);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_rooks);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_queen);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_queen);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_king);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_king);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_all_castlings_for_white_side);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_all_castlings_for_black_side);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_does_not_generate_all_castlings_for_white_side);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_does_not_generate_all_castlings_for_black_side);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_pieces);
      CPPUNIT_TEST(test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_pieces);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_does_not_generate_moves_for_initial_board);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_does_not_generate_moves_for_white_side_and_pawns);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_does_not_generate_moves_for_black_side_and_pawns);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_pawns);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_pawns);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_does_not_generate_captures_for_white_side_and_pawns);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_does_not_generate_captures_for_black_side_and_pawns);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_en_passant);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_en_passant);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_moves_for_white_side_and_promotions);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_moves_for_black_side_and_promotions);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_knights);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_knights);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_bishops);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_bishops);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_rooks);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_rooks);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_queen);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_queen);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_king);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_king);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_does_not_generate_castlings_for_white_side);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_does_not_generate_castlings_for_black_side);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_pieces);
      CPPUNIT_TEST(test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_pieces);
      CPPUNIT_TEST_SUITE_END();
    public:
      void setUp();

      void tearDown();

      void test_board_constructor_initializes_members();
      void test_board_set_method_sets_colors_and_pieces();
      void test_board_set_method_sets_king_squares();
      void test_board_set_method_sets_side_for_white_side();
      void test_board_set_method_sets_side_for_black_side();
      void test_board_set_method_sets_castlings_for_all_castlings();
      void test_board_set_method_sets_castlings_for_some_castlings();
      void test_board_set_method_sets_castlings_for_no_castlings();
      void test_board_set_method_sets_en_passant_column_for_white_side();
      void test_board_set_method_sets_en_passant_column_for_black_side();
      void test_board_set_method_sets_en_passant_column_for_white_side_and_no_pawns();
      void test_board_set_method_sets_en_passant_column_for_black_side_and_no_pawns();
      void test_board_set_method_sets_en_passant_column_for_no_en_passant_square();
      void test_board_set_method_sets_halfmove_clock();
      void test_board_set_method_sets_fullmove_number();
      void test_board_to_string_method_converts_board_to_string();
      void test_board_to_string_method_converts_board_to_string_for_white_side_and_en_passant();
      void test_board_to_string_method_converts_board_to_string_for_black_side_and_en_passant();
      void test_board_has_attack_method_returns_true_for_white_side_pawn_attack();
      void test_board_has_attack_method_returns_true_for_black_side_pawn_attack();
      void test_board_has_attack_method_returns_true_for_knight_attack();
      void test_board_has_attack_method_returns_true_for_king_attack();
      void test_board_has_attack_method_returns_true_for_bishop_attack();
      void test_board_has_attack_method_returns_true_for_rook_attack();
      void test_board_has_attack_method_returns_true_for_queen_attack_as_bishop_attack();
      void test_board_has_attack_method_returns_true_for_queen_attack_as_rook_attack();
      void test_board_has_attack_method_retruns_false_for_barriers();
      void test_board_has_attack_method_returns_false_for_no_barriers();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_initial_board();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_pawns();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_pawns();
      void test_board_generate_pseudolegal_moves_method_does_not_generate_moves_for_white_side_and_pawns_and_barriers();
      void test_board_generate_pseudolegal_moves_method_does_not_generate_moves_for_black_side_and_pawns_and_barriers();
      void test_board_generate_pseudolegal_moves_method_generates_captures_for_white_side_and_pawns();
      void test_board_generate_pseudolegal_moves_method_generates_captures_for_black_side_and_pawns();
      void test_board_generate_pseudolegal_moves_method_does_not_generate_captures_for_white_side_and_pawns();
      void test_board_generate_pseudolegal_moves_method_does_not_generate_captures_for_black_side_and_pawns();
      void test_board_generate_pseudolegal_moves_method_generates_captures_for_white_side_and_en_passant();
      void test_board_generate_pseudolegal_moves_method_generates_captures_for_black_side_and_en_passant();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_promotions();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_promotions();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_knights();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_knights();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_bishops();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_bishops();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_rooks();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_rooks();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_queen();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_queen();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_king();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_king();
      void test_board_generate_pseudolegal_moves_method_generates_all_castlings_for_white_side();
      void test_board_generate_pseudolegal_moves_method_generates_all_castlings_for_black_side();
      void test_board_generate_pseudolegal_moves_method_does_not_generate_all_castlings_for_white_side();
      void test_board_generate_pseudolegal_moves_method_does_not_generate_all_castlings_for_black_side();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_pieces();
      void test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_pieces();
      void test_board_generate_pseudolegal_good_moves_method_does_not_generate_moves_for_initial_board();
      void test_board_generate_pseudolegal_good_moves_method_does_not_generate_moves_for_white_side_and_pawns();
      void test_board_generate_pseudolegal_good_moves_method_does_not_generate_moves_for_black_side_and_pawns();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_pawns();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_pawns();
      void test_board_generate_pseudolegal_good_moves_method_does_not_generate_captures_for_white_side_and_pawns();
      void test_board_generate_pseudolegal_good_moves_method_does_not_generate_captures_for_black_side_and_pawns();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_en_passant();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_en_passant();
      void test_board_generate_pseudolegal_good_moves_method_generates_moves_for_white_side_and_promotions();
      void test_board_generate_pseudolegal_good_moves_method_generates_moves_for_black_side_and_promotions();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_knights();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_knights();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_bishops();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_bishops();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_rooks();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_rooks();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_queen();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_queen();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_king();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_king();
      void test_board_generate_pseudolegal_good_moves_method_does_not_generate_castlings_for_white_side();
      void test_board_generate_pseudolegal_good_moves_method_does_not_generate_castlings_for_black_side();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_pieces();
      void test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_pieces();
    };
  }
}

#endif
