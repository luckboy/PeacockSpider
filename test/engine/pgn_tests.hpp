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
#ifndef _PGN_TESTS_HPP
#define _PGN_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

namespace peacockspider
{
  namespace test
  {
    class PGNTests : public CppUnit::TestFixture
    {
      CPPUNIT_TEST_SUITE(PGNTests);
      CPPUNIT_TEST(test_write_pgn_function_writes_game);
      CPPUNIT_TEST(test_write_pgn_function_writes_game_for_white_win);
      CPPUNIT_TEST(test_write_pgn_function_writes_game_for_black_win);
      CPPUNIT_TEST(test_write_pgn_function_writes_game_for_draw);
      CPPUNIT_TEST(test_write_pgn_function_writes_game_for_fen_and_white_side);
      CPPUNIT_TEST(test_write_pgn_function_writes_game_for_fen_and_black_side);
      CPPUNIT_TEST(test_write_pgn_function_writes_game_for_move_characters_greater_than_80);
      CPPUNIT_TEST_SUITE_END();
    public:
      void setUp();

      void tearDown();

      void test_write_pgn_function_writes_game();
      void test_write_pgn_function_writes_game_for_white_win();
      void test_write_pgn_function_writes_game_for_black_win();
      void test_write_pgn_function_writes_game_for_draw();
      void test_write_pgn_function_writes_game_for_fen_and_white_side();
      void test_write_pgn_function_writes_game_for_fen_and_black_side();
      void test_write_pgn_function_writes_game_for_move_characters_greater_than_80();
    };
  }
}

#endif
