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
#ifndef _TOURNAMENT_TESTS_HPP
#define _TOURNAMENT_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "test_table.hpp"
#include "tournament.hpp"

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      class TournamentTests : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(TournamentTests);
        CPPUNIT_TEST(test_tournament_plays_tournament);
        CPPUNIT_TEST(test_tournament_does_not_play_tournament_for_start_error);
        CPPUNIT_TEST(test_tournament_does_not_play_tournament_for_game_error);
        CPPUNIT_TEST_SUITE_END();
      protected:
        TestTableResults *_M_results;
        Tournament *_M_tournament;
      public:
        void test_tournament_plays_tournament();
        void test_tournament_does_not_play_tournament_for_start_error();
        void test_tournament_does_not_play_tournament_for_game_error();
      };
    }
  }
}

#endif
