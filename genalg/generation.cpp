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
#include "gen_alg.hpp"
#include "gen_alg_vars.hpp"
#include "generator.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    void generate_individual(Individual &new_individual)
    {
      new_individual.parent_pair.first_parent = -1;
      new_individual.parent_pair.second_parent = -1;
      new_individual.genes = shared_ptr<int []>(new int[max_gene_count]);
      for(size_t i = 0; i < max_gene_count; i++) {
        uniform_int_distribution<int> dist(gene_ranges[i].min, gene_ranges[i].max);
        new_individual.genes[i] = dist(generator);
      }
    }

    void generate_individuals(int count, vector<Individual> &new_individuals)
    {
      new_individuals.clear();
      for(int i = 0; i < count; i++) {
        Individual new_individual;
        generate_individual(new_individual);
        new_individuals.push_back(new_individual);
      }
    }
  }
}
