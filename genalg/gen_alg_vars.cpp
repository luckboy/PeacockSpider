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
#include "default_gene_ranges.hpp"
#include "eval.hpp"
#include "gen_alg_vars.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    size_t max_gene_count;
    Range *gene_ranges;

    void initialize_genetic_algorithm_variables()
    {
      max_gene_count = MAX_EVALUATION_PARAMETER_COUNT;
      gene_ranges = default_gene_ranges;
    }
  }
}
