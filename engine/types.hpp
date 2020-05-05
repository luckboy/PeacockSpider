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
#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <cstdint>

namespace peacockspider
{
  typedef std::uint64_t Bitboard;
  typedef int Square;
  typedef int Column;
  typedef int Row;
  typedef std::int8_t Square8;
  typedef std::int8_t Column8;
  typedef std::int8_t Row8;
}

#endif
