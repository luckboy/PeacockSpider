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
#include "duplication_tests.hpp"
#include "gen_alg.hpp"
#include "gen_alg_vars.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      CPPUNIT_TEST_SUITE_REGISTRATION(DuplicationTests);

      namespace
      {
        size_t saved_max_gene_count;
      }
      
      void DuplicationTests::setUp()
      {
        saved_max_gene_count = max_gene_count;
        max_gene_count = 5;
      }

      void DuplicationTests::tearDown()
      { max_gene_count = saved_max_gene_count; }

      void DuplicationTests::test_duplicate_individual_function_duplicates_individual()
      {
        static int gene_tabs[5][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 5; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        Individual new_individual;
        duplicate_individual(2, individuals, new_individual);
        CPPUNIT_ASSERT_EQUAL(2, new_individual.parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(-1, new_individual.parent_pair.second_parent);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[2][0], new_individual.genes[0]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[2][1], new_individual.genes[1]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[2][2], new_individual.genes[2]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[2][3], new_individual.genes[3]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[2][4], new_individual.genes[4]);
      }
      
      void DuplicationTests::test_duplicate_individuals_function_duplicates_individuals()
      {
        static int gene_tabs[5][5] = {
          { 1, 2, 3, 4, 5 },
          { 6, 7, 8, 9, 10 },
          { 11, 12, 13, 14, 15 },
          { 16, 17, 18, 19, 20 },
          { 21, 22, 23, 24, 25 }
        };
        vector<Individual> individuals;
        for(size_t i = 0; i < 5; i++) {
          individuals.push_back(Individual(ParentPair(-1, -1), shared_ptr<int []>(new int[5])));
          copy(gene_tabs[i], gene_tabs[i] + 5, individuals.back().genes.get());
        }
        vector<int> indices;
        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(4);
        vector<Individual> new_individuals;
        duplicate_individuals(indices, individuals, new_individuals);
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), new_individuals.size());
        CPPUNIT_ASSERT_EQUAL(2, new_individuals[0].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(-1, new_individuals[0].parent_pair.second_parent);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[2][0], new_individuals[0].genes[0]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[2][1], new_individuals[0].genes[1]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[2][2], new_individuals[0].genes[2]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[2][3], new_individuals[0].genes[3]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[2][4], new_individuals[0].genes[4]);
        CPPUNIT_ASSERT_EQUAL(3, new_individuals[1].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(-1, new_individuals[1].parent_pair.second_parent);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[3][0], new_individuals[1].genes[0]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[3][1], new_individuals[1].genes[1]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[3][2], new_individuals[1].genes[2]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[3][3], new_individuals[1].genes[3]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[3][4], new_individuals[1].genes[4]);
        CPPUNIT_ASSERT_EQUAL(4, new_individuals[2].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(-1, new_individuals[2].parent_pair.second_parent);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[4][0], new_individuals[2].genes[0]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[4][1], new_individuals[2].genes[1]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[4][2], new_individuals[2].genes[2]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[4][3], new_individuals[2].genes[3]);
        CPPUNIT_ASSERT_EQUAL(gene_tabs[4][4], new_individuals[2].genes[4]);
      }
    }
  }
}
