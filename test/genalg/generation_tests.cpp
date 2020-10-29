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
#include "generation_tests.hpp"
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
      CPPUNIT_TEST_SUITE_REGISTRATION(GenerationTests);

      namespace
      {
        size_t saved_max_gene_count;
        Range *saved_gene_ranges;
      }
      
      void GenerationTests::setUp()
      {
        saved_max_gene_count = max_gene_count;
        saved_gene_ranges = gene_ranges;
        max_gene_count = 5;
        gene_ranges = test_gene_ranges;
      }

      void GenerationTests::tearDown()
      {
        max_gene_count = saved_max_gene_count;
        gene_ranges = saved_gene_ranges;
      }

      void GenerationTests::test_generate_individual_function_generates_individual()
      {
        Individual individual;
        generate_individual(individual);
        CPPUNIT_ASSERT_EQUAL(-1, individual.parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(-1, individual.parent_pair.second_parent);
        CPPUNIT_ASSERT(individual.genes[0] >= test_gene_ranges[0].min && individual.genes[0] <= test_gene_ranges[0].max);
        CPPUNIT_ASSERT(individual.genes[1] >= test_gene_ranges[1].min && individual.genes[1] <= test_gene_ranges[1].max);
        CPPUNIT_ASSERT(individual.genes[2] >= test_gene_ranges[2].min && individual.genes[2] <= test_gene_ranges[2].max);
        CPPUNIT_ASSERT(individual.genes[3] >= test_gene_ranges[3].min && individual.genes[3] <= test_gene_ranges[3].max);
        CPPUNIT_ASSERT(individual.genes[4] >= test_gene_ranges[4].min && individual.genes[4] <= test_gene_ranges[4].max);
      }

      void GenerationTests::test_generate_individuals_function_generates_individuals()
      {
        vector<Individual> individuals;
        generate_individuals(3, individuals);
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), individuals.size());
        CPPUNIT_ASSERT_EQUAL(-1, individuals[0].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(-1, individuals[0].parent_pair.second_parent);
        CPPUNIT_ASSERT(individuals[0].genes[0] >= test_gene_ranges[0].min && individuals[0].genes[0] <= test_gene_ranges[0].max);
        CPPUNIT_ASSERT(individuals[0].genes[1] >= test_gene_ranges[1].min && individuals[0].genes[1] <= test_gene_ranges[1].max);
        CPPUNIT_ASSERT(individuals[0].genes[2] >= test_gene_ranges[2].min && individuals[0].genes[2] <= test_gene_ranges[2].max);
        CPPUNIT_ASSERT(individuals[0].genes[3] >= test_gene_ranges[3].min && individuals[0].genes[3] <= test_gene_ranges[3].max);
        CPPUNIT_ASSERT(individuals[0].genes[4] >= test_gene_ranges[4].min && individuals[0].genes[4] <= test_gene_ranges[4].max);
        CPPUNIT_ASSERT_EQUAL(-1, individuals[1].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(-1, individuals[1].parent_pair.second_parent);
        CPPUNIT_ASSERT(individuals[1].genes[0] >= test_gene_ranges[0].min && individuals[1].genes[0] <= test_gene_ranges[0].max);
        CPPUNIT_ASSERT(individuals[1].genes[1] >= test_gene_ranges[1].min && individuals[1].genes[1] <= test_gene_ranges[1].max);
        CPPUNIT_ASSERT(individuals[1].genes[2] >= test_gene_ranges[2].min && individuals[1].genes[2] <= test_gene_ranges[2].max);
        CPPUNIT_ASSERT(individuals[1].genes[3] >= test_gene_ranges[3].min && individuals[1].genes[3] <= test_gene_ranges[3].max);
        CPPUNIT_ASSERT(individuals[1].genes[4] >= test_gene_ranges[4].min && individuals[1].genes[4] <= test_gene_ranges[4].max);
        CPPUNIT_ASSERT_EQUAL(-1, individuals[2].parent_pair.first_parent);
        CPPUNIT_ASSERT_EQUAL(-1, individuals[2].parent_pair.second_parent);
        CPPUNIT_ASSERT(individuals[2].genes[0] >= test_gene_ranges[0].min && individuals[2].genes[0] <= test_gene_ranges[0].max);
        CPPUNIT_ASSERT(individuals[2].genes[1] >= test_gene_ranges[1].min && individuals[2].genes[1] <= test_gene_ranges[1].max);
        CPPUNIT_ASSERT(individuals[2].genes[2] >= test_gene_ranges[2].min && individuals[2].genes[2] <= test_gene_ranges[2].max);
        CPPUNIT_ASSERT(individuals[2].genes[3] >= test_gene_ranges[3].min && individuals[2].genes[3] <= test_gene_ranges[3].max);
        CPPUNIT_ASSERT(individuals[2].genes[4] >= test_gene_ranges[4].min && individuals[2].genes[4] <= test_gene_ranges[4].max);
      }
    }
  }
}
