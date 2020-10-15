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
#include <iterator>
#include "gen_alg.hpp"
#include "generator.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    RouletteWheelSelector::RouletteWheelSelector(FitnessFunction *fitness_fun) :
      Selector(fitness_fun) {}

    RouletteWheelSelector::~RouletteWheelSelector() {}

    bool RouletteWheelSelector::update(int iter, const vector<Individual> &individuals)
    {
      vector<shared_ptr<int []>> gene_arrays;
      transform(individuals.begin(), individuals.end(), back_inserter(gene_arrays), [](const Individual &individual) {
        return individual.genes;
      });
      if(!_M_fitness_function->update(iter, gene_arrays)) return false;
      _M_sorted_individual_indices.clear();
      for(int i = 0; i < _M_fitness_function->individual_count(); i++) {
        _M_sorted_individual_indices.push_back(i);
      }
      sort(_M_sorted_individual_indices.begin(), _M_sorted_individual_indices.end(), [this](int i, int j) {
        return (*_M_fitness_function)(i) > (*_M_fitness_function)(j);
      });
      _M_individual_range_sum = create_individual_pairs(set<int>(), _M_individual_pairs);
      return true;
    }

    int RouletteWheelSelector::select_best_individual_for_excluded_indices(const set<int> &excluded_indices) const
    {
      for(int i : _M_sorted_individual_indices) {
        if(excluded_indices.find(i) == excluded_indices.end()) return i;
      }
      return -1;
    }

    int RouletteWheelSelector::select_individual_for_excluded_indices(const set<int> &excluded_indices) const
    {
      vector<IndividualPair> tmp_pairs;
      const vector<IndividualPair> *pairs;
      int sum;
      if(excluded_indices.empty()) {
        pairs = &_M_individual_pairs;
        sum = _M_individual_range_sum;
      } else {
        pairs = &tmp_pairs;
        sum = create_individual_pairs(excluded_indices, tmp_pairs);
      }
      if(sum == -1) return -1;
      int i = -1;
      if(sum > 0) {
        uniform_int_distribution<int> dist(0, sum);
        i = dist(generator);
      } else
        i = 0;
      IndividualPair pair(Range(i, i), -1);
      auto iter = lower_bound(pairs->begin(), pairs->end(), pair, [](const IndividualPair &pair1, const IndividualPair pair2) {
        return pair1.range.max < pair2.range.min;
      });
      return (iter != pairs->end() && !(pair.range.max < iter->range.min)) ? iter->index : -1;
    }

    int RouletteWheelSelector::create_individual_pairs(const set<int> &excluded_indices, vector<IndividualPair> &pairs) const
    {
      int sum = -1;
      pairs.clear();
      for(int i : _M_sorted_individual_indices) {
        if(excluded_indices.find(i) == excluded_indices.end()) {
          int max = sum + (*_M_fitness_function)(i) + 1;
          pairs.push_back(IndividualPair(Range(sum + 1, max), i));
          sum = max;
        }
      }
      return sum;
    }
  }
}
