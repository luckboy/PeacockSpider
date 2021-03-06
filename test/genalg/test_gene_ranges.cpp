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
#include "test_gene_ranges.hpp"

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      Range test_gene_ranges[5] = {
        Range(1, 1000),
        Range(2, 2000),
        Range(3, 3000),
        Range(4, 4000),
        Range(5, 5000)
      };
    }
  }
}
