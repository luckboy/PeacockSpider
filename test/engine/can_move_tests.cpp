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
#include "can_move_tests.hpp"
#include "chess.hpp"

using namespace std;

namespace peacockspider
{
  namespace test
  {
    CPPUNIT_TEST_SUITE_REGISTRATION(CANMoveTests);

    void CANMoveTests::setUp() {}

    void CANMoveTests::tearDown() {}

    void CANMoveTests::test_can_move_set_method_sets_move()
    {
      CANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("e2e4"));
      CPPUNIT_ASSERT(CANMove(E2, E4, PromotionPiece::NONE) == move);
    }
    
    void CANMoveTests::test_can_move_set_method_sets_move_with_promotion_piece()
    {
      CANMove move;
      CPPUNIT_ASSERT_EQUAL(true, move.set("g7g8q"));
      CPPUNIT_ASSERT(CANMove(G7, G8, PromotionPiece::QUEEN) == move);
    }
    
    void CANMoveTests::test_can_move_set_method_complains_on_incorrect_source_square()
    {
      CANMove move;
      CPPUNIT_ASSERT_EQUAL(false, move.set("z2e4"));
    }
    
    void CANMoveTests::test_can_move_set_method_complains_on_incorrect_destination_square()
    {
      CANMove move;
      CPPUNIT_ASSERT_EQUAL(false, move.set("b1c9"));
    }

    void CANMoveTests::test_can_move_set_method_complains_on_incorrect_promotion_piece()
    {
      CANMove move;
      CPPUNIT_ASSERT_EQUAL(false, move.set("a2a1p"));
    }

    void CANMoveTests::test_can_move_to_string_method_converts_move_to_string()
    {
      CANMove move("g1f3");
      CPPUNIT_ASSERT_EQUAL(string("g1f3"), move.to_string()); 
    }

    void CANMoveTests::test_can_move_to_string_method_converts_move_with_promotion_piece_to_string()
    {
      CANMove move("b7a8n");
      CPPUNIT_ASSERT_EQUAL(string("b7a8n"), move.to_string());
    }
  }
}
