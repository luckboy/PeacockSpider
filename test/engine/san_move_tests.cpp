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
#include "san_move_tests.hpp"
#include "chess.hpp"

using namespace std;

namespace peacockspider
{
  namespace test
  {
    CPPUNIT_TEST_SUITE_REGISTRATION(SANMoveTests);

    void SANMoveTests::setUp() {}

    void SANMoveTests::tearDown() {}

    void SANMoveTests::test_san_move_set_method_sets_move()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("e4"));
      CPPUNIT_ASSERT(SANMove(Piece::PAWN, -1, -1, E4, PromotionPiece::NONE, SANMoveFlags::NONE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_move_with_piece()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("Nc3"));
      CPPUNIT_ASSERT(SANMove(Piece::KNIGHT, -1, -1, C3, PromotionPiece::NONE, SANMoveFlags::NONE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_move_with_source_column()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("Bcf5"));
      CPPUNIT_ASSERT(SANMove(Piece::BISHOP, C8 % 8, -1, F5, PromotionPiece::NONE, SANMoveFlags::NONE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_move_with_source_row()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("R1a4"));
      CPPUNIT_ASSERT(SANMove(Piece::ROOK, -1, A1 / 8, A4, PromotionPiece::NONE, SANMoveFlags::NONE) == move);
    }
    
    void SANMoveTests::test_san_move_set_method_sets_move_with_source_square()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("Qb3d5"));
      CPPUNIT_ASSERT(SANMove(Piece::QUEEN, B3 % 8, B3 / 8, D5, PromotionPiece::NONE, SANMoveFlags::NONE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_capture_with_piece()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("Bxc4"));
      CPPUNIT_ASSERT(SANMove(Piece::BISHOP, -1, -1, C4, PromotionPiece::NONE, SANMoveFlags::CAPTURE) == move);
    }
    
    void SANMoveTests::test_san_move_set_method_sets_capture_with_source_column()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("exd5"));
      CPPUNIT_ASSERT(SANMove(Piece::PAWN, E4 % 8, -1, D5, PromotionPiece::NONE, SANMoveFlags::CAPTURE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_capture_with_source_row()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("Q1xf3"));
      CPPUNIT_ASSERT(SANMove(Piece::QUEEN, -1, D1 / 8, F3, PromotionPiece::NONE, SANMoveFlags::CAPTURE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_capture_with_source_square()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("Bb2xd4"));
      CPPUNIT_ASSERT(SANMove(Piece::BISHOP, B2 % 8, B2 / 8, D4, PromotionPiece::NONE, SANMoveFlags::CAPTURE) == move);
    }
    
    void SANMoveTests::test_san_move_set_method_sets_move_with_promotion_piece()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("g8Q"));
      CPPUNIT_ASSERT(SANMove(Piece::PAWN, -1, -1, G8, PromotionPiece::QUEEN, SANMoveFlags::NONE) == move);
    }
    
    void SANMoveTests::test_san_move_set_method_sets_capture_with_promotion_piece()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("bxa8N"));
      CPPUNIT_ASSERT(SANMove(Piece::PAWN, B7 % 8, -1, A8, PromotionPiece::KNIGHT, SANMoveFlags::CAPTURE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_move_with_promotion_piece_and_eqaul_character()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("h8=Q"));
      CPPUNIT_ASSERT(SANMove(Piece::PAWN, -1, -1, H8, PromotionPiece::QUEEN, SANMoveFlags::NONE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_short_castling()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("O-O"));
      CPPUNIT_ASSERT(SANMove(true, SANMoveFlags::NONE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_long_castling()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("O-O-O"));
      CPPUNIT_ASSERT(SANMove(false, SANMoveFlags::NONE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_move_with_check()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("Nf6+"));
      CPPUNIT_ASSERT(SANMove(Piece::KNIGHT, -1, -1, F6, PromotionPiece::NONE, SANMoveFlags::CHECK) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_capture_with_check()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("Bxb4+"));
      CPPUNIT_ASSERT(SANMove(Piece::BISHOP, -1, -1, B4, PromotionPiece::NONE, SANMoveFlags::CAPTURE | SANMoveFlags::CHECK) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_move_with_promotion_piece_and_check()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("b8=B+"));
      CPPUNIT_ASSERT(SANMove(Piece::PAWN, -1, -1, B8, PromotionPiece::BISHOP, SANMoveFlags::CHECK) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_castling_with_check()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("O-O-O+"));
      CPPUNIT_ASSERT(SANMove(false, SANMoveFlags::CHECK) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_move_with_checkmate()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("Bb2#"));
      CPPUNIT_ASSERT(SANMove(Piece::BISHOP, -1, -1, B2, PromotionPiece::NONE, SANMoveFlags::CHECKMATE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_capture_with_checkmate()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("Nxg6#"));
      CPPUNIT_ASSERT(SANMove(Piece::KNIGHT, -1, -1, G6, PromotionPiece::NONE, SANMoveFlags::CAPTURE | SANMoveFlags::CHECKMATE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_move_with_promotion_piece_and_checkmate()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("axb1=N#"));
      CPPUNIT_ASSERT(SANMove(Piece::PAWN, A2 % 8, -1, B1, PromotionPiece::KNIGHT, SANMoveFlags::CAPTURE | SANMoveFlags::CHECKMATE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_castling_with_checkmate()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("O-O#"));
      CPPUNIT_ASSERT(SANMove(true, SANMoveFlags::CHECKMATE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_move_with_question_mark_and_exclamation_mark()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("a4?!"));
      CPPUNIT_ASSERT(SANMove(Piece::PAWN, -1, -1, A4, PromotionPiece::NONE, SANMoveFlags::NONE) == move);
    }

    void SANMoveTests::test_san_move_set_method_sets_move_with_check_and_exclamation_marks()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("Bb2+!!"));
      CPPUNIT_ASSERT(SANMove(Piece::BISHOP, -1, -1, B2, PromotionPiece::NONE, SANMoveFlags::CHECK) == move);
    }
    
    void SANMoveTests::test_san_move_set_method_complains_on_incorrect_piece()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(false, move.set("Le4"));
    }

    void SANMoveTests::test_san_move_set_method_complains_on_incorrect_source_column_or_incorrect_source_row()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(false, move.set("Nic3"));
    }

    void SANMoveTests::test_san_move_set_method_complains_on_incorrect_destination_square()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(false, move.set("B1c9"));
    }

    void SANMoveTests::test_san_move_set_method_complains_on_move_without_promotion_piece_with_equal_character()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(false, move.set("e8="));
    }

    void SANMoveTests::test_san_move_set_method_complains_on_incorrect_promotion_piece()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(false, move.set("a8=Z"));
    }

    void SANMoveTests::test_san_move_set_method_complains_on_incorrect_flag()
    {
      SANMove move;
      CPPUNIT_ASSERT_EQUAL(false, move.set("b2=Q-"));
    }

    void SANMoveTests::test_san_move_to_string_method_converts_move_to_string()
    {
      SANMove move("d4");
      CPPUNIT_ASSERT_EQUAL(string("d4"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_move_with_piece_to_string()
    {
      SANMove move("Bf4");
      CPPUNIT_ASSERT_EQUAL(string("Bf4"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_move_with_source_column_to_string()
    {
      SANMove move("Nfe5");
      CPPUNIT_ASSERT_EQUAL(string("Nfe5"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_move_with_source_row_to_string()
    {
      SANMove move("R1a4");
      CPPUNIT_ASSERT_EQUAL(string("R1a4"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_move_with_source_square_to_string()
    {
      SANMove move("Nc3d5");
      CPPUNIT_ASSERT_EQUAL(string("Nc3d5"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_capture_with_piece_to_string()
    {
      SANMove move("Bxc4");
      CPPUNIT_ASSERT_EQUAL(string("Bxc4"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_capture_with_source_column_to_string()
    {
      SANMove move("dxc4");
      CPPUNIT_ASSERT_EQUAL(string("dxc4"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_capture_with_source_row_to_string()
    {
      SANMove move("Q2xf5");
      CPPUNIT_ASSERT_EQUAL(string("Q2xf5"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_capture_with_source_square_to_string()
    {
      SANMove move("Nc3xe4");
      CPPUNIT_ASSERT_EQUAL(string("Nc3xe4"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_move_with_promotion_piece_to_string()
    {
      SANMove move("e8=Q");
      CPPUNIT_ASSERT_EQUAL(string("e8=Q"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_capture_with_promotion_piece_to_string()
    {
      SANMove move("exd1=N");
      CPPUNIT_ASSERT_EQUAL(string("exd1=N"), move.to_string());
    }
    
    void SANMoveTests::test_san_move_to_string_method_converts_short_castling_to_string()
    {
      SANMove move("O-O");
      CPPUNIT_ASSERT_EQUAL(string("O-O"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_long_castling_to_string()
    {
      SANMove move("O-O-O");
      CPPUNIT_ASSERT_EQUAL(string("O-O-O"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_move_with_check_to_string()
    {
      SANMove move("Nf3+");
      CPPUNIT_ASSERT_EQUAL(string("Nf3+"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_capture_with_check_to_string()
    {
      SANMove move("Bxb2+");
      CPPUNIT_ASSERT_EQUAL(string("Bxb2+"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_move_with_promotion_piece_and_check_to_string()
    {
      SANMove move("b8=Q+");
      CPPUNIT_ASSERT_EQUAL(string("b8=Q+"), move.to_string());
    }
    
    void SANMoveTests::test_san_move_to_string_method_converts_castling_with_check_to_string()
    {
      SANMove move("O-O+");
      CPPUNIT_ASSERT_EQUAL(string("O-O+"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_move_with_checkmate_to_string()
    {
      SANMove move("Bh5#");
      CPPUNIT_ASSERT_EQUAL(string("Bh5#"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_capture_with_checkmate_to_string()
    {
      SANMove move("Rxa1#");
      CPPUNIT_ASSERT_EQUAL(string("Rxa1#"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_move_with_promotion_piece_and_checkmate_to_string()
    {
      SANMove move("b8=Q#");
      CPPUNIT_ASSERT_EQUAL(string("b8=Q#"), move.to_string());
    }

    void SANMoveTests::test_san_move_to_string_method_converts_castling_with_checkmate_to_string()
    {
      SANMove move("O-O-O#");
      CPPUNIT_ASSERT_EQUAL(string("O-O-O#"), move.to_string());
    }
  }
}
