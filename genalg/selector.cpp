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
    Selector::Selector(FitnessFunction *fitness_fun) :
      _M_fitness_function(fitness_fun) {}

    Selector::~Selector() {}

    function<void (int, int, int, int, Result)> Selector::tournament_output_function() const
    { return _M_fitness_function->tournament_output_function(); }

    void Selector::set_tournament_output_function(function<void (int, int, int, int, Result)> fun)
    { _M_fitness_function->set_tournament_output_function(fun); }

    function<bool (const TournamentResult &)> Selector::fitness_output_function() const
    { return _M_fitness_function->fitness_output_function(); }

    void Selector::set_fitness_output_function(function<bool (const TournamentResult &)> fun)
    { _M_fitness_function->set_fitness_output_function(fun); }

    int Selector::select_best_individual() const
    { return select_best_individual_for_excluded_indices(set<int>()); }

    int Selector::select_individual() const
    { return select_individual_for_excluded_indices(set<int>()); }

    bool Selector::select_best_individuals(int individual_count, vector<int> &indices) const
    {
      indices.clear();
      set<int> excluded_indices;
      for(int i = 0; i < individual_count; i++) {
        int j = select_best_individual_for_excluded_indices(excluded_indices);
        if(j == -1) return false;
        indices.push_back(j);
        excluded_indices.insert(j);
      }
      return true;
    }

    bool Selector::select_parents(int child_count, vector<ParentPair> &pairs) const
    {
      pairs.clear();
      for(int i = 0; i < (child_count + 1) / 2; i++) {
        int j = select_individual();
        if(j == -1) return false;
        set<int> excluded_indices;
        excluded_indices.insert(j);
        int k = select_individual_for_excluded_indices(excluded_indices);
        if(k == -1) return false;
        pairs.push_back(ParentPair(j, k));
      }
      return true;
    }
  }
}
