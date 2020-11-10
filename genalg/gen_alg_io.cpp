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
#include "eval.hpp"
#include "gen_alg.hpp"
#include "gen_alg_vars.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    namespace
    {
      istream &unsafely_read_individual(istream &is, Individual &individual)
      {
        individual.genes = shared_ptr<int []>(new int[max_gene_count]);
        return read_evaluation_parameters(is, &(individual.parent_pair), individual.genes.get(), max_gene_count);
      }
    } 

    istream &read_individual(istream &is, Individual &individual)
    {
      Individual tmp_individual;
      unsafely_read_individual(is, tmp_individual);
      if(is.fail()) return is;
      individual = tmp_individual;
      return is;
    }

    istream &read_individuals(istream &is, int count, vector<Individual> &individuals)
    {
      vector<Individual> tmp_individuals;
      for(int i = 0; i < count; i++) {
        Individual tmp_individual;
        unsafely_read_individual(is, tmp_individual);
        if(is.fail()) return is;
        tmp_individuals.push_back(tmp_individual);
      }
      individuals = tmp_individuals;
      return is;
    }
    
    ostream &write_individual(ostream &os, const Individual &individual)
    { return write_evaluation_parameters(os, individual.parent_pair, individual.genes.get(), max_gene_count); }

    ostream &write_individuals(ostream &os, const vector<Individual> &individuals)
    {
      for(const Individual &individual : individuals) {
        write_individual(os, individual);
      }
      return os;
    }

    istream &skip_individuals(istream &is, streamoff count)
    { return skip_evaluation_parameters(is, count, max_gene_count); }
  }
}
