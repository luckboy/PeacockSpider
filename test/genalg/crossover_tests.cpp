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
#include "crossover_tests.hpp"
#include "gen_alg.hpp"
#include "gen_alg_vars.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      CPPUNIT_TEST_SUITE_REGISTRATION(CrossoverTests);

      namespace
      {
        size_t saved_max_gene_count;
      }
      
      void CrossoverTests::setUp()
      {
        saved_max_gene_count = max_gene_count;
        max_gene_count = 5;
      }

      void CrossoverTests::tearDown()
      { max_gene_count = saved_max_gene_count; }

      void CrossoverTests::test_cross_parant_pair_function_crosses_parent_pair_for_two_children()
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
        Individual child1;
        Individual child2;
        cross_parent_pair(ParentPair(2, 3), individuals, &child1, &child2);
        CPPUNIT_ASSERT_EQUAL(2, child1.parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(3, child1.parent_pair.second_parent);
        CPPUNIT_ASSERT_EQUAL(2, child2.parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(3, child2.parent_pair.second_parent);
        bool are_first_parent_genes = false;
        bool are_second_parent_genes = false;
        CPPUNIT_ASSERT((gene_tabs[2][0] == child1.genes[0] && gene_tabs[3][0] == child2.genes[0]) || (gene_tabs[3][0] == child1.genes[0] && gene_tabs[2][0] == child2.genes[0]));
        if(gene_tabs[2][0] == child1.genes[0] && gene_tabs[3][0] == child2.genes[0])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[2][1] == child1.genes[1] && gene_tabs[3][1] == child2.genes[1]) || (gene_tabs[3][1] == child1.genes[1] && gene_tabs[2][1] == child2.genes[1]));
        if(gene_tabs[2][1] == child1.genes[1] && gene_tabs[3][1] == child2.genes[1])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[2][2] == child1.genes[2] && gene_tabs[3][2] == child2.genes[2]) || (gene_tabs[3][2] == child1.genes[2] && gene_tabs[2][2] == child2.genes[2]));
        if(gene_tabs[2][2] == child1.genes[2] && gene_tabs[3][2] == child2.genes[2])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[2][3] == child1.genes[3] && gene_tabs[3][3] == child2.genes[3]) || (gene_tabs[3][3] == child1.genes[3] && gene_tabs[2][3] == child2.genes[3]));
        if(gene_tabs[2][3] == child1.genes[3] && gene_tabs[3][3] == child2.genes[3])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[2][4] == child1.genes[4] && gene_tabs[3][4] == child2.genes[4]) || (gene_tabs[3][4] == child1.genes[4] && gene_tabs[2][4] == child2.genes[4]));
        if(gene_tabs[2][4] == child1.genes[4] && gene_tabs[3][4] == child2.genes[4])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(are_first_parent_genes && are_second_parent_genes);
      }
      
      void CrossoverTests::test_cross_parant_pair_function_crosses_parent_pair_for_first_child()
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
        Individual child;
        cross_parent_pair(ParentPair(1, 4), individuals, &child, nullptr);
        CPPUNIT_ASSERT_EQUAL(1, child.parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(4, child.parent_pair.second_parent);
        bool are_first_parent_genes = false;
        bool are_second_parent_genes = false;
        CPPUNIT_ASSERT(gene_tabs[1][0] == child.genes[0] || gene_tabs[4][0] == child.genes[0]);
        if(gene_tabs[1][0] == child.genes[0])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(gene_tabs[1][1] == child.genes[1] || gene_tabs[4][1] == child.genes[1]);
        if(gene_tabs[1][1] == child.genes[1])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(gene_tabs[1][2] == child.genes[2] || gene_tabs[4][2] == child.genes[2]);
        if(gene_tabs[1][2] == child.genes[2])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(gene_tabs[1][3] == child.genes[3] || gene_tabs[4][3] == child.genes[3]);
        if(gene_tabs[1][3] == child.genes[3])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(gene_tabs[1][4] == child.genes[4] || gene_tabs[4][4] == child.genes[4]);
        if(gene_tabs[1][4] == child.genes[4])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(are_first_parent_genes && are_second_parent_genes);
      }
      
      void CrossoverTests::test_cross_parant_pair_function_crosses_parent_pair_for_second_child()
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
        Individual child;
        cross_parent_pair(ParentPair(4, 2), individuals, nullptr, &child);
        CPPUNIT_ASSERT_EQUAL(4, child.parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(2, child.parent_pair.second_parent);
        bool are_first_parent_genes = false;
        bool are_second_parent_genes = false;
        CPPUNIT_ASSERT(gene_tabs[2][0] == child.genes[0] || gene_tabs[4][0] == child.genes[0]);
        if(gene_tabs[2][0] == child.genes[0])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(gene_tabs[2][1] == child.genes[1] || gene_tabs[4][1] == child.genes[1]);
        if(gene_tabs[2][1] == child.genes[1])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(gene_tabs[2][2] == child.genes[2] || gene_tabs[4][2] == child.genes[2]);
        if(gene_tabs[2][2] == child.genes[2])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(gene_tabs[2][3] == child.genes[3] || gene_tabs[4][3] == child.genes[3]);
        if(gene_tabs[2][3] == child.genes[3])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(gene_tabs[2][4] == child.genes[4] || gene_tabs[4][4] == child.genes[4]);
        if(gene_tabs[2][4] == child.genes[4])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(are_first_parent_genes && are_second_parent_genes);
      }
      
      void CrossoverTests::test_cross_parents_function_crosses_parents_for_even_number_of_children()
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
        vector<ParentPair> parent_pairs;
        parent_pairs.push_back(ParentPair(0, 2));
        parent_pairs.push_back(ParentPair(3, 4));
        vector<Individual> children;
        cross_parents(4, parent_pairs, individuals, children);
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), children.size());
        CPPUNIT_ASSERT_EQUAL(0, children[0].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(2, children[0].parent_pair.second_parent);
        CPPUNIT_ASSERT_EQUAL(0, children[1].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(2, children[1].parent_pair.second_parent);
        bool are_first_parent_genes = false;
        bool are_second_parent_genes = false;
        CPPUNIT_ASSERT((gene_tabs[0][0] == children[0].genes[0] && gene_tabs[2][0] == children[1].genes[0]) || (gene_tabs[2][0] == children[0].genes[0] && gene_tabs[0][0] == children[1].genes[0]));
        if(gene_tabs[0][0] == children[0].genes[0] && gene_tabs[2][0] == children[1].genes[0])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[0][1] == children[0].genes[1] && gene_tabs[2][1] == children[1].genes[1]) || (gene_tabs[2][1] == children[0].genes[1] && gene_tabs[0][1] == children[1].genes[1]));
        if(gene_tabs[0][1] == children[0].genes[1] && gene_tabs[2][1] == children[1].genes[1])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[0][2] == children[0].genes[2] && gene_tabs[2][2] == children[1].genes[2]) || (gene_tabs[2][2] == children[0].genes[2] && gene_tabs[0][2] == children[1].genes[2]));
        if(gene_tabs[0][2] == children[0].genes[2] && gene_tabs[2][2] == children[1].genes[2])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[0][3] == children[0].genes[3] && gene_tabs[2][3] == children[1].genes[3]) || (gene_tabs[2][3] == children[0].genes[3] && gene_tabs[0][3] == children[1].genes[3]));
        if(gene_tabs[0][3] == children[0].genes[3] && gene_tabs[2][3] == children[1].genes[3])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[0][4] == children[0].genes[4] && gene_tabs[2][4] == children[1].genes[4]) || (gene_tabs[2][4] == children[0].genes[4] && gene_tabs[0][4] == children[1].genes[4]));
        if(gene_tabs[0][4] == children[0].genes[4] && gene_tabs[2][4] == children[1].genes[4])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(are_first_parent_genes && are_second_parent_genes);
        CPPUNIT_ASSERT_EQUAL(3, children[2].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(4, children[2].parent_pair.second_parent);
        CPPUNIT_ASSERT_EQUAL(3, children[3].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(4, children[3].parent_pair.second_parent);
        are_first_parent_genes = false;
        are_second_parent_genes = false;
        CPPUNIT_ASSERT((gene_tabs[3][0] == children[2].genes[0] && gene_tabs[4][0] == children[3].genes[0]) || (gene_tabs[4][0] == children[2].genes[0] && gene_tabs[3][0] == children[3].genes[0]));
        if(gene_tabs[3][0] == children[2].genes[0] && gene_tabs[4][0] == children[3].genes[0])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[3][1] == children[2].genes[1] && gene_tabs[4][1] == children[3].genes[1]) || (gene_tabs[4][1] == children[2].genes[1] && gene_tabs[3][1] == children[3].genes[1]));
        if(gene_tabs[3][1] == children[2].genes[1] && gene_tabs[4][1] == children[3].genes[1])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[3][2] == children[2].genes[2] && gene_tabs[4][2] == children[3].genes[2]) || (gene_tabs[4][2] == children[2].genes[2] && gene_tabs[3][2] == children[3].genes[2]));
        if(gene_tabs[3][2] == children[2].genes[2] && gene_tabs[4][2] == children[3].genes[2])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[3][3] == children[2].genes[3] && gene_tabs[4][3] == children[3].genes[3]) || (gene_tabs[4][3] == children[2].genes[3] && gene_tabs[3][3] == children[3].genes[3]));
        if(gene_tabs[3][3] == children[2].genes[3] && gene_tabs[4][3] == children[3].genes[3])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[3][4] == children[2].genes[4] && gene_tabs[4][4] == children[3].genes[4]) || (gene_tabs[4][4] == children[2].genes[4] && gene_tabs[3][4] == children[3].genes[4]));
        if(gene_tabs[3][4] == children[2].genes[4] && gene_tabs[4][4] == children[3].genes[4])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(are_first_parent_genes && are_second_parent_genes);
      }
      
      void CrossoverTests::test_cross_parents_function_crosses_parents_for_odd_number_of_children()
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
        vector<ParentPair> parent_pairs;
        parent_pairs.push_back(ParentPair(0, 1));
        parent_pairs.push_back(ParentPair(2, 4));
        vector<Individual> children;
        cross_parents(3, parent_pairs, individuals, children);
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), children.size());
        CPPUNIT_ASSERT_EQUAL(0, children[0].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(1, children[0].parent_pair.second_parent);
        CPPUNIT_ASSERT_EQUAL(0, children[1].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(1, children[1].parent_pair.second_parent);
        bool are_first_parent_genes = false;
        bool are_second_parent_genes = false;
        CPPUNIT_ASSERT((gene_tabs[0][0] == children[0].genes[0] && gene_tabs[1][0] == children[1].genes[0]) || (gene_tabs[1][0] == children[0].genes[0] && gene_tabs[0][0] == children[1].genes[0]));
        if(gene_tabs[0][0] == children[0].genes[0] && gene_tabs[1][0] == children[1].genes[0])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[0][1] == children[0].genes[1] && gene_tabs[1][1] == children[1].genes[1]) || (gene_tabs[1][1] == children[0].genes[1] && gene_tabs[0][1] == children[1].genes[1]));
        if(gene_tabs[0][1] == children[0].genes[1] && gene_tabs[1][1] == children[1].genes[1])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[0][2] == children[0].genes[2] && gene_tabs[1][2] == children[1].genes[2]) || (gene_tabs[1][2] == children[0].genes[2] && gene_tabs[0][2] == children[1].genes[2]));
        if(gene_tabs[0][2] == children[0].genes[2] && gene_tabs[1][2] == children[1].genes[2])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[0][3] == children[0].genes[3] && gene_tabs[1][3] == children[1].genes[3]) || (gene_tabs[1][3] == children[0].genes[3] && gene_tabs[0][3] == children[1].genes[3]));
        if(gene_tabs[0][3] == children[0].genes[3] && gene_tabs[1][3] == children[1].genes[3])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT((gene_tabs[0][4] == children[0].genes[4] && gene_tabs[1][4] == children[1].genes[4]) || (gene_tabs[1][4] == children[0].genes[4] && gene_tabs[0][4] == children[1].genes[4]));
        if(gene_tabs[0][4] == children[0].genes[4] && gene_tabs[1][4] == children[1].genes[4])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(are_first_parent_genes && are_second_parent_genes);
        CPPUNIT_ASSERT_EQUAL(2, children[2].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(4, children[2].parent_pair.second_parent);
        are_first_parent_genes = false;
        are_second_parent_genes = false;
        CPPUNIT_ASSERT(gene_tabs[2][0] == children[2].genes[0] || gene_tabs[4][0] == children[2].genes[0]);
        if(gene_tabs[2][0] == children[2].genes[0])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(gene_tabs[2][1] == children[2].genes[1] || gene_tabs[4][1] == children[2].genes[1]);
        if(gene_tabs[2][1] == children[2].genes[1])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(gene_tabs[2][2] == children[2].genes[2] || gene_tabs[4][2] == children[2].genes[2]);
        if(gene_tabs[2][2] == children[2].genes[2])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(gene_tabs[2][3] == children[2].genes[3] || gene_tabs[4][3] == children[2].genes[3]);
        if(gene_tabs[2][3] == children[2].genes[3])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(gene_tabs[2][4] == children[2].genes[4] || gene_tabs[4][4] == children[2].genes[4]);
        if(gene_tabs[2][4] == children[2].genes[4])
          are_first_parent_genes = true;
        else
          are_second_parent_genes = true;
        CPPUNIT_ASSERT(are_first_parent_genes && are_second_parent_genes);
      }
    }
  }
}
