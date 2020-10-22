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
    void mutate_individuals(int count, vector<Individual> &individuals)
    {
      uniform_int_distribution<size_t> individual_dist(0, individuals.size() * max_gene_count - 1);
      for(int i = 0; i < count; i++) {
        size_t n = individual_dist(generator);
        int j = static_cast<int>(n / max_gene_count);
        size_t k = n % max_gene_count;
        uniform_int_distribution<int> gene_dist(gene_ranges[k].min, gene_ranges[k].max);
        individuals[j].genes[k] = gene_dist(generator);
      }
    }
  }
}
