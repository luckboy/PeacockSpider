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
#include "fitness.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    FitnessFunction::FitnessFunction(Tournament *tournament) :
      _M_tournament(tournament), _M_fitness_output_function([](int iter, const TournamentResult &result) {
        return true;
      }) {}

    FitnessFunction::~FitnessFunction() {}

    function<void (int, int, int, int, Result)> FitnessFunction::tournament_output_function() const
    { return _M_tournament->tournament_output_function(); }

    void FitnessFunction::set_tournament_output_function(std::function<void (int, int, int, int, Result)> fun)
    { _M_tournament->set_tournament_output_function(fun); }

    function<bool (int, const TournamentResult &)> FitnessFunction::fitness_output_function() const
    { return _M_fitness_output_function; }

    void FitnessFunction::set_fitness_output_function(function<bool (int, const TournamentResult &)> fun)
    { _M_fitness_output_function = fun; }

    bool FitnessFunction::update(int iter, const vector<shared_ptr<int []>> &gene_arrays)
    {
      if(!_M_tournament->play(iter, gene_arrays)) return false;
      if(!_M_fitness_output_function(iter, _M_tournament->result())) return false;
      return true;
    }

    int FitnessFunction::operator()(int i) const
    { return _M_tournament->result().score(i); }
  }
}
