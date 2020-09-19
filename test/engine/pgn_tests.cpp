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
#include <sstream>
#include "game.hpp"
#include "pgn_tests.hpp"

using namespace std;

namespace peacockspider
{
  namespace test
  {
    CPPUNIT_TEST_SUITE_REGISTRATION(PGNTests);

    void PGNTests::setUp() {}

    void PGNTests::tearDown() {}

    void PGNTests::test_write_pgn_function_writes_game()
    {
      ostringstream oss;
      Game game(
        "Maly turniej",
        "Nowakowo",
        "????.??.??",
        "1",
        "Nowak, Jan",
        "Kowalski, Piotr",
        Result::UNFINISHED);
      game.moves().push_back(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::PAWN, E7, E5, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KNIGHT, B8, C6, PromotionPiece::NONE));
      write_pgn(oss, game);
      CPPUNIT_ASSERT_EQUAL(string("\
[Event \"Maly turniej\"]\n\
[Site \"Nowakowo\"]\n\
[Date \"????.??.??\"]\n\
[Round \"1\"]\n\
[White \"Nowak, Jan\"]\n\
[Black \"Kowalski, Piotr\"]\n\
[Result \"*\"]\n\
\n\
1. e4 e5 2. Nc3 Nc6 *\n\
\n\
"), oss.str());
    }

