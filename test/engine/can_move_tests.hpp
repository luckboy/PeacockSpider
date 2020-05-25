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
#ifndef _CAN_MOVE_TESTS_HPP
#define _CAN_MOVE_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

namespace peacockspider
{
  namespace test
  {
    class CANMoveTests : public CppUnit::TestFixture
    {
      CPPUNIT_TEST_SUITE(CANMoveTests);
      CPPUNIT_TEST(test_can_move_set_method_sets_move);
      CPPUNIT_TEST(test_can_move_set_method_sets_move_with_promotion_piece);
      CPPUNIT_TEST(test_can_move_set_method_complains_on_incorrect_source_square);
      CPPUNIT_TEST(test_can_move_set_method_complains_on_incorrect_destination_square);
      CPPUNIT_TEST(test_can_move_set_method_complains_on_incorrect_promotion_piece);
      CPPUNIT_TEST(test_can_move_to_string_method_converts_move_to_string);
      CPPUNIT_TEST(test_can_move_to_string_method_converts_move_with_promotion_piece_to_string);
      CPPUNIT_TEST_SUITE_END();
    public:
      void setUp();

      void tearDown();

      void test_can_move_set_method_sets_move();
      void test_can_move_set_method_sets_move_with_promotion_piece();
      void test_can_move_set_method_complains_on_incorrect_source_square();
      void test_can_move_set_method_complains_on_incorrect_destination_square();
      void test_can_move_set_method_complains_on_incorrect_promotion_piece();
      void test_can_move_to_string_method_converts_move_to_string();
      void test_can_move_to_string_method_converts_move_with_promotion_piece_to_string();
    };
  }
}

#endif
