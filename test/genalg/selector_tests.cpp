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
#include <cstddef>
#include "selector_tests.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      void SelectorTests::test_selector_selects_best_individual_for_empty_excluded_index_set()
      {
        static int gene_tabs[6][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 },
          { 26, 27, 28, 29, 30 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 6; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        _M_results->start = string(" ");
                                                //        1
                                                //  6 3 4 0 3 6
        _M_results->game_results.push_back(string("xx 0 1 0 1 0")); // 4 + 6 = 10
        _M_results->game_results.push_back(string(" 0xx 1 0 1 0")); // 4 + 3 = 7
        _M_results->game_results.push_back(string(" 0 1xx 0 = 1")); // 5 + 4 = 9
        _M_results->game_results.push_back(string(" 1 1 1xx 1 1")); // 10 + 10 = 20
        _M_results->game_results.push_back(string(" 1 = 0 0xx 0")); // 3 + 3 = 6
        _M_results->game_results.push_back(string(" 0 1 0 0 0xx")); // 2 + 6 = 8
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->update(0, individuals));
        CPPUNIT_ASSERT_EQUAL(3, _M_selector->select_best_individual_for_excluded_indices(set<int>()));
      }

      void SelectorTests::test_selector_selects_best_individual_for_excluded_index_set()
      {
        static int gene_tabs[6][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 },
          { 26, 27, 28, 29, 30 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 6; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        _M_results->start = string(" ");
                                                //
                                                //  6 3 9 6 4 8
        _M_results->game_results.push_back(string("xx 1 0 1 1 0")); // 6 + 6 = 12
        _M_results->game_results.push_back(string(" 0xx = 0 0 0")); // 1 + 3 = 4
        _M_results->game_results.push_back(string(" 1 1xx 1 1 1")); // 10 + 9 = 19
        _M_results->game_results.push_back(string(" 0 0 0xx 1 0")); // 2 + 6 = 8
        _M_results->game_results.push_back(string(" 1 1 0 0xx 0")); // 4 + 4 = 8
        _M_results->game_results.push_back(string(" 0 = 0 0 0xx")); // 1 + 8 = 9
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->update(0, individuals));
        set<int> excluded_indices { 2, 5 };
        CPPUNIT_ASSERT_EQUAL(0, _M_selector->select_best_individual_for_excluded_indices(excluded_indices));
      }

      void SelectorTests::test_selector_does_not_select_best_individual_for_full_excluded_index_set()
      {
        static int gene_tabs[6][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 },
          { 26, 27, 28, 29, 30 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 6; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        _M_results->start = string(" ");
                                                //          1
                                                //  6 4 3 5 0 6
        _M_results->game_results.push_back(string("xx 0 0 1 1 0")); // 4 + 6 = 10
        _M_results->game_results.push_back(string(" 0xx 1 = 1 1")); // 6 + 4 = 10
        _M_results->game_results.push_back(string(" 0 1xx 0 1 0")); // 4 + 3 = 7
        _M_results->game_results.push_back(string(" 1 1 =xx 1 0")); // 5 + 5 = 10
        _M_results->game_results.push_back(string(" 1 1 1 1xx 1")); // 10 + 10 = 20
        _M_results->game_results.push_back(string(" 0 0 1 0 1xx")); // 4 + 6 = 10
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->update(0, individuals));
        set<int> excluded_indices { 0, 1, 2, 3, 4, 5 };
        CPPUNIT_ASSERT_EQUAL(-1, _M_selector->select_best_individual_for_excluded_indices(excluded_indices));
      }

      void SelectorTests::test_selector_selects_individual_for_empty_excluded_index_set()
      {
        static int gene_tabs[6][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 },
          { 26, 27, 28, 29, 30 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 6; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        _M_results->start = string(" ");
                                                //        1
                                                //  6 3 4 0 3 6
        _M_results->game_results.push_back(string("xx 0 1 0 1 0")); // 4 + 6 = 10
        _M_results->game_results.push_back(string(" 0xx 1 0 1 0")); // 4 + 3 = 7
        _M_results->game_results.push_back(string(" 0 1xx 0 = 1")); // 5 + 4 = 9
        _M_results->game_results.push_back(string(" 1 1 1xx 1 1")); // 10 + 10 = 20
        _M_results->game_results.push_back(string(" 1 = 0 0xx 0")); // 3 + 3 = 6
        _M_results->game_results.push_back(string(" 0 1 0 0 0xx")); // 2 + 6 = 8
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->update(0, individuals));
        int i = _M_selector->select_individual_for_excluded_indices(set<int>());
        CPPUNIT_ASSERT(i >= 0 && i <= 5);
      }

      void SelectorTests::test_selector_selects_individual_for_excluded_index_set()
      {
        static int gene_tabs[6][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 },
          { 26, 27, 28, 29, 30 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 6; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        _M_results->start = string(" ");
                                                //
                                                //  6 3 9 6 4 8
        _M_results->game_results.push_back(string("xx 1 0 1 1 0")); // 6 + 6 = 12
        _M_results->game_results.push_back(string(" 0xx = 0 0 0")); // 1 + 3 = 4
        _M_results->game_results.push_back(string(" 1 1xx 1 1 1")); // 10 + 9 = 19
        _M_results->game_results.push_back(string(" 0 0 0xx 1 0")); // 2 + 6 = 8
        _M_results->game_results.push_back(string(" 1 1 0 0xx 0")); // 4 + 4 = 8
        _M_results->game_results.push_back(string(" 0 = 0 0 0xx")); // 1 + 8 = 9
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->update(0, individuals));
        set<int> excluded_indices { 2, 5 };
        int i = _M_selector->select_individual_for_excluded_indices(excluded_indices);
        CPPUNIT_ASSERT(i >= 0 && i <= 5 && i != 2 && i != 5);
      }

      void SelectorTests::test_selector_does_not_select_individual_for_full_excluded_index_set()
      {
        static int gene_tabs[6][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 },
          { 26, 27, 28, 29, 30 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 6; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        _M_results->start = string(" ");
                                                //          1
                                                //  6 4 3 5 0 6
        _M_results->game_results.push_back(string("xx 0 0 1 1 0")); // 4 + 6 = 10
        _M_results->game_results.push_back(string(" 0xx 1 = 1 1")); // 6 + 4 = 10
        _M_results->game_results.push_back(string(" 0 1xx 0 1 0")); // 4 + 3 = 7
        _M_results->game_results.push_back(string(" 1 1 =xx 1 0")); // 5 + 5 = 10
        _M_results->game_results.push_back(string(" 1 1 1 1xx 1")); // 10 + 10 = 20
        _M_results->game_results.push_back(string(" 0 0 1 0 1xx")); // 4 + 6 = 10
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->update(0, individuals));
        set<int> excluded_indices { 0, 1, 2, 3, 4, 5 };
        CPPUNIT_ASSERT_EQUAL(-1, _M_selector->select_individual_for_excluded_indices(excluded_indices));
      }

      void SelectorTests::test_selector_selects_best_individuals()
      {
        static int gene_tabs[6][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 },
          { 26, 27, 28, 29, 30 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 6; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        _M_results->start = string(" ");
                                                //    1
                                                //  4 0 6 6 6 4
        _M_results->game_results.push_back(string("xx 0 0 0 0 0")); // 0 + 4 = 4
        _M_results->game_results.push_back(string(" 1xx 1 1 1 1")); // 10 + 10 = 20
        _M_results->game_results.push_back(string(" 0 0xx 0 1 1")); // 4 + 6 = 10
        _M_results->game_results.push_back(string(" 1 0 =xx 0 1")); // 5 + 6 = 11
        _M_results->game_results.push_back(string(" 1 0 = 0xx 0")); // 3 + 6 = 9
        _M_results->game_results.push_back(string(" 0 0 0 1 0xx")); // 2 + 4 = 6
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->update(0, individuals));
        vector<int> indices;
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->select_best_individuals(3, indices));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), indices.size());
        CPPUNIT_ASSERT_EQUAL(1, indices[0]);
        CPPUNIT_ASSERT_EQUAL(3, indices[1]);
        CPPUNIT_ASSERT_EQUAL(2, indices[2]);
      }
      
      void SelectorTests::test_selector_does_not_select_best_individuals_for_best_individuals_greater_than_population()
      {
        static int gene_tabs[6][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 },
          { 26, 27, 28, 29, 30 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 6; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        _M_results->start = string(" ");
                                                //          1
                                                //  6 4 8 4 0 6
        _M_results->game_results.push_back(string("xx 1 0 = 0 0")); // 3 + 6 = 9
        _M_results->game_results.push_back(string(" 0xx 0 = 0 0")); // 1 + 4 = 5
        _M_results->game_results.push_back(string(" 0 0xx 1 0 1")); // 4 + 8 = 12
        _M_results->game_results.push_back(string(" 1 0 0xx 0 0")); // 2 + 4 = 6
        _M_results->game_results.push_back(string(" 1 1 1 1xx 1")); // 10 + 10 = 20
        _M_results->game_results.push_back(string(" 0 1 0 0 0xx")); // 2 + 6 = 8
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->update(0, individuals));
        vector<int> indices;
        CPPUNIT_ASSERT_EQUAL(false, _M_selector->select_best_individuals(7, indices));
      }

      void SelectorTests::test_selector_selects_parents_for_even_number_of_children()
      {
        static int gene_tabs[6][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 },
          { 26, 27, 28, 29, 30 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 6; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        _M_results->start = string(" ");
                                                //    1
                                                //  4 0 6 6 6 4
        _M_results->game_results.push_back(string("xx 0 0 0 0 0")); // 0 + 4 = 4
        _M_results->game_results.push_back(string(" 1xx 1 1 1 1")); // 10 + 10 = 20
        _M_results->game_results.push_back(string(" 0 0xx 0 1 1")); // 4 + 6 = 10
        _M_results->game_results.push_back(string(" 1 0 =xx 0 1")); // 5 + 6 = 11
        _M_results->game_results.push_back(string(" 1 0 = 0xx 0")); // 3 + 6 = 9
        _M_results->game_results.push_back(string(" 0 0 0 1 0xx")); // 2 + 4 = 6
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->update(0, individuals));
        vector<ParentPair> pairs;
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->select_parents(4, pairs));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), pairs.size());
        CPPUNIT_ASSERT(pairs[0].first_parent >= 0 && pairs[0].first_parent <= 5);
        CPPUNIT_ASSERT(pairs[0].second_parent >= 0 && pairs[0].second_parent <= 5 && pairs[0].second_parent != pairs[0].first_parent);
        CPPUNIT_ASSERT(pairs[1].first_parent >= 0 && pairs[1].first_parent <= 5);
        CPPUNIT_ASSERT(pairs[1].second_parent >= 0 && pairs[1].second_parent <= 5 && pairs[1].second_parent != pairs[1].first_parent);
      }

      void SelectorTests::test_selector_selects_parents_for_odd_number_of_children()
      {
        static int gene_tabs[6][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 },
          { 26, 27, 28, 29, 30 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 6; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        _M_results->start = string(" ");
                                                //          1
                                                //  6 4 8 4 0 6
        _M_results->game_results.push_back(string("xx 1 0 = 0 0")); // 3 + 6 = 9
        _M_results->game_results.push_back(string(" 0xx 0 = 0 0")); // 1 + 4 = 5
        _M_results->game_results.push_back(string(" 0 0xx 1 0 1")); // 4 + 8 = 12
        _M_results->game_results.push_back(string(" 1 0 0xx 0 0")); // 2 + 4 = 6
        _M_results->game_results.push_back(string(" 1 1 1 1xx 1")); // 10 + 10 = 20
        _M_results->game_results.push_back(string(" 0 1 0 0 0xx")); // 2 + 6 = 8
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->update(0, individuals));
        vector<ParentPair> pairs;
        CPPUNIT_ASSERT_EQUAL(true, _M_selector->select_parents(3, pairs));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), pairs.size());
        CPPUNIT_ASSERT(pairs[0].first_parent >= 0 && pairs[0].first_parent <= 5);
        CPPUNIT_ASSERT(pairs[0].second_parent >= 0 && pairs[0].second_parent <= 5 && pairs[0].second_parent != pairs[0].first_parent);
        CPPUNIT_ASSERT(pairs[1].first_parent >= 0 && pairs[1].first_parent <= 5);
        CPPUNIT_ASSERT(pairs[1].second_parent >= 0 && pairs[1].second_parent <= 5 && pairs[1].second_parent != pairs[1].first_parent);
      }
    }
  }
}
