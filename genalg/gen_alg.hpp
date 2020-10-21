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
#ifndef _GEN_ALG_HPP
#define _GEN_ALG_HPP

#include <set>
#include "eval.hpp"
#include "fitness.hpp"

namespace peacockspider
{
  namespace genalg
  {
    struct Range
    {
      int min, max;
      
      Range() {}

      Range(int min, int max) :
        min(min), max(max) {}
    };
    
    struct Individual
    {
      ParentPair parent_pair;
      std::shared_ptr<int []> genes;
      
      Individual() :
        parent_pair(-1, -1) {}
      
      Individual(const ParentPair &parent_pair, const std::shared_ptr<int []> &genes) :
        parent_pair(parent_pair), genes(genes) {}
    };

    class Selector
    {
    protected:
      FitnessFunction *_M_fitness_function;

      Selector(FitnessFunction *fitness_fun);
    public:
      virtual ~Selector();

      std::function<void (int, int, int, int, Result)> tournament_output_function() const;

      void set_tournament_output_function(std::function<void (int, int, int, int, Result)> fun);

      std::function<void (const TournamentResult &)> fitness_output_function() const;

      void set_fitness_output_function(std::function<void (const TournamentResult &)> fun);

      virtual bool update(int iter, const std::vector<Individual> &individuals) = 0;

      int select_best_individual() const;

      virtual int select_best_individual_for_excluded_indices(const std::set<int> &excluded_indices) const = 0;

      int select_individual() const;

      virtual int select_individual_for_excluded_indices(const std::set<int> &excluded_indices) const = 0;

      bool select_best_individuals(int individual_count, std::vector<int> &indices) const;

      bool select_parents(int child_count, std::vector<ParentPair> &pairs) const;
    };

    class RouletteWheelSelector : public Selector
    {
      struct IndividualPair
      {
        Range range;
        int index;

        IndividualPair() {}
        
        IndividualPair(const Range &range, int index) :
          range(range), index(index) {}
      };
      
      std::vector<int> _M_sorted_individual_indices;
      std::vector<IndividualPair> _M_individual_pairs;
      int _M_individual_range_sum;
    public:
      RouletteWheelSelector(FitnessFunction *fitness_fun);

      virtual ~RouletteWheelSelector();

      virtual bool update(int iter, const std::vector<Individual> &individuals);

      virtual int select_best_individual_for_excluded_indices(const std::set<int> &excluded_indices) const;

      virtual int select_individual_for_excluded_indices(const std::set<int> &excluded_indices) const;
    private:
      int create_individual_pairs(const std::set<int> &excluded_indices, std::vector<IndividualPair> &pairs) const;
    };

    void cross_parent_pair(const ParentPair &parent_pair, const std::vector<Individual> &individuals, Individual *child1, Individual *child2);

    void cross_parents(int child_count, const std::vector<ParentPair> &parent_pairs, const std::vector<Individual> &individuals, std::vector<Individual> &children);
  }
}

#endif
