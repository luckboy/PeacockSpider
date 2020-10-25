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
#include "gen_alg.hpp"
#include "gen_alg_vars.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    void copy_individual(int i, const vector<Individual> &individuals, Individual &new_individual)
    {
      const Individual &individual = individuals[i];
      new_individual.parent_pair.first_parent = i;
      new_individual.parent_pair.second_parent = -1;
      new_individual.genes = shared_ptr<int []>(new int[max_gene_count]);
      copy(individual.genes.get(), individual.genes.get() + max_gene_count, new_individual.genes.get());
    }

    void copy_individuals(const vector<int> &indices, const vector<Individual> &individuals, vector<Individual> &new_individuals)
    {
      new_individuals.clear();
      for(int i : indices) {
        Individual new_individual;
        copy_individual(i, individuals, new_individual);
        new_individuals.push_back(new_individual);
      }
    }
  }
}
