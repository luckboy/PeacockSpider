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
#include <memory>
#include "move_tests.hpp"
#include "chess.hpp"

using namespace std;

namespace peacockspider
{
  namespace test
  {
    CPPUNIT_TEST_SUITE_REGISTRATION(MoveTests);

    void MoveTests::setUp() {}

    void MoveTests::tearDown() {}

    void MoveTests::test_move_set_can_method_sets_move()
    {
      Board board("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_can(CANMove("b1c3"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE) == move);
    }

    void MoveTests::test_move_set_can_method_sets_move_with_promotion_piece_for_knight()
    {
      Board board("4k3/6P1/8/8/8/8/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_can(CANMove("g7g8n"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::PAWN, G7, G8, PromotionPiece::KNIGHT) == move);
    }

    void MoveTests::test_move_set_can_method_sets_move_with_promotion_piece_for_bishop()
    {
      Board board("4k3/2P5/8/8/8/8/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_can(CANMove("c7c8b"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::PAWN, C7, C8, PromotionPiece::BISHOP) == move);
    }

    void MoveTests::test_move_set_can_method_sets_move_with_promotion_piece_for_rook()
    {
      Board board("4k3/8/8/8/8/8/1p6/4K3 b - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_can(CANMove("b2b1r"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::PAWN, B2, B1, PromotionPiece::ROOK) == move);
    }

    void MoveTests::test_move_set_can_method_sets_move_with_promotion_piece_for_queen()
    {
      Board board("4k3/8/8/8/8/8/7p/4K3 b - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_can(CANMove("h2h1q"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::PAWN, H2, H1, PromotionPiece::QUEEN) == move);
    }

    void MoveTests::test_move_set_can_method_complains_on_non_existent_move_in_moves()
    {
      Board board("4k3/8/8/8/8/8/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(false, move.set_can(CANMove("e2e4"), board, move_pairs));
    }

    void MoveTests::test_move_set_can_method_complains_on_illegal_move()
    {
      Board board("4k3/8/8/8/7b/8/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(false, move.set_can(CANMove("e1f2"), board, move_pairs));
    }

    void MoveTests::test_move_set_san_method_sets_move()
    {
      Board board("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("Nc3"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE) == move);
    }

    void MoveTests::test_move_set_san_method_sets_move_with_source_column()
    {
      Board board("4k3/8/8/8/8/3N1N2/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("Nfe5"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, F3, E5, PromotionPiece::NONE) == move);
    }

    void MoveTests::test_move_set_san_method_sets_move_with_source_row()
    {
      Board board("r3k3/8/8/8/8/8/r7/4K3 b - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("R2a5"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::ROOK, A2, A5, PromotionPiece::NONE) == move);
    }

    void MoveTests::test_move_set_san_method_sets_move_with_source_square()
    {
      Board board("4k3/1B6/8/8/8/1B3B2/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("Bb3d5"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::BISHOP, B3, D5, PromotionPiece::NONE) == move);
    }

    void MoveTests::test_move_set_san_method_sets_move_with_promotion_piece_for_knight()
    {
      Board board("4k3/6P1/8/8/8/8/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("g8=N"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::PAWN, G7, G8, PromotionPiece::KNIGHT) == move);
    }

    void MoveTests::test_move_set_san_method_sets_move_with_promotion_piece_for_bishop()
    {
      Board board("4k3/2P5/8/8/8/8/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("c8=B"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::PAWN, C7, C8, PromotionPiece::BISHOP) == move);
    }
    
    void MoveTests::test_move_set_san_method_sets_move_with_promotion_piece_for_rook()
    {
      Board board("4k3/8/8/8/8/8/6p1/4K3 b - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("g1=R"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::PAWN, G2, G1, PromotionPiece::ROOK) == move);
    }
    
    void MoveTests::test_move_set_san_method_sets_move_with_promotion_piece_for_queen()
    {
      Board board("4k3/7P/8/8/8/8/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("h8=Q"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::PAWN, H7, H8, PromotionPiece::QUEEN) == move);
    }

    void MoveTests::test_move_set_san_method_sets_short_castling_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("O-O"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::KING, E1, G1, PromotionPiece::NONE) == move);
    }
    
    void MoveTests::test_move_set_san_method_sets_short_castling_for_black_side()
    {
      Board board("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("O-O"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::KING, E8, G8, PromotionPiece::NONE) == move);
    }
    
    void MoveTests::test_move_set_san_method_sets_long_castling_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("O-O-O"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::KING, E1, C1, PromotionPiece::NONE) == move);
    }

    void MoveTests::test_move_set_san_method_sets_capture()
    {
      Board board("4k3/8/8/4p3/8/2B5/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("Bxe5"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::BISHOP, C3, E5, PromotionPiece::NONE) == move);
    }

    void MoveTests::test_move_set_san_method_sets_capture_for_white_side_and_en_passant()
    {
      Board board("4k3/8/8/3Pp3/8/8/8/4K3 w - e6 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("dxe6"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::PAWN, D5, E6, PromotionPiece::NONE) == move);
    }

    void MoveTests::test_move_set_san_method_sets_capture_for_black_side_and_en_passant()
    {
      Board board("4k3/8/8/8/2Pp4/8/8/4K3 b - c3 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("dxc3"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::PAWN, D4, C3, PromotionPiece::NONE) == move);
    }

    void MoveTests::test_move_set_san_method_sets_move_with_check()
    {
      Board board("4k3/8/8/8/7n/2p5/8/4K3 b - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("Nf3+"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, H4, F3, PromotionPiece::NONE) == move);
    }

    void MoveTests::test_move_set_san_method_sets_move_with_checkmate()
    {
      Board board("4k3/R7/8/2Q5/8/8/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(true, move.set_san(SANMove("Qc8#"), board, move_pairs));
      CPPUNIT_ASSERT(Move(Piece::QUEEN, C5, C8, PromotionPiece::NONE) == move);
    }

    void MoveTests::test_move_set_san_method_complains_on_non_existent_move_in_moves()
    {
      Board board("4k3/8/8/8/8/8/2P5/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(false, move.set_san(SANMove("e4"), board, move_pairs));
    }

    void MoveTests::test_move_set_san_method_complains_on_illegal_move()
    {
      Board board("4k3/8/8/8/4r3/8/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(false, move.set_san(SANMove("Ke2"), board, move_pairs));
    }

    void MoveTests::test_move_set_san_method_complains_on_ambiguous_move()
    {
      Board board("4k3/8/8/8/8/3N1N2/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(false, move.set_san(SANMove("Ne5"), board, move_pairs));
    }

    void MoveTests::test_move_set_san_method_complains_on_non_existent_short_castling_in_moves_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(false, move.set_san(SANMove("O-O"), board, move_pairs));
    }

    void MoveTests::test_move_set_san_method_complains_on_non_existent_short_castling_in_moves_for_black_side()
    {
      Board board("4k3/8/8/8/8/8/8/4K3 b - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(false, move.set_san(SANMove("O-O"), board, move_pairs));
    }

    void MoveTests::test_move_set_san_method_complains_on_non_existent_long_castling_in_moves_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(false, move.set_san(SANMove("O-O-O"), board, move_pairs));
    }

    void MoveTests::test_move_set_san_method_complains_on_non_existent_long_castling_in_moves_for_black_side()
    {
      Board board("4k3/8/8/8/8/8/8/4K3 b - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(false, move.set_san(SANMove("O-O-O"), board, move_pairs));
    }
    
    void MoveTests::test_move_set_san_method_complains_on_no_capture()
    {
      Board board("4k3/8/8/8/8/8/5N2/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(false, move.set_san(SANMove("Nxe4"), board, move_pairs));
    }

    void MoveTests::test_move_set_san_method_complains_on_no_check()
    {
      Board board("4k3/5n2/8/8/8/8/8/4K3 b - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(false, move.set_san(SANMove("Ne5+"), board, move_pairs));
    }

    void MoveTests::test_move_set_san_method_complains_on_no_checkmate()
    {
      Board board("4k3/8/8/8/6B1/8/8/4K3 w - - 0 1");
      Move move;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT_EQUAL(false, move.set_san(SANMove("Bh5#"), board, move_pairs));
    }

    void MoveTests::test_move_to_can_move_method_converts_move_to_can_move()
    {
      Move move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE);
      CPPUNIT_ASSERT(CANMove("b1c3") == move.to_can_move());
    }

    void MoveTests::test_move_to_can_move_method_converts_move_with_promotion_piece_to_can_move()
    {
      Move move(Piece::PAWN, A7, A8, PromotionPiece::QUEEN);
      CPPUNIT_ASSERT(CANMove("a7a8q") == move.to_can_move());
    }

    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move()
    {
      Board board("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
      Move move(Piece::KNIGHT, G1, F3, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("Nf3") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move_with_source_column()
    {
      Board board("4k3/8/8/8/8/1N1N4/8/4K3 w - - 0 1");
      Move move(Piece::KNIGHT, D3, C5, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("Ndc5") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move_with_source_row()
    {
      Board board("4k3/7b/8/8/8/7b/8/4K3 b - - 0 1");
      Move move(Piece::BISHOP, H7, F5, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("B7f5") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move_with_source_square()
    {
      Board board("4k3/2n1n3/8/8/8/2n5/8/4K3 b - - 0 1");
      Move move(Piece::KNIGHT, C7, D5, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("Nc7d5") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move_with_source_row_for_three_pieces()
    {
      Board board("4k3/8/6b1/8/8/8/2b3b1/4K3 b - - 0 1");
      Move move(Piece::BISHOP, G6, E4, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("B6e4") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move_with_source_square_for_four_pieces()
    {
      Board board("4k3/8/2N1N3/8/8/8/2N1N3/4K3 w - - 0 1");
      Move move(Piece::KNIGHT, E2, D4, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("Ne2d4") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move_with_source_column_for_different_columns_and_different_rows()
    {
      Board board("4k3/8/5q2/2q5/8/8/8/4K3 b - - 0 1");
      Move move(Piece::QUEEN, F6, D4, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("Qfd4") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_pawn_capture_to_san_move_with_source_column()
    {
      Board board("4k3/8/8/4p3/3P4/8/8/4K3 w - - 0 1");
      Move move(Piece::PAWN, D4, E5, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("dxe5") == move.to_san_move(board, move_pairs));
    }
    
    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move_with_promotion_piece_for_knight()
    {
      Board board("4k3/7P/8/8/8/8/8/4K3 w - - 0 1");
      Move move(Piece::PAWN, H7, H8, PromotionPiece::KNIGHT);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("h8=N") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move_with_promotion_piece_for_bishop()
    {
      Board board("4k3/8/8/8/8/8/1p6/4K3 b - - 0 1");
      Move move(Piece::PAWN, B2, B1, PromotionPiece::BISHOP);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("b1=B") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move_with_promotion_piece_for_rook()
    {
      Board board("4k3/8/8/8/8/8/p7/3BK3 b - - 0 1");
      Move move(Piece::PAWN, A2, A1, PromotionPiece::ROOK);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("a1=R") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move_with_promotion_piece_for_queen()
    {
      Board board("4kr2/7P/8/8/8/8/8/4K3 w - - 0 1");
      Move move(Piece::PAWN, H7, H8, PromotionPiece::QUEEN);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("h8=Q") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_short_castling_to_san_move_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
      Move move(Piece::KING, E1, G1, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("O-O") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_short_castling_to_san_move_for_black_side()
    {
      Board board("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
      Move move(Piece::KING, E8, G8, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("O-O") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_long_castling_to_san_move_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
      Move move(Piece::KING, E1, C1, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("O-O-O") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_long_castling_to_san_move_for_black_side()
    {
      Board board("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
      Move move(Piece::KING, E8, C8, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("O-O-O") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_capture_to_san_move()
    {
      Board board("4k3/8/8/4n3/8/6B1/8/4K3 w - - 0 1");
      Move move(Piece::BISHOP, G3, E5, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("Bxe5") == move.to_san_move(board, move_pairs));
    }
    
    void MoveTests::test_move_to_san_move_method_converts_capture_to_san_move_for_white_side_and_en_passant()
    {
      Board board("4k3/8/8/2Pp4/8/8/8/4K3 w - d6 0 1");
      Move move(Piece::PAWN, C5, D6, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("cxd6") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_capture_to_san_move_for_black_side_and_en_passant()
    {
      Board board("4k3/8/8/8/2Pp4/8/8/4K3 b - c3 0 1");
      Move move(Piece::PAWN, D4, C3, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("dxc3") == move.to_san_move(board, move_pairs));
    }
    
    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move_with_check()
    {
      Board board("4k3/8/8/8/6N1/8/8/4K3 w - - 0 1");
      Move move(Piece::KNIGHT, G4, F6, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("Nf6+") == move.to_san_move(board, move_pairs));
    }

    void MoveTests::test_move_to_san_move_method_converts_move_to_san_move_with_checkmate()
    {
      Board board("4k3/8/8/2r5/8/8/r7/4K3 b - - 0 1");
      Move move(Piece::ROOK, C5, C1, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("Rc1#") == move.to_san_move(board, move_pairs));
    }
    
    void MoveTests::test_move_to_san_move_method_does_not_set_flags_for_illegal_move()
    {
      Board board("4k3/8/8/8/8/8/3P4/4K3 w - - 0 1");
      Move move(Piece::KNIGHT, C4, D6, PromotionPiece::NONE);
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      CPPUNIT_ASSERT(SANMove("Nd6") == move.to_san_move(board, move_pairs));
    }
  }
}
