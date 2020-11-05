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

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    bool genetic_algorithm_iterate(Selector *selector, int iter, const vector<Individual> &individuals, vector<Individual> &new_individuals, int best_individual_count, int child_count, int mutation_count)
    {
      if(!selector->update(iter, individuals)) return false;
      vector<int> indices;
      vector<ParentPair> parent_pairs;
      selector->select_best_individuals(best_individual_count, indices);
      selector->select_parents(child_count, parent_pairs);
      vector<Individual> best_individuals;
      vector<Individual> children;
      vector<Individual> generated_individuals;
      duplicate_individuals(indices, individuals, best_individuals);
      cross_parents(child_count, parent_pairs, individuals, children);
      mutate_individuals(mutation_count, children);
      generate_individuals(selector->individual_count() - best_individual_count - child_count, generated_individuals);
      new_individuals.clear();
      new_individuals.insert(new_individuals.end(), best_individuals.begin(), best_individuals.end());
      new_individuals.insert(new_individuals.end(), children.begin(), children.end());
      new_individuals.insert(new_individuals.end(), generated_individuals.begin(), generated_individuals.end());
      return true;
    }
  }
}
