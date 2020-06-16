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
#include "move_pair_list_tests.hpp"
#include "chess.hpp"

using namespace std;

namespace peacockspider
{
  namespace test
  {
    CPPUNIT_TEST_SUITE_REGISTRATION(MovePairListTests);

    void MovePairListTests::setUp() {}

    void MovePairListTests::tearDown() {}

    void MovePairListTests::test_move_pair_list_select_sort_move_method_sorts_move_for_first_index()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE), 100));
      move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE), 200));
      move_pairs.add_move_pair(MovePair(Move(Piece::KNIGHT, B1, A3, PromotionPiece::NONE), 300));
      move_pairs.add_move_pair(MovePair(Move(Piece::KNIGHT, B2, C3, PromotionPiece::NONE), 50));
      move_pairs.select_sort_move(0);
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, B1, A3, PromotionPiece::NONE) == move_pairs[0].move);
      CPPUNIT_ASSERT_EQUAL(300, move_pairs[0].score);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE) == move_pairs[1].move);
      CPPUNIT_ASSERT_EQUAL(200, move_pairs[1].score);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE) == move_pairs[2].move);
      CPPUNIT_ASSERT_EQUAL(100, move_pairs[2].score);
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, B2, C3, PromotionPiece::NONE) == move_pairs[3].move);
      CPPUNIT_ASSERT_EQUAL(50, move_pairs[3].score);
    }
    
    void MovePairListTests::test_move_pair_list_select_sort_move_method_sorts_move_for_no_better()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, D2, D3, PromotionPiece::NONE), 600));
      move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, D2, D4, PromotionPiece::NONE), 300));
      move_pairs.add_move_pair(MovePair(Move(Piece::KNIGHT, G1, F3, PromotionPiece::NONE), 100));
      move_pairs.add_move_pair(MovePair(Move(Piece::KNIGHT, G2, H3, PromotionPiece::NONE), 50));
      move_pairs.select_sort_move(1);
      CPPUNIT_ASSERT(Move(Piece::PAWN, D2, D3, PromotionPiece::NONE) == move_pairs[0].move);
      CPPUNIT_ASSERT_EQUAL(600, move_pairs[0].score);
      CPPUNIT_ASSERT(Move(Piece::PAWN, D2, D4, PromotionPiece::NONE) == move_pairs[1].move);
      CPPUNIT_ASSERT_EQUAL(300, move_pairs[1].score);
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, G1, F3, PromotionPiece::NONE) == move_pairs[2].move);
      CPPUNIT_ASSERT_EQUAL(100, move_pairs[2].score);
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, G2, H3, PromotionPiece::NONE) == move_pairs[3].move);
      CPPUNIT_ASSERT_EQUAL(50, move_pairs[3].score);
    }

    void MovePairListTests::test_move_pair_list_select_sort_move_method_sorts_move_for_better()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE), 600));
      move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE), 400));
      move_pairs.add_move_pair(MovePair(Move(Piece::KNIGHT, B1, A3, PromotionPiece::NONE), 50));
      move_pairs.add_move_pair(MovePair(Move(Piece::KNIGHT, B2, C3, PromotionPiece::NONE), 200));
      move_pairs.add_move_pair(MovePair(Move(Piece::KNIGHT, G2, H3, PromotionPiece::NONE), 40));
      move_pairs.select_sort_move(2);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE) == move_pairs[0].move);
      CPPUNIT_ASSERT_EQUAL(600, move_pairs[0].score);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE) == move_pairs[1].move);
      CPPUNIT_ASSERT_EQUAL(400, move_pairs[1].score);
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, B2, C3, PromotionPiece::NONE) == move_pairs[2].move);
      CPPUNIT_ASSERT_EQUAL(200, move_pairs[2].score);
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, B1, A3, PromotionPiece::NONE) == move_pairs[3].move);
      CPPUNIT_ASSERT_EQUAL(50, move_pairs[3].score);
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, G2, H3, PromotionPiece::NONE) == move_pairs[4].move);
      CPPUNIT_ASSERT_EQUAL(40, move_pairs[4].score);
    }
    
    void MovePairListTests::test_move_pair_list_select_sort_move_method_sorts_move_for_better_better()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE), 600));
      move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE), 50));
      move_pairs.add_move_pair(MovePair(Move(Piece::KNIGHT, B1, A3, PromotionPiece::NONE), 100));
      move_pairs.add_move_pair(MovePair(Move(Piece::KNIGHT, B2, C3, PromotionPiece::NONE), 200));
      move_pairs.add_move_pair(MovePair(Move(Piece::KNIGHT, G2, H3, PromotionPiece::NONE), 40));
      move_pairs.select_sort_move(1);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE) == move_pairs[0].move);
      CPPUNIT_ASSERT_EQUAL(600, move_pairs[0].score);
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, B2, C3, PromotionPiece::NONE) == move_pairs[1].move);
      CPPUNIT_ASSERT_EQUAL(200, move_pairs[1].score);
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, B1, A3, PromotionPiece::NONE) == move_pairs[2].move);
      CPPUNIT_ASSERT_EQUAL(100, move_pairs[2].score);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE) == move_pairs[3].move);
      CPPUNIT_ASSERT_EQUAL(50, move_pairs[3].score);
      CPPUNIT_ASSERT(Move(Piece::KNIGHT, G2, H3, PromotionPiece::NONE) == move_pairs[4].move);
      CPPUNIT_ASSERT_EQUAL(40, move_pairs[4].score);
    }
  }
}
