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
#include "board_tests.hpp"
#include "chess.hpp"

using namespace std;

namespace peacockspider
{
  namespace test
  {
    CPPUNIT_TEST_SUITE_REGISTRATION(BoardTests);

    void BoardTests::setUp() {}

    void BoardTests::tearDown() {}

    void BoardTests::test_board_constructor_initializes_members()
    {
      Board board;
      CPPUNIT_ASSERT(Color::BLACK == board.color(A8));
      CPPUNIT_ASSERT(Piece::ROOK == board.piece(A8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(B8));
      CPPUNIT_ASSERT(Piece::KNIGHT == board.piece(B8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(C8));
      CPPUNIT_ASSERT(Piece::BISHOP == board.piece(C8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(D8));
      CPPUNIT_ASSERT(Piece::QUEEN == board.piece(D8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(E8));
      CPPUNIT_ASSERT(Piece::KING == board.piece(E8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(F8));
      CPPUNIT_ASSERT(Piece::BISHOP == board.piece(F8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(G8));
      CPPUNIT_ASSERT(Piece::KNIGHT == board.piece(G8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(H8));
      CPPUNIT_ASSERT(Piece::ROOK == board.piece(H8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(A7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(A7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(B7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(B7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(C7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(C7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(D7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(D7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(E7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(E7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(F7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(F7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(G7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(G7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(H7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(H7));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(A6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(B6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(C6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(D6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(E6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(F6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(G6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(H6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(A5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(B5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(C5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(D5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(E5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(F5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(G5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(H5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(A4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(B4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(C4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(D4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(E4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(F4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(G4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(H4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(A3));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(B3));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(C3));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(D3));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(E3));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(F3));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(G3));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(H3));
      CPPUNIT_ASSERT(Color::WHITE == board.color(A2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(A2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(B2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(B2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(C2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(C2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(D2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(D2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(E2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(E2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(F2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(F2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(G2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(G2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(H2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(H2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(A1));
      CPPUNIT_ASSERT(Piece::ROOK == board.piece(A1));
      CPPUNIT_ASSERT(Color::WHITE == board.color(B1));
      CPPUNIT_ASSERT(Piece::KNIGHT == board.piece(B1));
      CPPUNIT_ASSERT(Color::WHITE == board.color(C1));
      CPPUNIT_ASSERT(Piece::BISHOP == board.piece(C1));
      CPPUNIT_ASSERT(Color::WHITE == board.color(D1));
      CPPUNIT_ASSERT(Piece::QUEEN == board.piece(D1));
      CPPUNIT_ASSERT(Color::WHITE == board.color(E1));
      CPPUNIT_ASSERT(Piece::KING == board.piece(E1));
      CPPUNIT_ASSERT(Color::WHITE == board.color(F1));
      CPPUNIT_ASSERT(Piece::BISHOP == board.piece(F1));
      CPPUNIT_ASSERT(Color::WHITE == board.color(G1));
      CPPUNIT_ASSERT(Piece::KNIGHT == board.piece(G1));
      CPPUNIT_ASSERT(Color::WHITE == board.color(H1));
      CPPUNIT_ASSERT(Piece::ROOK == board.piece(H1));
      CPPUNIT_ASSERT_EQUAL(E1, board.king_square(Side::WHITE));
      CPPUNIT_ASSERT_EQUAL(E8, board.king_square(Side::BLACK));
      CPPUNIT_ASSERT(Side::WHITE == board.side());
      CPPUNIT_ASSERT((SideCastlings::SHORT | SideCastlings::LONG) == board.side_castlings(Side::WHITE));
      CPPUNIT_ASSERT((SideCastlings::SHORT | SideCastlings::LONG) == board.side_castlings(Side::BLACK));
      CPPUNIT_ASSERT_EQUAL(-1, board.en_passant_column());
      CPPUNIT_ASSERT_EQUAL(0, board.halfmove_clock());
      CPPUNIT_ASSERT_EQUAL(1, board.fullmove_number());
    }

    void BoardTests::test_board_set_method_sets_colors_and_pieces()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 0 4"));
      CPPUNIT_ASSERT(Color::BLACK == board.color(A8));
      CPPUNIT_ASSERT(Piece::ROOK == board.piece(A8));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(B8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(C8));
      CPPUNIT_ASSERT(Piece::BISHOP == board.piece(C8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(D8));
      CPPUNIT_ASSERT(Piece::QUEEN == board.piece(D8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(E8));
      CPPUNIT_ASSERT(Piece::KING == board.piece(E8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(F8));
      CPPUNIT_ASSERT(Piece::BISHOP == board.piece(F8));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(G8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(H8));
      CPPUNIT_ASSERT(Piece::ROOK == board.piece(H8));
      CPPUNIT_ASSERT(Color::BLACK == board.color(A7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(A7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(B7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(B7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(C7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(C7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(D7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(D7));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(E7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(F7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(F7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(G7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(G7));
      CPPUNIT_ASSERT(Color::BLACK == board.color(H7));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(H7));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(A6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(B6));
      CPPUNIT_ASSERT(Color::BLACK == board.color(C6));
      CPPUNIT_ASSERT(Piece::KNIGHT == board.piece(C6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(D6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(E6));
      CPPUNIT_ASSERT(Color::BLACK == board.color(F6));
      CPPUNIT_ASSERT(Piece::KNIGHT == board.piece(F6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(G6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(H6));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(A5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(B5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(C5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(D5));
      CPPUNIT_ASSERT(Color::BLACK == board.color(E5));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(E5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(F5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(G5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(H5));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(A4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(B4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(C4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(D4));
      CPPUNIT_ASSERT(Color::WHITE == board.color(E4));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(E4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(F4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(G4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(H4));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(A3));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(B3));
      CPPUNIT_ASSERT(Color::WHITE == board.color(C3));
      CPPUNIT_ASSERT(Piece::KNIGHT == board.piece(C3));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(D3));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(E3));
      CPPUNIT_ASSERT(Color::WHITE == board.color(F3));
      CPPUNIT_ASSERT(Piece::KNIGHT == board.piece(F3));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(G3));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(H3));
      CPPUNIT_ASSERT(Color::WHITE == board.color(A2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(A2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(B2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(B2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(C2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(C2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(D2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(D2));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(E2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(F2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(F2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(G2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(G2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(H2));
      CPPUNIT_ASSERT(Piece::PAWN == board.piece(H2));
      CPPUNIT_ASSERT(Color::WHITE == board.color(A1));
      CPPUNIT_ASSERT(Piece::ROOK == board.piece(A1));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(B1));
      CPPUNIT_ASSERT(Color::WHITE == board.color(C1));
      CPPUNIT_ASSERT(Piece::BISHOP == board.piece(C1));
      CPPUNIT_ASSERT(Color::WHITE == board.color(D1));
      CPPUNIT_ASSERT(Piece::QUEEN == board.piece(D1));
      CPPUNIT_ASSERT(Color::WHITE == board.color(E1));
      CPPUNIT_ASSERT(Piece::KING == board.piece(E1));
      CPPUNIT_ASSERT(Color::WHITE == board.color(F1));
      CPPUNIT_ASSERT(Piece::BISHOP == board.piece(F1));
      CPPUNIT_ASSERT(Color::EMPTY == board.color(G1));
      CPPUNIT_ASSERT(Color::WHITE == board.color(H1));
      CPPUNIT_ASSERT(Piece::ROOK == board.piece(H1));
    }

    void BoardTests::test_board_set_method_sets_king_squares()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("8/5k2/8/6p1/7P/8/3K4/8 w - - 0 1"));
      CPPUNIT_ASSERT_EQUAL(D2, board.king_square(Side::WHITE));
      CPPUNIT_ASSERT_EQUAL(F7, board.king_square(Side::BLACK));
    }

    void BoardTests::test_board_set_method_sets_side_for_white_side()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("rnbqkb1r/ppp1pppp/5n2/3p4/4P3/3B4/PPPP1PPP/RNBQK1NR w KQkq - 0 3"));
      CPPUNIT_ASSERT(Side::WHITE == board.side());
    }

    void BoardTests::test_board_set_method_sets_side_for_black_side()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("rnbqkb1r/ppp1pppp/5n2/3P4/8/3B4/PPPP1PPP/RNBQK1NR b KQkq - 0 3"));
      CPPUNIT_ASSERT(Side::BLACK == board.side());
    }
    
    void BoardTests::test_board_set_method_sets_castlings_for_all_castlings()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("rnbqkb1r/ppp1pppp/8/3n4/8/3B4/PPPP1PPP/RNBQK1NR w KQkq - 0 4"));
      CPPUNIT_ASSERT((SideCastlings::SHORT | SideCastlings::LONG) == board.side_castlings(Side::WHITE));
      CPPUNIT_ASSERT((SideCastlings::SHORT | SideCastlings::LONG) == board.side_castlings(Side::BLACK));
    }

    void BoardTests::test_board_set_method_sets_castlings_for_some_castlings()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("1nbqkbnr/1ppppppp/r7/p7/7P/7R/PPPPPPP1/RNBQKBN1 w Qk - 0 3"));
      CPPUNIT_ASSERT(SideCastlings::LONG == board.side_castlings(Side::WHITE));
      CPPUNIT_ASSERT(SideCastlings::SHORT == board.side_castlings(Side::BLACK));
    }    

    void BoardTests::test_board_set_method_sets_castlings_for_no_castlings()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("8/3k4/7p/6p1/1P6/P7/4K3/8 w - - 0 1"));
      CPPUNIT_ASSERT(SideCastlings::NONE == board.side_castlings(Side::WHITE));
      CPPUNIT_ASSERT(SideCastlings::NONE == board.side_castlings(Side::BLACK));
    }

    void BoardTests::test_board_set_method_sets_en_passant_column_for_white_side()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("rnbqkb1r/ppp2ppp/5n2/2Ppp3/4P3/8/PP1P1PPP/RNBQKBNR w KQkq d6 0 4"));
      CPPUNIT_ASSERT_EQUAL(3, board.en_passant_column());
    }

    void BoardTests::test_board_set_method_sets_en_passant_column_for_black_side()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("rnbqkbnr/pppppp1p/8/8/4PPp1/2N5/PPPP2PP/R1BQKBNR b KQkq f3 0 3"));
      CPPUNIT_ASSERT_EQUAL(5, board.en_passant_column());
    }

    void BoardTests::test_board_set_method_sets_en_passant_column_for_white_side_and_no_pawns()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"));
      CPPUNIT_ASSERT_EQUAL(-1, board.en_passant_column());
    }
    
    void BoardTests::test_board_set_method_sets_en_passant_column_for_black_side_and_no_pawns()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2"));
      CPPUNIT_ASSERT_EQUAL(-1, board.en_passant_column());
    }

    void BoardTests::test_board_set_method_sets_en_passant_column_for_no_en_passant_square()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("rnbqkb1r/ppp1pppp/5n2/3p4/4P3/2N5/PPPP1PPP/R1BQKBNR w KQkq - 0 3"));
      CPPUNIT_ASSERT_EQUAL(-1, board.en_passant_column());
    }

    void BoardTests::test_board_set_method_sets_halfmove_clock()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("r1bqkb1r/ppp1pppp/2n2n2/3p4/4P3/2NB1N2/PPPP1PPP/R1BQK2R b KQkq - 5 4"));
      CPPUNIT_ASSERT_EQUAL(5, board.halfmove_clock());
    }
    
    void BoardTests::test_board_set_method_sets_fullmove_number()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(true, board.set("r1bqkb1r/ppp2ppp/2n1pn2/3p4/4P3/2NB1N2/PPPP1PPP/R1BQK2R w KQkq - 0 5"));
      CPPUNIT_ASSERT_EQUAL(5, board.fullmove_number());
    }

    void BoardTests::test_board_set_method_complains_on_incorrect_pieces()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(false, board.set("rnbqkb1r/pppp1ppp/5n2/4p3/4P3/2N5/PPPP1PPP/X1BQKBNR w KQkq - 0 3"));
    }

    void BoardTests::test_board_set_method_complains_on_incorrect_side()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(false, board.set("rnbqkb1r/pppp1ppp/5n2/4p3/4P3/2N5/PPPP1PPP/R1BQKBNR x KQkq - 0 3"));
    }

    void BoardTests::test_board_set_method_complains_on_incorrect_castlings()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(false, board.set("rnbqkb1r/pppp1ppp/5n2/4p3/4P3/2N5/PPPP1PPP/R1BQKBNR w XQkq - 0 3"));
    }

    void BoardTests::test_board_set_method_complains_on_incorrect_en_passant_square()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(false, board.set("rnbqkbnr/pp1p1ppp/8/4p3/2pPP3/5N2/PPP1BPPP/RNBQK2R b KQkq x3 0 4"));
    }

    void BoardTests::test_board_set_method_complains_on_incorrect_halfmove_clock()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(false, board.set("rnbqkb1r/pppp1ppp/5n2/4p3/4P3/2N5/PPPP1PPP/R1BQKBNR w KQkq - 0x 3"));
    }

    void BoardTests::test_board_set_method_complains_on_incorrect_fullmove_number()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(false, board.set("rnbqkb1r/pppp1ppp/5n2/4p3/4P3/2N5/PPPP1PPP/R1BQKBNR w KQkq - 0 x"));
    }

    void BoardTests::test_board_to_string_method_converts_board_to_string()
    {
      Board board("r1bqkb1r/ppp1pppp/2n2n2/3p4/3P4/5N2/PPPBPPPP/RN1QKB1R w KQkq - 0 4");
      CPPUNIT_ASSERT_EQUAL(string("r1bqkb1r/ppp1pppp/2n2n2/3p4/3P4/5N2/PPPBPPPP/RN1QKB1R w KQkq - 0 4"), board.to_string());
    }

    void BoardTests::test_board_to_string_method_converts_board_to_string_for_white_side_and_en_passant()
    {
      Board board("rnbqk1nr/p1ppbppp/8/1pP1p3/4P3/8/PP1P1PPP/RNBQKBNR w KQkq b6 0 4");
      CPPUNIT_ASSERT_EQUAL(string("rnbqk1nr/p1ppbppp/8/1pP1p3/4P3/8/PP1P1PPP/RNBQKBNR w KQkq b6 0 4"), board.to_string());
    }

    void BoardTests::test_board_to_string_method_converts_board_to_string_for_black_side_and_en_passant()
    {
      Board board("rnbqkbnr/ppppp1pp/8/8/3P1pP1/4P3/PPP2P1P/RNBQKBNR b KQkq g3 0 3");
      CPPUNIT_ASSERT_EQUAL(string("rnbqkbnr/ppppp1pp/8/8/3P1pP1/4P3/PPP2P1P/RNBQKBNR b KQkq g3 0 3"), board.to_string());
    }

    void BoardTests::test_board_has_attack_method_returns_true_for_white_side_pawn_attack()
    {
      Board board("4k3/8/8/3p1p2/8/8/4K3/8 w - - 0 1");
      CPPUNIT_ASSERT_EQUAL(true, board.has_attack(Side::WHITE, E4));
    }
    
    void BoardTests::test_board_has_attack_method_returns_true_for_black_side_pawn_attack()
    {
      Board board("4k3/8/8/8/1P1P4/8/4K3/8 w - - 0 1");
      CPPUNIT_ASSERT_EQUAL(true, board.has_attack(Side::BLACK, C5));
    }
    
    void BoardTests::test_board_has_attack_method_returns_true_for_knight_attack()
    {
      Board board("4k3/8/8/6n1/5n2/8/4K3/8 w - - 0 1");
      CPPUNIT_ASSERT_EQUAL(true, board.has_attack(Side::WHITE, H3));
    }
    
    void BoardTests::test_board_has_attack_method_returns_true_for_king_attack()
    {
      Board board("4k3/8/8/8/8/4K3/8/8 b - - 0 1");
      CPPUNIT_ASSERT_EQUAL(true, board.has_attack(Side::BLACK, E4));
    }
    
    void BoardTests::test_board_has_attack_method_returns_true_for_bishop_attack()
    {
      Board board("4k3/8/8/8/8/6b1/8/4K3 w - - 0 1");
      CPPUNIT_ASSERT_EQUAL(true, board.has_attack(Side::WHITE, E1));
    }

    void BoardTests::test_board_has_attack_method_returns_true_for_rook_attack()
    {
      Board board("8/8/4k3/8/8/4R3/8/4K3 b - - 0 1");
      CPPUNIT_ASSERT_EQUAL(true, board.has_attack(Side::BLACK, E6));
    }

    void BoardTests::test_board_has_attack_method_returns_true_for_queen_attack_as_bishop_attack()
    {
      Board board("4k3/8/8/5q2/8/8/8/4K3 w - - 0 1");
      CPPUNIT_ASSERT_EQUAL(true, board.has_attack(Side::WHITE, D3));
    }

    void BoardTests::test_board_has_attack_method_returns_true_for_queen_attack_as_rook_attack()
    {
      Board board("4k3/8/1Q6/8/8/8/8/4K3 b - - 0 1");
      CPPUNIT_ASSERT_EQUAL(true, board.has_attack(Side::BLACK, E6));
    }

    void BoardTests::test_board_has_attack_method_retruns_false_for_barriers()
    {
      Board board("4k3/4b3/5p2/8/3q1P2/8/8/4K3 w - - 0 1");
      CPPUNIT_ASSERT_EQUAL(false, board.has_attack(Side::WHITE, H4));
    }

    void BoardTests::test_board_has_attack_method_returns_false_for_no_barriers()
    {
      Board board("4k3/8/8/8/8/5N2/8/4K3 w - - 0 1");
      CPPUNIT_ASSERT_EQUAL(false, board.has_attack(Side::WHITE, E1));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_initial_board()
    {
      Board board;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(20), move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B1, A3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, G1, F3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, G1, H3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, A2, A3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, A2, A4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, B2, B3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, B2, B4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C2, C3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C2, C4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, D2, D3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, D2, D4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, F2, F3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, F2, F4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, G2, G3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, G2, G4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, H2, H3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, H2, H4, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_pawns()
    {
      Board board("4k3/4p3/8/5p2/2P5/8/4P3/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(3 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C4, C5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, C4, C6, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_pawns()
    {
      Board board("4k3/4p3/8/5p2/2P5/8/4P3/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(3 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E7, E6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E7, E5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, F5, F4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, F5, F3, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_does_not_generate_moves_for_white_side_and_pawns_and_barriers()
    {
      Board board("4k3/2p1p3/2N5/4n3/4n3/2B5/2P1P3/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, C2, C3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, C2, C4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_does_not_generate_moves_for_black_side_and_pawns_and_barriers()
    {
      Board board("4k3/2p1p3/2N5/4n3/4n3/2B5/2P1P3/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, C7, C6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, C7, C5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E7, E5, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_captures_for_white_side_and_pawns()
    {
      Board board("4k3/8/8/8/3n4/2P1b3/5P2/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(2 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C3, D4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, F2, E3, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_captures_for_black_side_and_pawns()
    {
      Board board("4k3/5p2/4B3/2p5/3R4/8/8/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(2 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C5, D4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, F7, E6, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_does_not_generate_captures_for_white_side_and_pawns()
    {
      Board board("4k3/8/8/8/8/3P4/4P3/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E2, D3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E2, F3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, D3, C4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, D3, E4, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_does_not_generate_captures_for_black_side_and_pawns()
    {
      Board board("4k3/4p3/3p4/8/8/8/8/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, D6, C5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, D6, E5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E7, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E7, F6, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_captures_for_white_side_and_en_passant()
    {
      Board board("4k3/8/8/4PpP1/8/8/8/4K3 w - f6 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(2 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E5, F6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, G5, F6, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_captures_for_black_side_and_en_passant()
    {
      Board board("4k3/8/8/8/2pPp3/8/8/4K3 b - d3 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(2 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C4, D3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E4, D3, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_promotions()
    {
      Board board("4k1n1/P6P/8/8/8/8/8/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(6 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, A7, A8, PromotionPiece::QUEEN)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, A7, A8, PromotionPiece::KNIGHT)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, H7, G8, PromotionPiece::QUEEN)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, H7, G8, PromotionPiece::KNIGHT)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, H7, H8, PromotionPiece::QUEEN)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, H7, H8, PromotionPiece::KNIGHT)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_promotions()
    {
      Board board("4k3/8/8/8/8/8/p5p1/1N2K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(6 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, A2, A1, PromotionPiece::QUEEN)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, A2, A1, PromotionPiece::KNIGHT)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, A2, B1, PromotionPiece::QUEEN)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, A2, B1, PromotionPiece::KNIGHT)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, G2, G1, PromotionPiece::QUEEN)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, G2, G1, PromotionPiece::KNIGHT)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_knights()
    {
      Board board("4k3/4p1P1/8/5N2/1N6/6P1/2P5/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(11 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B4, A6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B4, C6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B4, D5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B4, D3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B4, A2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, B4, C2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F5, E7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, F5, G7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F5, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F5, H6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F5, D4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F5, H4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F5, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, F5, G3, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_knights()
    {
      Board board("4k3/1n6/6p1/2p5/5n2/8/4P1p1/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(9 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F4, E6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, F4, G6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F4, D5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F4, H5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F4, D3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F4, H3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F4, E2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, F4, G2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B7, D8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B7, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B7, A5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, B7, C5, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_bishops()
    {
      Board board("4k3/8/8/3p2B1/8/1B2P3/8/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(12 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B3, A4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B3, C4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B3, D5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, B3, E6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B3, A2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B3, C2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B3, D1, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G5, F6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G5, E7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G5, D8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G5, H6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G5, F4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, G5, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G5, H6, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_bishops()
    {
      Board board("4k3/1b6/8/6b1/4P3/4p3/8/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(12 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G5, F6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G5, E7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G5, D8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G5, H6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G5, F4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, G5, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G5, H4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B7, A8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B7, C8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B7, A6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B7, C6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B7, D5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B7, E4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, B7, F3, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_rooks()
    {
      Board board("4k3/1R3n2/8/8/1n6/2P2R2/8/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(16 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, F3, F4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, F3, F5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, F3, F6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, F3, F7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, F3, F8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, F3, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, F3, D3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, F3, C3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, F3, G3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, F3, H3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B7, B8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B7, A7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B7, C7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B7, D7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B7, E7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B7, F7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B7, G7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B7, B6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B7, B5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B7, B4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B7, B3, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_rooks()
    {
      Board board("4k3/6P1/8/1B6/3P2r1/8/1r4p1/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(15 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B2, B3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B2, B4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B2, B5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B2, B6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B2, A2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B2, C2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B2, D2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B2, E2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B2, F2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B2, G2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B2, B1, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, G4, G5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, G4, G6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, G4, G7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G4, G8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, G4, F4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, G4, E4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, G4, D4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G4, C4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, G4, H4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, G4, G3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G4, G2, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_queen()
    {
      Board board("4k3/8/3n4/8/1b3Q2/8/3P4/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(20 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, E5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F4, C7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, F5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, F6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, F7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, F8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, G5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, H6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, E4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, D4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, C4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, B4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F4, A4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, G4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, H4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F4, D2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, F3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, F2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, F1, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, G3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F4, H2, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_queen()
    {
      Board board("4k3/8/2q3p1/8/8/5N2/2N5/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(19 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, B7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, A8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, C7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, C8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, D7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, B6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, A6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, E6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, F6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, G6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, B5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, A4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, C5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, C4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, C3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, C2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, C1, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, D5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, E4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, F3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, G2, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_king()
    {
      Board board("4k3/8/8/8/8/8/3P1p2/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(4 <= move_pairs.length());
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E1, D2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E1, E2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E1, F2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E1, D1, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E1, F1, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_king()
    {
      Board board("4k3/3P1p2/8/8/8/8/8/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(4 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E8, D8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E8, F8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E8, D7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E8, E7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E8, F7, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_all_castlings_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(2 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E1, G1, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E1, C1, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_all_castlings_for_black_side()
    {
      Board board("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(2 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E8, G8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E8, C8, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_does_not_generate_all_castlings_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/R3K1NR w K - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E1, G1, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E1, C1, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_does_not_generate_all_castlings_for_black_side()
    {
      Board board("rB1nk2r/8/8/8/8/8/8/4K3 b q - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E8, G8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E8, C8, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_white_side_and_pieces()
    {
      Board board("rnbqkbnr/ppp2ppp/3p4/4p3/4P3/3P4/PPP2PPP/RNBQKBNR w KQkq - 0 3");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(32), move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B1, A3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B1, D2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, C1, D2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, C1, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, C1, F4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, C1, G5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, C1, H6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, D1, D2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, D1, E2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, D1, F3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, D1, G4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, D1, H5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E1, D2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E1, E2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, F1, E2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, G1, F3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, G1, H3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, G1, E2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, A2, A3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, A2, A4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, B2, B3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, B2, B4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C2, C3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C2, C4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, F2, F3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, F2, F4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, G2, G3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, G2, G4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, H2, H3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, H2, H4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, D3, D4, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_moves_method_generates_moves_for_black_side_and_pieces()
    {
      Board board("rnbqkbnr/ppp2ppp/3p4/4p3/4P3/2NP4/PPP2PPP/R1BQKBNR b KQkq - 0 3");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(32), move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, D6, D5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, A7, A6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, A7, A5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, B7, B6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, B7, B5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C7, C6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C7, C5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, F7, F6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, F7, F5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, G7, G6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, G7, G5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, H7, H6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, H7, H5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B8, D7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B8, A6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B8, C6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, C8, D7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, C8, E6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, C8, F5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, C8, G4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, C8, H3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, D8, D7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, D8, E7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, D8, F6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, D8, G5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, D8, H4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E8, D7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E8, E7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, F8, E7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, G8, E7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, G8, F6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, G8, H6, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_good_moves_method_does_not_generate_moves_for_initial_board()
    {
      Board board;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), move_pairs.length());
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_does_not_generate_moves_for_white_side_and_pawns()
    {
      Board board("4k3/4p3/8/6p1/2P5/8/4P3/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, C4, C5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, C4, C6, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_does_not_generate_moves_for_black_side_and_pawns()
    {
      Board board("4k3/4p3/8/6p1/2P5/8/4P3/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E7, E6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E7, E5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, G5, G4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, G4, G3, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_pawns()
    {
      Board board("4k3/8/8/3p4/2P5/3b1b2/4P3/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(3 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E2, D3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E2, F3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C4, D5, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_pawns()
    {
      Board board("4k3/4p3/5P2/2p5/1B1N4/8/8/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(3 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C5, B4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C5, D4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E7, F6, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_does_not_generate_captures_for_white_side_and_pawns()
    {
      Board board("4k3/8/8/8/8/3P4/4P3/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E2, D3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E2, F3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, D3, C4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, D3, E4, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_does_not_generate_captures_for_black_side_and_pawns()
    {
      Board board("4k3/4p3/3p4/8/8/8/8/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, D6, C5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, D6, E5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E7, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::PAWN, E7, F6, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_en_passant()
    {
      Board board("4k3/8/8/2PpP3/8/8/8/4K3 w - d6 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(2 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C5, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E5, D6, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_en_passant()
    {
      Board board("4k3/8/8/8/4pPp1/8/8/4K3 b - f3 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(2 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E4, F3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, G4, F3, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_moves_for_white_side_and_promotions()
    {
      Board board("2n1k3/1P4P1/8/8/8/8/8/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(6 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, B7, B8, PromotionPiece::QUEEN)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, B7, B8, PromotionPiece::KNIGHT)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, B7, C8, PromotionPiece::QUEEN)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, B7, C8, PromotionPiece::KNIGHT)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, G7, G8, PromotionPiece::QUEEN)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, G7, G8, PromotionPiece::KNIGHT)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_moves_for_black_side_and_promotions()
    {
      Board board("4k3/8/8/8/8/8/2p4p/1B2K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(6 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C2, C1, PromotionPiece::QUEEN)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C2, C1, PromotionPiece::KNIGHT)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C2, B1, PromotionPiece::QUEEN)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, C2, B1, PromotionPiece::KNIGHT)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, H2, H1, PromotionPiece::QUEEN)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, H2, H1, PromotionPiece::KNIGHT)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_knights()
    {
      Board board("4k3/4p1p1/8/5N2/1N6/4P3/2b5/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(3 <= move_pairs.length());
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, B4, A6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, B4, C6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, B4, D5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, B4, D3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, B4, A2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, B4, C2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F5, E7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, F5, G7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, F5, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, F5, H6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, F5, D4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, F5, H4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, F5, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, F5, G3, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_knights()
    {
      Board board("4k3/6n1/1p2P3/5B2/2n5/4P3/3P4/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(4 <= move_pairs.length());
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, C4, B6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, C4, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, C4, A5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, C4, E5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, C4, A3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, C4, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, C4, B2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, C4, D2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, G7, E6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, G7, F5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KNIGHT, G7, H5, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_bishops()
    {
      Board board("4k3/8/3P4/8/3p1B2/8/1B1n3p/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(3 <= move_pairs.length());
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, B2, A3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, B2, C3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, B2, D4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, B2, E5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, B2, A1, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, B2, C1, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, F4, E5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, F4, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, F4, G5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, F4, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, F4, D2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, F4, C1, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, F4, G3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, F4, H2, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_bishops()
    {
      Board board("4k3/P7/6b1/2b5/8/p2PP3/8/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(3 <= move_pairs.length());
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, C5, B6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, C5, A7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, C5, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, C5, B4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, C5, A3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, C5, D4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, C5, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, C5, F2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, G6, F7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, G6, E8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, G6, H7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, G6, F5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::BISHOP, G6, D3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, G6, C2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::BISHOP, G6, H5, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_rooks()
    {
      Board board("4k3/8/1R2p3/8/8/1P2n1R1/8/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(2 <= move_pairs.length());
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G3, G4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G3, F3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, G3, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G3, D3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G3, H3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G3, G2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B6, B7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B6, A6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B6, C6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B6, E6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B6, F6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B6, B5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B6, B3, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_rooks()
    {
      Board board("4k3/8/1p2P1r1/8/1r2P1N1/8/8/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(3 <= move_pairs.length());
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B4, B5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B4, B6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B4, A4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B4, C4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, B4, E4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B4, F4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, B4, B3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G6, G7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G6, F6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, G6, E6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G6, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G6, H6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G6, G5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::ROOK, G6, G4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::ROOK, G6, G3, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_queen()
    {
      Board board("4k3/8/5p2/3P3p/8/2n2Q2/8/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(3 <= move_pairs.length());
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F3, E4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F3, D5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F3, F4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F3, F6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F3, F7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F3, G4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F3, H5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F3, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, F3, C3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F3, B3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F3, E2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F3, F2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, F3, G2, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_queen()
    {
      Board board("4k3/8/2q3N1/8/P7/2P2p2/8/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(3 <= move_pairs.length());
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, B7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, C7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, D7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, B6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, D6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, G6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, H6, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, B5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, A4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, C5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::QUEEN, C6, C3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, C2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, D5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::QUEEN, C6, F3, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_king()
    {
      Board board("4k3/8/8/8/8/8/3pPp2/4K3 w - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(2 <= move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E1, D2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E1, E2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E1, F2, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E1, D1, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E1, F1, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_king()
    {
      Board board("4k3/3PpP2/8/8/8/8/8/4K3 b - - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(2 <= move_pairs.length());
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E8, D8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E8, F8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E8, D7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E8, E7, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KING, E8, F7, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_does_not_generate_castlings_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E1, G1, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E1, C1, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_does_not_generate_castlings_for_black_side()
    {
      Board board("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E8, G8, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(!move_pairs.contain_move(Move(Piece::KING, E8, C8, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_white_side_and_pieces()
    {
      Board board("r1bqkbnr/ppp2ppp/2n5/3pp3/3PP3/2N5/PPP2PPP/R1BQKBNR w KQkq - 0 4");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, C3, D5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, D4, E5, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E4, D5, PromotionPiece::NONE)));
    }

    void BoardTests::test_board_generate_pseudolegal_good_moves_method_generates_captures_for_black_side_and_pieces()
    {
      Board board("r1bqkbnr/ppp2ppp/2n5/3pp3/3PP3/2N2N2/PPP2PPP/R1BQKB1R b KQkq - 0 4");
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      board.generate_pseudolegal_good_moves(move_pairs);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), move_pairs.length());
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, D5, E4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::PAWN, E5, D4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT(move_pairs.contain_move(Move(Piece::KNIGHT, C6, D4, PromotionPiece::NONE)));
    }
    
    void BoardTests::test_board_make_move_method_makes_move_for_piece()
    {
      Board board("4k3/8/2b5/8/8/2B3N1/8/4K3 w - - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KNIGHT, G3, F5, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/8/2b5/5N2/8/2B5/8/4K3 b - - 1 1") == board2);
    }

    void BoardTests::test_board_make_move_method_makes_capture_for_piece()
    {
      Board board("4k3/8/2b5/8/8/2N2N2/8/4K3 b - - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::BISHOP, C6, F3, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/8/8/8/8/2N2b2/8/4K3 w - - 0 2") == board2);
    }

    void BoardTests::test_board_make_move_method_makes_capture_for_king_and_captured_pawn()
    {
      Board board("4k3/8/8/8/3P4/8/5p2/4K3 w - - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, E1, F2, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/8/8/8/3P4/8/5K2/8 b - - 0 1") == board2);
    }

    void BoardTests::test_board_make_move_method_makes_capture_for_king_and_captured_knight()
    {
      Board board("4k3/5n2/8/8/3P4/8/8/4Kn2 w - - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, E1, F1, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/5n2/8/8/3P4/8/8/5K2 b - - 0 1") == board2);
    }

    void BoardTests::test_board_make_move_method_makes_capture_for_king_and_captured_bishop()
    {
      Board board("4kB2/8/8/5p2/3n4/4B3/8/4K3 b - - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, E8, F8, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("5k2/8/8/5p2/3n4/4B3/8/4K3 w - - 0 2") == board2);
    }
    
    void BoardTests::test_board_make_move_method_makes_capture_for_king_and_captured_rook()
    {
      Board board("6Rk/8/8/6n1/8/3R1B2/8/4K3 b - - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, H8, G8, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("6k1/8/8/6n1/8/3R1B2/8/4K3 w - - 0 2") == board2);
    }
    
    void BoardTests::test_board_make_move_method_makes_capture_for_king_and_captured_queen()
    {
      Board board("4k3/8/8/5b2/3P4/2N5/5q2/4K3 w - - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, E1, F2, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/8/8/5b2/3P4/2N5/5K2/8 b - - 0 1") == board2);
    }

    void BoardTests::test_board_make_move_method_does_not_make_king_move_for_check()
    {
      Board board("4k3/8/8/8/8/6n1/8/4K3 w - - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(false, board.make_move(Move(Piece::KING, E1, E2, PromotionPiece::NONE), board2));
    }

    void BoardTests::test_board_make_move_method_does_not_make_pawn_move_for_check()
    {
      Board board("4k3/8/2p5/8/B7/8/8/4K3 b - - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(false, board.make_move(Move(Piece::PAWN, C6, C5, PromotionPiece::NONE), board2));
    }

    void BoardTests::test_board_make_move_method_makes_move_for_promotion()
    {
      Board board("4k3/6P1/8/8/8/2p5/8/4K3 w - - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::PAWN, G7, G8, PromotionPiece::QUEEN), board2));
      CPPUNIT_ASSERT(Board("4k1Q1/8/8/8/8/2p5/8/4K3 b - - 0 1") == board2);
    }
    
    void BoardTests::test_board_make_move_method_makes_capture_for_promotion()
    {
      Board board("4k3/8/8/8/8/8/2p5/1B2K3 b - - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::PAWN, C2, B1, PromotionPiece::KNIGHT), board2));
      CPPUNIT_ASSERT(Board("4k3/8/8/8/8/8/8/1n2K3 w - - 0 2") == board2);
    }

    void BoardTests::test_board_make_move_method_makes_capture_for_white_side_and_en_passant()
    {
      Board board("rnbqkb1r/pp1p1ppp/5n2/1Pp1p3/4P3/8/P1PP1PPP/RNBQKBNR w KQkq c6 0 4");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::PAWN, B5, C6, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("rnbqkb1r/pp1p1ppp/2P2n2/4p3/4P3/8/P1PP1PPP/RNBQKBNR b KQkq - 0 4") == board2);
    }

    void BoardTests::test_board_make_move_method_makes_capture_for_black_side_and_en_passant()
    {
      Board board("rnbqkbnr/ppp1p1pp/8/3p4/3PPp2/2N5/PPPB1PPP/R2QKBNR b KQkq e3 0 4");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::PAWN, F4, E3, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("rnbqkbnr/ppp1p1pp/8/3p4/3P4/2N1p3/PPPB1PPP/R2QKBNR w KQkq - 0 5") == board2);
    }

    void BoardTests::test_board_make_move_method_sets_en_passant_column_for_white_side()
    {
      Board board("rnbqkbnr/pp1p1ppp/8/4p3/2p1P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 0 4");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::PAWN, B2, B4, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("rnbqkbnr/pp1p1ppp/8/4p3/1Pp1P3/2N2N2/P1PP1PPP/R1BQKB1R b KQkq b3 0 4") == board2);
    }

    void BoardTests::test_board_make_move_method_sets_en_passant_column_for_black_side()
    {
      Board board("r1bqkbnr/pppp1ppp/2n5/4p1P1/4P3/8/PPPP1P1P/RNBQKBNR b KQkq - 0 3");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::PAWN, F7, F5, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("r1bqkbnr/pppp2pp/2n5/4ppP1/4P3/8/PPPP1P1P/RNBQKBNR w KQkq f6 0 4") == board2);
    }
    
    void BoardTests::test_board_make_move_method_does_not_set_en_passant_column_for_white_side()
    {
      Board board("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::PAWN, D2, D4, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("rnbqkbnr/pppp1ppp/8/4p3/3PP3/8/PPP2PPP/RNBQKBNR b KQkq - 0 2") == board2);
    }

    void BoardTests::test_board_make_move_method_does_not_set_en_passant_column_for_black_side()
    {
      Board board("rnbqkbnr/pppp1ppp/8/4p3/3PP3/8/PPP2PPP/RNBQKBNR b KQkq - 0 2");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::PAWN, D7, D5, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("rnbqkbnr/ppp2ppp/8/3pp3/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 3") == board2);
    }

    void BoardTests::test_board_make_move_method_removes_white_short_castling_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::ROOK, H1, H4, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/8/8/8/7R/8/8/R3K3 b Q - 1 1") == board2);
    }

    void BoardTests::test_board_make_move_method_removes_black_short_castling_for_black_side()
    {
      Board board("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::ROOK, H8, H5, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("r3k3/8/8/7r/8/8/8/4K3 w q - 1 2") == board2);
    }

    void BoardTests::test_board_make_move_method_removes_white_long_castling_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::ROOK, A1, C1, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/8/8/8/8/8/8/2R1K2R b K - 1 1") == board2);
    }
    
    void BoardTests::test_board_make_move_method_removes_black_long_castling_for_black_side()
    {
      Board board("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::ROOK, A8, C8, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("2r1k2r/8/8/8/8/8/8/4K3 w k - 1 2") == board2);
    }

    void BoardTests::test_board_make_move_method_removes_all_white_castling_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, E1, E2, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/8/8/8/8/8/4K3/R6R b - - 1 1") == board2);
    }

    void BoardTests::test_board_make_move_method_removes_all_black_castling_for_black_side()
    {
      Board board("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, E8, E7, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("r6r/4k3/8/8/8/8/8/4K3 w - - 1 2") == board2);
    }
    
    void BoardTests::test_board_make_move_method_removes_black_short_castling_for_white_side()
    {
      Board board("r3k2r/8/8/8/3B4/8/8/4K3 w kq - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::BISHOP, D4, H8, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("r3k2B/8/8/8/8/8/8/4K3 b q - 0 1") == board2);
    }

    void BoardTests::test_board_make_move_method_removes_white_short_castling_for_black_side()
    {
      Board board("4k3/8/8/3b4/8/8/8/R3K2R b KQ - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::BISHOP, D5, H1, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/8/8/8/8/8/8/R3K2b w Q - 0 2") == board2);
    }

    void BoardTests::test_board_make_move_method_removes_black_long_castling_for_white_side()
    {
      Board board("r3k2r/8/8/8/R7/8/8/4K3 w kq - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::ROOK, A4, A8, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("R3k2r/8/8/8/8/8/8/4K3 b k - 0 1") == board2);
    }

    void BoardTests::test_board_make_move_method_removes_white_long_castling_for_black_side()
    {
      Board board("4k3/8/8/r7/8/8/8/R3K2R b KQ - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::ROOK, A5, A1, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/8/8/8/8/8/8/r3K2R w K - 0 2") == board2);
    }

    void BoardTests::test_board_make_move_method_makes_short_castling_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, E1, G1, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/8/8/8/8/8/8/R4RK1 b - - 1 1") == board2);
    }

    void BoardTests::test_board_make_move_method_makes_short_castling_for_black_side()
    {
      Board board("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, E8, G8, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("r4rk1/8/8/8/8/8/8/4K3 w - - 1 2") == board2);
    }

    void BoardTests::test_board_make_move_method_makes_long_castling_for_white_side()
    {
      Board board("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, E1, C1, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/8/8/8/8/8/8/2KR3R b - - 1 1") == board2);
    }

    void BoardTests::test_board_make_move_method_makes_long_castling_for_black_side()
    {
      Board board("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, E8, C8, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("2kr3r/8/8/8/8/8/8/4K3 w - - 1 2") == board2);
    }

    void BoardTests::test_board_make_move_method_does_not_make_short_castling_for_check_before_castling()
    {
      Board board("4k3/8/8/8/8/6b1/8/R3K2R w KQ - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(false, board.make_move(Move(Piece::KING, E1, G1, PromotionPiece::NONE), board2));
    }

    void BoardTests::test_board_make_move_method_does_not_make_short_castling_for_attack_to_rook_destination_square()
    {
      Board board("r3k2r/8/8/8/8/8/8/4KR2 b kq - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(false, board.make_move(Move(Piece::KING, E8, G8, PromotionPiece::NONE), board2));
    }
    
    void BoardTests::test_board_make_move_method_does_not_make_short_castling_for_check_after_castling()
    {
      Board board("4k3/8/8/8/8/7n/8/R3K2R w KQ - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(false, board.make_move(Move(Piece::KING, E1, G1, PromotionPiece::NONE), board2));
    }

    void BoardTests::test_board_make_move_method_does_not_make_long_castling_for_check_before_castling()
    {
      Board board("4k3/8/4q3/8/8/8/8/R3K2R w KQ - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(false, board.make_move(Move(Piece::KING, E1, C1, PromotionPiece::NONE), board2));
    }

    void BoardTests::test_board_make_move_method_does_not_make_long_castling_for_attack_to_rook_destination_square()
    {
      Board board("r3k2r/8/1B6/8/8/8/8/4K3 b kq - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(false, board.make_move(Move(Piece::KING, E8, C8, PromotionPiece::NONE), board2));
    }

    void BoardTests::test_board_make_move_method_does_not_make_long_castling_for_check_after_castling()
    {
      Board board("4k3/8/8/8/2r5/8/8/R3K2R w KQ - 0 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(false, board.make_move(Move(Piece::KING, E1, C1, PromotionPiece::NONE), board2));
    }
    
    void BoardTests::test_board_make_move_method_makes_short_castling_for_bug_of_castling_making()
    {
      Board board("4k3/8/8/8/8/8/8/R3K2R w KQ - 2 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, E1, G1, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("4k3/8/8/8/8/8/8/R4RK1 b - - 3 1") == board2);
    }
    
    void BoardTests::test_board_make_move_method_makes_long_castling_for_bug_of_castling_making()
    {
      Board board("r3k2r/8/8/8/8/8/8/4K3 b kq - 3 1");
      Board board2;
      CPPUNIT_ASSERT_EQUAL(true, board.make_move(Move(Piece::KING, E8, C8, PromotionPiece::NONE), board2));
      CPPUNIT_ASSERT(Board("2kr3r/8/8/8/8/8/8/4K3 w - - 4 2") == board2);
    }

    void BoardTests::test_board_make_null_move_method_makes_null_move_for_white_side()
    {
      Board board("r3k3/8/2n5/8/8/6N1/8/4K2R w Kq - 0 1");
      Board board2;
      board.make_null_move(board2);
      CPPUNIT_ASSERT(Board("r3k3/8/2n5/8/8/6N1/8/4K2R b Kq - 0 1") == board2);
    }

    void BoardTests::test_board_make_null_move_method_makes_null_move_for_black_side()
    {
      Board board("4k2r/8/3b4/8/8/5B2/8/R3K3 b Qk - 0 1");
      Board board2;
      board.make_null_move(board2);
      CPPUNIT_ASSERT(Board("4k2r/8/3b4/8/8/5B2/8/R3K3 w Qk - 0 2") == board2);
    }

    void BoardTests::test_board_make_null_move_method_does_not_set_en_passant_column_for_white_side_and_en_passant()
    {
      Board board("rnbqkb1r/ppp2ppp/5n2/2Ppp3/4P3/8/PP1P1PPP/RNBQKBNR w KQkq d6 0 4");
      Board board2;
      board.make_null_move(board2);
      CPPUNIT_ASSERT(Board("rnbqkb1r/ppp2ppp/5n2/2Ppp3/4P3/8/PP1P1PPP/RNBQKBNR b KQkq - 0 4") == board2);
    }

    void BoardTests::test_board_make_null_move_method_does_not_set_en_passant_column_for_black_side_and_en_passant()
    {
      Board board("rnbqkbnr/p1pp1ppp/8/4p3/1pP1P3/5N1P/PP1P1PP1/RNBQKB1R b KQkq c3 0 4");
      Board board2;
      board.make_null_move(board2);
      CPPUNIT_ASSERT(Board("rnbqkbnr/p1pp1ppp/8/4p3/1pP1P3/5N1P/PP1P1PP1/RNBQKB1R w KQkq - 0 5") == board2);
    }

    void BoardTests::test_board_set_method_complains_for_white_side_and_bug_of_board_setting_check()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(false, board.set("4k3/8/8/7B/8/8/8/4K3 w - - 0 1"));      
    }

    void BoardTests::test_board_set_method_complains_for_black_side_and_bug_of_board_setting_check()
    {
      Board board;
      CPPUNIT_ASSERT_EQUAL(false, board.set("4k3/8/8/8/8/3n4/8/4K3 b - - 0 1"));      
    }
  }
}