    void PGNTests::test_write_pgn_function_writes_game_for_white_win()
    {
      ostringstream oss;
      Game game(
        "Maly turniej",
        "Nowakowo",
        "????.??.??",
        "2",
        "Kowalski, Piotr",
        "Nowak, Jan",
        Result::WHITE_WIN);
      game.moves().push_back(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::PAWN, F7, F6, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::PAWN, D2, D4, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::PAWN, G7, G5, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::QUEEN, D1, H5, PromotionPiece::NONE));
      write_pgn(oss, game);
      CPPUNIT_ASSERT_EQUAL(string("\
[Event \"Maly turniej\"]\n\
[Site \"Nowakowo\"]\n\
[Date \"????.??.??\"]\n\
[Round \"2\"]\n\
[White \"Kowalski, Piotr\"]\n\
[Black \"Nowak, Jan\"]\n\
[Result \"1-0\"]\n\
\n\
1. e4 f6 2. d4 g5 3. Qh5# 1-0\n\
\n\
"), oss.str());
    }

    void PGNTests::test_write_pgn_function_writes_game_for_black_win()
    {
      ostringstream oss;
      Game game(
        "Maly turniej",
        "Nowakowo",
        "????.??.??",
        "3",
        "Kowalik, Adam",
        "Nowak, Jan",
        Result::BLACK_WIN);
      game.moves().push_back(Move(Piece::PAWN, F2, F3, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::PAWN, E7, E5, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::PAWN, G2, G4, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::QUEEN, D8, H4, PromotionPiece::NONE));
      write_pgn(oss, game);
      CPPUNIT_ASSERT_EQUAL(string("\
[Event \"Maly turniej\"]\n\
[Site \"Nowakowo\"]\n\
[Date \"????.??.??\"]\n\
[Round \"3\"]\n\
[White \"Kowalik, Adam\"]\n\
[Black \"Nowak, Jan\"]\n\
[Result \"0-1\"]\n\
\n\
1. f3 e5 2. g4 Qh4# 0-1\n\
\n\
"), oss.str());
    }

    void PGNTests::test_write_pgn_function_writes_game_for_draw()
    {
      ostringstream oss;
      Game game(
        "Maly turniej",
        "Nowakowo",
        "????.??.??",
        "4",
        "Kowalski, Piotr",
        "Kowalik, Adam",
        Result::DRAW);
      game.moves().push_back(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::PAWN, D7, D5, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KNIGHT, G8, F6, PromotionPiece::NONE));
      write_pgn(oss, game);
      CPPUNIT_ASSERT_EQUAL(string("\
[Event \"Maly turniej\"]\n\
[Site \"Nowakowo\"]\n\
[Date \"????.??.??\"]\n\
[Round \"4\"]\n\
[White \"Kowalski, Piotr\"]\n\
[Black \"Kowalik, Adam\"]\n\
[Result \"1/2-1/2\"]\n\
\n\
1. e4 d5 2. Nc3 Nf6 1/2-1/2\n\
\n\
"), oss.str());
    }

    void PGNTests::test_write_pgn_function_writes_game_for_fen_and_white_side()
    {
      ostringstream oss;
      Game game(
        "Jakies zdarzenie",
        "Kowalno",
        "????.??.??",
        "1",
        "Nowak, Jan",
        "Kowalski, Piotr",
        Result::UNFINISHED,
        new Board("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2"));
      game.moves().push_back(Move(Piece::PAWN, D2, D4, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::PAWN, D7, D5, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KNIGHT, B8, C6, PromotionPiece::NONE));
      write_pgn(oss, game);
      CPPUNIT_ASSERT_EQUAL(string("\
[Event \"Jakies zdarzenie\"]\n\
[Site \"Kowalno\"]\n\
[Date \"????.??.??\"]\n\
[Round \"1\"]\n\
[White \"Nowak, Jan\"]\n\
[Black \"Kowalski, Piotr\"]\n\
[Result \"*\"]\n\
[FEN \"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2\"]\n\
\n\
2. d4 d5 3. Nc3 Nc6 *\n\
\n\
"), oss.str());
    }

    void PGNTests::test_write_pgn_function_writes_game_for_fen_and_black_side()
    {
      ostringstream oss;
      Game game(
        "Jakies zdarzenie",
        "Kowalno",
        "????.??.??",
        "2",
        "Kowalik, Adam",
        "Nowak, Jan",
        Result::UNFINISHED,
        new Board("rnbqkbnr/pppp1ppp/8/4p3/4P3/3P4/PPP2PPP/RNBQKBNR b KQkq - 0 2"));
      game.moves().push_back(Move(Piece::PAWN, D7, D6, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KNIGHT, B8, C6, PromotionPiece::NONE));
      write_pgn(oss, game);
      CPPUNIT_ASSERT_EQUAL(string("\
[Event \"Jakies zdarzenie\"]\n\
[Site \"Kowalno\"]\n\
[Date \"????.??.??\"]\n\
[Round \"2\"]\n\
[White \"Kowalik, Adam\"]\n\
[Black \"Nowak, Jan\"]\n\
[Result \"*\"]\n\
[FEN \"rnbqkbnr/pppp1ppp/8/4p3/4P3/3P4/PPP2PPP/RNBQKBNR b KQkq - 0 2\"]\n\
\n\
2... d6 3. Nc3 Nc6 *\n\
\n\
"), oss.str());
    }

    void PGNTests::test_write_pgn_function_writes_game_for_move_characters_greater_than_80()
    {
      ostringstream oss;
      Game game(
        "Jakies zdarzenie",
        "Kowalno",
        "????.??.??",
        "3",
        "Kowalski, Piotr",
        "Kowalik, Adam",
        Result::UNFINISHED);
      game.moves().push_back(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::PAWN, E7, E5, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::PAWN, D2, D4, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::PAWN, D7, D5, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KNIGHT, B8, C6, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KNIGHT, G1, F3, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KNIGHT, G8, F6, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::BISHOP, C1, G5, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::BISHOP, C8, G4, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::BISHOP, F1, B5, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::BISHOP, F8, B4, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KING, E1, G1, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::KING, E8, G8, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::QUEEN, D1, D3, PromotionPiece::NONE));
      game.moves().push_back(Move(Piece::QUEEN, D8, D6, PromotionPiece::NONE));
      write_pgn(oss, game);
      CPPUNIT_ASSERT_EQUAL(string("\
[Event \"Jakies zdarzenie\"]\n\
[Site \"Kowalno\"]\n\
[Date \"????.??.??\"]\n\
[Round \"3\"]\n\
[White \"Kowalski, Piotr\"]\n\
[Black \"Kowalik, Adam\"]\n\
[Result \"*\"]\n\
\n\
1. e4 e5 2. d4 d5 3. Nc3 Nc6 4. Nf3 Nf6 5. Bg5 Bg4 6. Bb5 Bb4 7. O-O O-O 8. Qd3\n\
Qd6 *\n\
\n\
"), oss.str());
    }
  }
}
