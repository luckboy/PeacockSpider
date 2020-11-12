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
#include <cstddef>
#include "gen_alg_iter_tests.hpp"
#include "gen_alg.hpp"
#include "gen_alg_vars.hpp"
#include "test_gene_ranges.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      CPPUNIT_TEST_SUITE_REGISTRATION(GeneticAlgorithmIterationTests);

      namespace
      {
        size_t saved_max_gene_count;
        Range *saved_gene_ranges;
      }

      void GeneticAlgorithmIterationTests::setUp()
      {
        saved_max_gene_count = max_gene_count;
        saved_gene_ranges = gene_ranges;
        max_gene_count = 5;
        gene_ranges = test_gene_ranges;
        _M_results = new TestTableResults;
        _M_tournament = new SingleTournament(8, [this]() {
          return new TestTable(*_M_results);
        });
        _M_fitness_function = new FitnessFunction(_M_tournament);
        _M_selector = new RouletteWheelSelector(_M_fitness_function);
      }

      void GeneticAlgorithmIterationTests::tearDown()
      {
        delete _M_selector;
        delete _M_fitness_function;
        delete _M_tournament;
        delete _M_results;
        max_gene_count = saved_max_gene_count;
        gene_ranges = saved_gene_ranges;
      }

      void GeneticAlgorithmIterationTests::test_genetic_algorithm_iterate_function_iterates()
      {
        static int gene_tabs[8][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 },
          { 26, 27, 28, 29, 30 },
          { 31, 32, 33, 34, 35 },
          { 36, 37, 38, 39, 40 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 8; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        _M_results->start = string(" ");
                                                //  1 1     1     1
                                                //  2 0 9 8 0 5 8 2
        _M_results->game_results.push_back(string("xx 0 0 0 1 0 0 0")); // 2 + 12 = 14
        _M_results->game_results.push_back(string(" 0xx 0 1 0 1 1 0")); // 6 + 10 = 16
        _M_results->game_results.push_back(string(" 0 0xx 0 1 0 = 0")); // 3 + 9 = 12
        _M_results->game_results.push_back(string(" 0 0 0xx 0 1 0 0")); // 2 + 8 = 10
        _M_results->game_results.push_back(string(" 1 1 1 1xx 1 1 1")); // 14 + 10 = 24
        _M_results->game_results.push_back(string(" 0 0 1 0 0xx = 0")); // 3 + 5 = 8
        _M_results->game_results.push_back(string(" 0 1 = 1 0 0xx 0")); // 5 + 8 = 13
        _M_results->game_results.push_back(string(" 0 0 0 0 0 = 0xx")); // 1 + 12 = 13
        vector<Individual> new_individuals;
        CPPUNIT_ASSERT_EQUAL(true, genetic_algorithm_iterate(_M_selector, 0, individuals, new_individuals, 2, 4, 4));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(8), new_individuals.size());
        CPPUNIT_ASSERT_EQUAL(4, new_individuals[0].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(-1, new_individuals[0].parent_pair.second_parent);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[4][0], new_individuals[0].genes[0]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[4][1], new_individuals[0].genes[1]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[4][2], new_individuals[0].genes[2]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[4][3], new_individuals[0].genes[3]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[4][4], new_individuals[0].genes[4]);
        CPPUNIT_ASSERT_EQUAL(1, new_individuals[1].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(-1, new_individuals[1].parent_pair.second_parent);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[1][0], new_individuals[1].genes[0]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[1][1], new_individuals[1].genes[1]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[1][2], new_individuals[1].genes[2]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[1][3], new_individuals[1].genes[3]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[1][4], new_individuals[1].genes[4]);
        CPPUNIT_ASSERT(new_individuals[2].parent_pair.first_parent >= 0 && new_individuals[2].parent_pair.first_parent <= 7);
        CPPUNIT_ASSERT(new_individuals[2].parent_pair.second_parent >= 0 && new_individuals[2].parent_pair.second_parent <= 7);
        CPPUNIT_ASSERT(new_individuals[2].parent_pair.first_parent != new_individuals[2].parent_pair.second_parent);
        CPPUNIT_ASSERT(new_individuals[2].genes[0] >= test_gene_ranges[0].min && new_individuals[2].genes[0] <= test_gene_ranges[0].max);
        CPPUNIT_ASSERT(new_individuals[2].genes[1] >= test_gene_ranges[1].min && new_individuals[2].genes[1] <= test_gene_ranges[1].max);
        CPPUNIT_ASSERT(new_individuals[2].genes[2] >= test_gene_ranges[2].min && new_individuals[2].genes[2] <= test_gene_ranges[2].max);
        CPPUNIT_ASSERT(new_individuals[2].genes[3] >= test_gene_ranges[3].min && new_individuals[2].genes[3] <= test_gene_ranges[3].max);
        CPPUNIT_ASSERT(new_individuals[2].genes[4] >= test_gene_ranges[4].min && new_individuals[2].genes[4] <= test_gene_ranges[4].max);
        CPPUNIT_ASSERT(new_individuals[3].parent_pair.first_parent >= 0 && new_individuals[3].parent_pair.first_parent <= 7);
        CPPUNIT_ASSERT(new_individuals[3].parent_pair.second_parent >= 0 && new_individuals[3].parent_pair.second_parent <= 7);
        CPPUNIT_ASSERT(new_individuals[3].parent_pair.first_parent != new_individuals[3].parent_pair.second_parent);
        CPPUNIT_ASSERT(new_individuals[3].genes[0] >= test_gene_ranges[0].min && new_individuals[3].genes[0] <= test_gene_ranges[0].max);
        CPPUNIT_ASSERT(new_individuals[3].genes[1] >= test_gene_ranges[1].min && new_individuals[3].genes[1] <= test_gene_ranges[1].max);
        CPPUNIT_ASSERT(new_individuals[3].genes[2] >= test_gene_ranges[2].min && new_individuals[3].genes[2] <= test_gene_ranges[2].max);
        CPPUNIT_ASSERT(new_individuals[3].genes[3] >= test_gene_ranges[3].min && new_individuals[3].genes[3] <= test_gene_ranges[3].max);
        CPPUNIT_ASSERT(new_individuals[3].genes[4] >= test_gene_ranges[4].min && new_individuals[3].genes[4] <= test_gene_ranges[4].max);
        CPPUNIT_ASSERT(new_individuals[4].parent_pair.first_parent >= 0 && new_individuals[4].parent_pair.first_parent <= 7);
        CPPUNIT_ASSERT(new_individuals[4].parent_pair.second_parent >= 0 && new_individuals[4].parent_pair.second_parent <= 7);
        CPPUNIT_ASSERT(new_individuals[4].parent_pair.first_parent != new_individuals[4].parent_pair.second_parent);
        CPPUNIT_ASSERT(new_individuals[4].genes[0] >= test_gene_ranges[0].min && new_individuals[4].genes[0] <= test_gene_ranges[0].max);
        CPPUNIT_ASSERT(new_individuals[4].genes[1] >= test_gene_ranges[1].min && new_individuals[4].genes[1] <= test_gene_ranges[1].max);
        CPPUNIT_ASSERT(new_individuals[4].genes[2] >= test_gene_ranges[2].min && new_individuals[4].genes[2] <= test_gene_ranges[2].max);
        CPPUNIT_ASSERT(new_individuals[4].genes[3] >= test_gene_ranges[3].min && new_individuals[4].genes[3] <= test_gene_ranges[3].max);
        CPPUNIT_ASSERT(new_individuals[4].genes[4] >= test_gene_ranges[4].min && new_individuals[4].genes[4] <= test_gene_ranges[4].max);
        CPPUNIT_ASSERT(new_individuals[5].parent_pair.first_parent >= 0 && new_individuals[5].parent_pair.first_parent <= 7);
        CPPUNIT_ASSERT(new_individuals[5].parent_pair.second_parent >= 0 && new_individuals[5].parent_pair.second_parent <= 7);
        CPPUNIT_ASSERT(new_individuals[5].parent_pair.first_parent != new_individuals[5].parent_pair.second_parent);
        CPPUNIT_ASSERT(new_individuals[5].genes[0] >= test_gene_ranges[0].min && new_individuals[5].genes[0] <= test_gene_ranges[0].max);
        CPPUNIT_ASSERT(new_individuals[5].genes[1] >= test_gene_ranges[1].min && new_individuals[5].genes[1] <= test_gene_ranges[1].max);
        CPPUNIT_ASSERT(new_individuals[5].genes[2] >= test_gene_ranges[2].min && new_individuals[5].genes[2] <= test_gene_ranges[2].max);
        CPPUNIT_ASSERT(new_individuals[5].genes[3] >= test_gene_ranges[3].min && new_individuals[5].genes[3] <= test_gene_ranges[3].max);
        CPPUNIT_ASSERT(new_individuals[5].genes[4] >= test_gene_ranges[4].min && new_individuals[5].genes[4] <= test_gene_ranges[4].max);
        CPPUNIT_ASSERT_EQUAL(-1, new_individuals[6].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(-1, new_individuals[6].parent_pair.second_parent);
        CPPUNIT_ASSERT(new_individuals[6].genes[0] >= test_gene_ranges[0].min && new_individuals[6].genes[0] <= test_gene_ranges[0].max);
        CPPUNIT_ASSERT(new_individuals[6].genes[1] >= test_gene_ranges[1].min && new_individuals[6].genes[1] <= test_gene_ranges[1].max);
        CPPUNIT_ASSERT(new_individuals[6].genes[2] >= test_gene_ranges[2].min && new_individuals[6].genes[2] <= test_gene_ranges[2].max);
        CPPUNIT_ASSERT(new_individuals[6].genes[3] >= test_gene_ranges[3].min && new_individuals[6].genes[3] <= test_gene_ranges[3].max);
        CPPUNIT_ASSERT(new_individuals[6].genes[4] >= test_gene_ranges[4].min && new_individuals[6].genes[4] <= test_gene_ranges[4].max);
        CPPUNIT_ASSERT_EQUAL(-1, new_individuals[7].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(-1, new_individuals[7].parent_pair.second_parent);
        CPPUNIT_ASSERT(new_individuals[7].genes[0] >= test_gene_ranges[0].min && new_individuals[7].genes[0] <= test_gene_ranges[0].max);
        CPPUNIT_ASSERT(new_individuals[7].genes[1] >= test_gene_ranges[1].min && new_individuals[7].genes[1] <= test_gene_ranges[1].max);
        CPPUNIT_ASSERT(new_individuals[7].genes[2] >= test_gene_ranges[2].min && new_individuals[7].genes[2] <= test_gene_ranges[2].max);
        CPPUNIT_ASSERT(new_individuals[7].genes[3] >= test_gene_ranges[3].min && new_individuals[7].genes[3] <= test_gene_ranges[3].max);
        CPPUNIT_ASSERT(new_individuals[7].genes[4] >= test_gene_ranges[4].min && new_individuals[7].genes[4] <= test_gene_ranges[4].max);
      }
      
      void GeneticAlgorithmIterationTests::test_genetic_algorithm_iterate_function_does_not_iterate_for_error()
      {
        static int gene_tabs[8][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 },
          { 26, 27, 28, 29, 30 },
          { 31, 32, 33, 34, 35 },
          { 36, 37, 38, 39, 40 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 8; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        _M_results->start = string("e");
                                                //  1   1 1   1 1
                                                //  0 8 1 2 7 0 0 8
        _M_results->game_results.push_back(string("xx 0 0 0 1 0 0 0")); // 2 + 10 = 12
        _M_results->game_results.push_back(string(" 0xx 0 0 = 1 0 1")); // 5 + 8 = 13
        _M_results->game_results.push_back(string(" 0 0xx 0 1 0 1 0")); // 4 + 11 = 15
        _M_results->game_results.push_back(string(" 1 1 1xx 1 1 0 1")); // 12 + 12 = 24
        _M_results->game_results.push_back(string(" 0 0 0 0xx 0 0 1")); // 2 + 7 = 9
        _M_results->game_results.push_back(string(" 0 1 0 0 0xx 1 0")); // 4 + 10 = 14
        _M_results->game_results.push_back(string(" 0 1 = 0 0 0xx 0")); // 3 + 10 = 13
        _M_results->game_results.push_back(string(" 1 0 0 1 0 0 0xx")); // 4 + 8 = 12
        vector<Individual> new_individuals;
        CPPUNIT_ASSERT_EQUAL(false, genetic_algorithm_iterate(_M_selector, 0, individuals, new_individuals, 2, 4, 4));
      }
    }
  }
}
