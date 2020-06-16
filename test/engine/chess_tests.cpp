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
#include <algorithm>
#include <vector>
#include "chess_tests.hpp"
#include "chess.hpp"

using namespace std;

namespace peacockspider
{
  namespace test
  {
    CPPUNIT_TEST_SUITE_REGISTRATION(ChessTests);

    void ChessTests::setUp() {}

    void ChessTests::tearDown() {}
    
    void ChessTests::test_repetitions_function_returns_number_of_repetirions()
    {
      vector<Board> boards {
        Board("4k3/8/1b6/8/8/6B1/8/4K3 w - - 0 1"),
        Board("4k3/8/1b6/8/8/8/5B2/4K3 b - - 0 1"),
        Board("4k3/2b5/8/8/8/8/5B2/4K3 w - - 0 2"),
        Board("4k3/2b5/8/8/8/6B1/8/4K3 b - - 0 2"),
        Board("4k3/8/1b6/8/8/6B1/8/4K3 w - - 0 3"),
        Board("4k3/8/1b6/8/8/8/5B2/4K3 b - - 0 3"),
        Board("4k3/2b5/8/8/8/8/5B2/4K3 w - - 0 4"),
        Board("4k3/2b5/8/8/8/6B1/8/4K3 b - - 0 4"),
        Board("4k3/8/1b6/8/8/6B1/8/4K3 w - - 0 5"),
        Board("4k3/8/1b6/8/8/8/5B2/4K3 b - - 0 5"),
        Board("4k3/2b5/8/8/8/8/5B2/4K3 w - - 0 6"),
        Board("4k3/2b5/8/8/8/6B1/8/4K3 b - - 0 6")
      };
      Board board("4k3/8/1b6/8/8/6B1/8/4K3 w - - 0 1");
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), repetitions(board, boards));
    }

    void ChessTests::test_repetitions_function_with_last_board_returns_number_of_repetirions_without_last_board()
    {
      vector<Board> boards {
        Board("4k3/2n5/8/8/8/8/5N2/4K3 w - - 0 1"),
        Board("4k3/2n5/8/8/8/3N4/8/4K3 b - - 0 1"),
        Board("4k3/8/8/3n4/8/3N4/8/4K3 w - - 0 2"),
        Board("4k3/8/8/3n4/8/8/5N2/4K3 b - - 0 2"),
        Board("4k3/2n5/8/8/8/8/5N2/4K3 w - - 0 3"),
        Board("4k3/2n5/8/8/8/3N4/8/4K3 b - - 0 3"),
        Board("4k3/8/8/3n4/8/3N4/8/4K3 w - - 0 4"),
        Board("4k3/8/8/3n4/8/8/5N2/4K3 b - - 0 4"),
        Board("4k3/2n5/8/8/8/8/5N2/4K3 w - - 0 5"),
        Board("4k3/2n5/8/8/8/3N4/8/4K3 b - - 0 5"),
        Board("4k3/8/8/3n4/8/3N4/8/4K3 w - - 0 6"),
        Board("4k3/8/8/3n4/8/8/5N2/4K3 b - - 0 6")
      };
      Board board("4k3/2n5/8/8/8/8/5N2/4K3 w - - 0 1");
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), repetitions(board, boards, nullptr));
    }
    
    void ChessTests::test_repetitions_function_with_last_board_returns_number_of_repetirions_with_last_board()
    {
      vector<Board> boards {
        Board("4k3/2r5/8/8/8/8/6R1/4K3 w - - 0 1"),
        Board("4k3/2r5/8/8/6R1/8/8/4K3 b - - 0 1"),
        Board("4k3/8/8/2r5/6R1/8/8/4K3 w - - 0 2"),
        Board("4k3/8/8/2r5/8/8/6R1/4K3 b - - 0 2"),
        Board("4k3/2r5/8/8/8/8/6R1/4K3 w - - 0 3"),
        Board("4k3/2r5/8/8/6R1/8/8/4K3 b - - 0 3"),
        Board("4k3/8/8/2r5/6R1/8/8/4K3 w - - 0 4"),
        Board("4k3/8/8/2r5/8/8/6R1/4K3 b - - 0 4"),
        Board("4k3/2r5/8/8/8/8/6R1/4K3 w - - 0 5"),
        Board("4k3/2r5/8/8/6R1/8/8/4K3 b - - 0 5"),
        Board("4k3/8/8/2r5/6R1/8/8/4K3 w - - 0 6"),
        Board("4k3/8/8/2r5/8/8/6R1/4K3 b - - 0 6"),
      };
      Board last_board("4k3/2r5/8/8/8/8/6R1/4K3 w - - 0 7");
      Board board("4k3/2r5/8/8/8/8/6R1/4K3 w - - 0 1");
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), repetitions(board, boards, &last_board));
    }

    void ChessTests::test_fold_squares_function_folds_squares()
    {
      vector<Square> squares;
      int sum = fold_squares((static_cast<Bitboard>(0x425a0014) << 32) | static_cast<Bitboard>(0x00a54218), 0, [&](int sum, Square squ) {
        squares.push_back(squ);
        return sum + 1;
      });
      CPPUNIT_ASSERT_EQUAL(16, sum);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(16), squares.size());
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D1));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), E1));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), B2));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), G2));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), A3));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), C3));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), F3));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), H3));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), C5));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), E5));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), B7));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D7));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), E7));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), G7));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), B8));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), G8));
    }

    void ChessTests::test_fold_pawn_capture_squares_function_folds_squares_for_white_side()
    {
      vector<Square> squares;
      int sum = fold_pawn_capture_squares(Side::WHITE, C3, 0, [&](int sum, Square squ) {
        squares.push_back(squ);
        return sum + 1;
      });
      CPPUNIT_ASSERT_EQUAL(2, sum);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), squares.size());
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), B4));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D4));
    }
    
    void ChessTests::test_fold_pawn_capture_squares_function_folds_squares_for_black_side()
    {
      vector<Square> squares;
      int sum = fold_pawn_capture_squares(Side::BLACK, E5, 0, [&](int sum, Square squ) {
        squares.push_back(squ);
        return sum + 1;
      });
      CPPUNIT_ASSERT_EQUAL(2, sum);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), squares.size());
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D4));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), F4));
    }

    void ChessTests::test_fold_pawn_squares_function_folds_squares_for_white_side_and_start_square()
    {
      vector<Square> squares;
      int sum = fold_pawn_squares(Side::WHITE, E2, 0, [&](int sum, Square squ) {
        squares.push_back(squ);
        return make_pair(sum + 1, true);
      });
      CPPUNIT_ASSERT_EQUAL(2, sum);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), squares.size());
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), E3));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), E4));
    }

    void ChessTests::test_fold_pawn_squares_function_folds_squares_for_black_side_and_start_square()
    {
      vector<Square> squares;
      int sum = fold_pawn_squares(Side::BLACK, D7, 0, [&](int sum, Square squ) {
        squares.push_back(squ);
        return make_pair(sum + 1, true);
      });
      CPPUNIT_ASSERT_EQUAL(2, sum);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), squares.size());
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D6));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D5));
    }

    void ChessTests::test_fold_pawn_squares_function_folds_squares_for_white_side_and_non_start_square()
    {
      vector<Square> squares;
      int sum = fold_pawn_squares(Side::WHITE, C3, 0, [&](int sum, Square squ) {
        squares.push_back(squ);
        return make_pair(sum + 1, true);
      });
      CPPUNIT_ASSERT_EQUAL(1, sum);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), squares.size());
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), C4));
    }

    void ChessTests::test_fold_pawn_squares_function_folds_squares_for_black_side_and_non_start_square()
    {
      vector<Square> squares;
      int sum = fold_pawn_squares(Side::BLACK, E5, 0, [&](int sum, Square squ) {
        squares.push_back(squ);
        return make_pair(sum + 1, true);
      });
      CPPUNIT_ASSERT_EQUAL(1, sum);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), squares.size());
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), E4));
    }

    void ChessTests::test_fold_knight_squares_function_folds_squares()
    {
      vector<Square> squares;
      int sum = fold_knight_squares(B6, 0, [&](int sum, Square squ) {
        squares.push_back(squ);
        return sum + 1;
      });
      CPPUNIT_ASSERT_EQUAL(6, sum);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(6), squares.size());
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), A8));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), C8));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D7));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D5));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), A4));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), C4));
    }

    void ChessTests::test_fold_king_squares_function_folds_squares()
    {
      vector<Square> squares;
      int sum = fold_king_squares(E1, 0, [&](int sum, Square squ) {
        squares.push_back(squ);
        return sum + 1;
      });
      CPPUNIT_ASSERT_EQUAL(5, sum);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), squares.size());
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D2));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), E2));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), F2));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D1));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), F1));
    }

    void ChessTests::test_fold_bishop_slides_function_folds_slides()
    {
      vector<Square> squares;
      int sum = fold_bishop_slides(B7, 0, [&](int sum) {
        return sum + 100;
      }, [&](int sum, Square squ) {
        squares.push_back(squ);
        return make_pair(sum + 1, squ != E4);
      });
      CPPUNIT_ASSERT_EQUAL(406, sum);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(6), squares.size());
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), A8));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), C8));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), A6));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), C6));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D5));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), E4));
    }

    void ChessTests::test_fold_rook_slides_function_folds_slides()
    {
      vector<Square> squares;
      int sum = fold_rook_slides(B6, 0, [&](int sum) {
        return sum + 100;
      }, [&](int sum, Square squ) {
        squares.push_back(squ);
        return make_pair(sum + 1, squ != F6 && squ != B3);
      });
      CPPUNIT_ASSERT_EQUAL(410, sum);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), squares.size());
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), B7));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), B8));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), A6));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), C6));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D6));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), E6));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), F6));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), B5));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), B4));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), B3));
    }

    void ChessTests::test_fold_queen_slides_function_folds_slides()
    {
      vector<Square> squares;
      int sum = fold_queen_slides(G3, 0, [&](int sum) {
        return sum + 100;
      }, [&](int sum, Square squ) {
        squares.push_back(squ);
        return make_pair(sum + 1, squ != D6 && squ != G6 && squ != C3);
      });
      CPPUNIT_ASSERT_EQUAL(817, sum);
      CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(17), squares.size());
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), F4));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), E5));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D6));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), G4));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), G5));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), G6));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), F3));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), E3));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), D3));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), C3));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), H3));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), F2));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), E1));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), G2));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), G1));
      CPPUNIT_ASSERT(squares.end() != find(squares.begin(), squares.end(), H2));
    }
  }
}
