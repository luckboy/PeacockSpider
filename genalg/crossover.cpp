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
    void cross_parent_pair(const ParentPair &parent_pair, const vector<Individual> &individuals, Individual *child1, Individual *child2)
    {
      const Individual &first_parent = individuals[parent_pair.first_parent];
      const Individual &second_parent = individuals[parent_pair.second_parent];
      uniform_int_distribution<int> dist(0, 1);
      bool are_genes1 = false;
      bool are_genes2 = false;
      if(child1 != nullptr) {
        child1->parent_pair = parent_pair;
        child1->genes = shared_ptr<int []>(new int[max_gene_count]);
      }
      if(child2 != nullptr) {
        child2->parent_pair = parent_pair;
        child2->genes = shared_ptr<int []>(new int[max_gene_count]);
      }
      for(size_t i = 0; i < max_gene_count; i++) {
        bool is_first_parent_gene;
        if(i + 1 >= max_gene_count && ((are_genes1 && !are_genes2) || (!are_genes1 && are_genes2)))
          is_first_parent_gene = !are_genes1;
        else
          is_first_parent_gene = (dist(generator) == 0);
        if(is_first_parent_gene) {
          if(child1 != nullptr) child1->genes[i] = first_parent.genes[i];
          if(child2 != nullptr) child2->genes[i] = second_parent.genes[i];
          are_genes1 = true;
        } else {
          if(child1 != nullptr) child1->genes[i] = second_parent.genes[i];
          if(child2 != nullptr) child2->genes[i] = first_parent.genes[i];
          are_genes2 = true;
        }
      }
    }

    void cross_parents(int child_count, const vector<ParentPair> &parent_pairs, const vector<Individual> &individuals, vector<Individual> &children)
    {
      children.clear();
      for(int i = 0; i < (child_count + 1) / 2; i++) {
        if(i + 1 >= (child_count + 1) / 2 && (child_count % 2) != 0) {
          children.push_back(Individual());
          cross_parent_pair(parent_pairs[i], individuals, &(children[children.size() - 1]), nullptr);
        } else {
          children.push_back(Individual());
          children.push_back(Individual());
          cross_parent_pair(parent_pairs[i], individuals, &(children[children.size() - 2]), &(children[children.size() - 1]));
        }
      }
    }
  }
}
