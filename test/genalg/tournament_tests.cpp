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
#include "tournament_tests.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      void TournamentTests::test_tournament_plays_tournament()
      {
        static int param_tab[5][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 }
        };
        vector<shared_ptr<int []>> param_list;
        for(size_t i = 0; i < 5; i++) {
          param_list.push_back(shared_ptr<int []>(new int[5]));
          copy(param_tab[i], param_tab[i] + 5, param_list.back().get());
        }
        _M_results->start = string(" ");
                                                //  4 3 7 1 6
        _M_results->game_results.push_back(string("xx 0 = = 0")); // 2 + 4 = 6
        _M_results->game_results.push_back(string(" 0xx 0 1 0")); // 2 + 3 = 5
        _M_results->game_results.push_back(string(" 1 1xx 1 1")); // 8 + 7 = 15 
        _M_results->game_results.push_back(string(" 1 = 0xx 0")); // 3 + 1 = 4
        _M_results->game_results.push_back(string(" 0 1 0 1xx")); // 4 + 6 = 10
        CPPUNIT_ASSERT_EQUAL(true, _M_tournament->play(0, param_list));
        CPPUNIT_ASSERT_EQUAL(5, _M_tournament->result().player_count());
        CPPUNIT_ASSERT_EQUAL(6, _M_tournament->result().score(0));
        CPPUNIT_ASSERT_EQUAL(5, _M_tournament->result().score(1));
        CPPUNIT_ASSERT_EQUAL(15, _M_tournament->result().score(2));
        CPPUNIT_ASSERT_EQUAL(4, _M_tournament->result().score(3));
        CPPUNIT_ASSERT_EQUAL(10, _M_tournament->result().score(4));
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().sorted_player_index(0));
        CPPUNIT_ASSERT_EQUAL(4, _M_tournament->result().sorted_player_index(1));
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().sorted_player_index(2));
        CPPUNIT_ASSERT_EQUAL(1, _M_tournament->result().sorted_player_index(3));
        CPPUNIT_ASSERT_EQUAL(3, _M_tournament->result().sorted_player_index(4));
        // XX
        // XX
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(0, 1).scores[0]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(0, 1).scores[1]);
        CPPUNIT_ASSERT_EQUAL(1, _M_tournament->result().crosstable_match_result(0, 2).scores[0]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(0, 2).scores[1]);
        CPPUNIT_ASSERT_EQUAL(1, _M_tournament->result().crosstable_match_result(0, 3).scores[0]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(0, 3).scores[1]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(0, 4).scores[0]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(0, 4).scores[1]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(1, 0).scores[0]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(1, 0).scores[1]);
        // XX
        // XX
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(1, 2).scores[0]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(1, 2).scores[1]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(1, 3).scores[0]);
        CPPUNIT_ASSERT_EQUAL(1, _M_tournament->result().crosstable_match_result(1, 3).scores[1]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(1, 4).scores[0]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(1, 4).scores[1]);
        CPPUNIT_ASSERT_EQUAL(1, _M_tournament->result().crosstable_match_result(2, 0).scores[0]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(2, 0).scores[1]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(2, 1).scores[0]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(2, 1).scores[1]);
        // XX
        // XX
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(2, 3).scores[0]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(2, 3).scores[1]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(2, 4).scores[0]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(2, 4).scores[1]);
        CPPUNIT_ASSERT_EQUAL(1, _M_tournament->result().crosstable_match_result(3, 0).scores[0]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(3, 0).scores[1]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(3, 1).scores[0]);
        CPPUNIT_ASSERT_EQUAL(1, _M_tournament->result().crosstable_match_result(3, 1).scores[1]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(3, 2).scores[0]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(3, 2).scores[1]);
        // XX
        // XX
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(3, 4).scores[0]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(3, 4).scores[1]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(4, 0).scores[0]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(4, 0).scores[1]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(4, 1).scores[0]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(4, 1).scores[1]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(4, 2).scores[0]);
        CPPUNIT_ASSERT_EQUAL(0, _M_tournament->result().crosstable_match_result(4, 2).scores[1]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(4, 3).scores[0]);
        CPPUNIT_ASSERT_EQUAL(2, _M_tournament->result().crosstable_match_result(4, 3).scores[1]);
        // XX
        // XX
      }

      void TournamentTests::test_tournament_does_not_play_tournament_for_start_error()
      {
        static int param_tab[5][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 }
        };
        vector<shared_ptr<int []>> param_list;
        for(size_t i = 0; i < 5; i++) {
          param_list.push_back(shared_ptr<int []>(new int[5]));
          copy(param_tab[i], param_tab[i] + 5, param_list.back().get());
        }
        _M_results->start = string("e");
                                                //  4 6 5 4 3
        _M_results->game_results.push_back(string("xx 1 0 0 0")); // 2 + 4 = 6
        _M_results->game_results.push_back(string(" 1xx 1 1 1")); // 8 + 6 = 14
        _M_results->game_results.push_back(string(" 0 0xx 0 1")); // 2 + 5 = 7
        _M_results->game_results.push_back(string(" 1 0 =xx =")); // 4 + 4 = 8
        _M_results->game_results.push_back(string(" 0 0 0 1xx")); // 2 + 3 = 5
        CPPUNIT_ASSERT_EQUAL(false, _M_tournament->play(0, param_list));
      }

      void TournamentTests::test_tournament_does_not_play_tournament_for_game_error()
      {
        static int param_tab[5][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 }
        };
        vector<shared_ptr<int []>> param_list;
        for(size_t i = 0; i < 5; i++) {
          param_list.push_back(shared_ptr<int []>(new int[5]));
          copy(param_tab[i], param_tab[i] + 5, param_list.back().get());
        }
        _M_results->start = string(" ");
                                                //  4 6 4 6 5
        _M_results->game_results.push_back(string("xx 0 0 0 0")); // 0 + 4 = 4
        _M_results->game_results.push_back(string(" 1xx 1 = 0")); // 5 + 6 = 11
        _M_results->game_results.push_back(string(" 0 0xx e 1")); // 3 + 5 = 8
        _M_results->game_results.push_back(string(" 1 1 1xx =")); // 7 + 6 = 13
        _M_results->game_results.push_back(string(" 0 0 0 0xx")); // 0 + 5 = 5
        CPPUNIT_ASSERT_EQUAL(false, _M_tournament->play(0, param_list));
      }
    }
  }
}
