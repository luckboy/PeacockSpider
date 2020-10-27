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
#ifndef _FITNESS_HPP
#define _FITNESS_HPP

#include "tournament.hpp"

namespace peacockspider
{
  namespace genalg
  {
    class FitnessFunction
    {
      Tournament *_M_tournament;
      std::function<bool (const TournamentResult &)> _M_fitness_output_function;
    public:
      FitnessFunction(Tournament *tournament);

      ~FitnessFunction();

      std::function<void (int, int, int, int, Result)> tournament_output_function() const;

      void set_tournament_output_function(std::function<void (int, int, int, int, Result)> fun);

      std::function<bool (const TournamentResult &)> fitness_output_function() const;

      void set_fitness_output_function(std::function<bool (const TournamentResult &)> fun);

      int individual_count() const
      { return _M_tournament->result().player_count(); }

      bool update(int iter, const std::vector<std::shared_ptr<int []>> &gene_arrays);

      int operator()(int i) const;
    };
  }
}

#endif
