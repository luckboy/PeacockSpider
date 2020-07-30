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
#ifndef _TRANSPOS_TABLE_HPP
#define _TRANSPOS_TABLE_HPP

#include <memory>
#include "chess.hpp"

namespace peacockspider
{
  enum class ValueType
  {
    NONE = 0,
    EXACT = 1,
    UPPER_BOUND = 2,
    LOWER_BOUND = 3
  };
  
  class TranspositionTableEntry
  {
    HashKey _M_hash_key;
    std::uint8_t _M_pad1;
    std::uint8_t _M_depth;
    std::int16_t _M_value;
    Move _M_best_move;
    std::int8_t _M_value_type;
    std::uint8_t _M_pad2;
    std::int16_t _M_age;
    std::uint32_t _M_pad3;
  public:
    TranspositionTableEntry() :
      _M_hash_key(0), _M_value_type(0), _M_age(0) {}

    HashKey hash_key() const
    { return _M_hash_key; }

    void set_hash_key(HashKey hash_key)
    { _M_hash_key = hash_key; }

    int depth() const
    { return static_cast<int>(_M_depth); }
    
    void set_depth(int depth)
    { _M_depth = static_cast<std::uint8_t>(depth); }

    int value() const
    { return _M_value; }
    
    void set_value(int value)
    { _M_value = value; }
    
    Move best_move() const
    { return _M_best_move; }
    
    void set_best_move(Move move)
    { _M_best_move = move; }
    
    ValueType value_type() const
    { return static_cast<ValueType>(_M_value); }

    void set_value_type(ValueType value_type)
    { _M_value_type = static_cast<std::int8_t>(value_type); }

    unsigned age() const
    { return _M_age; }
    
    void set_age(unsigned age)
    { _M_age = age; }
  };

  class TranspositionTable
  {
    std::unique_ptr<TranspositionTableEntry []> _M_entries;
    std::size_t _M_entry_count;
    std::uint16_t _M_age;
  public:
    TranspositionTable(std::size_t count);

    ~TranspositionTable();

    void clear();

    void increase_age_or_clear();

    bool retrieve(HashKey hash_key, int &alpha, int &beta, int depth, int &best_value, Move &best_move);

    bool store(HashKey hash_key, int alpha, int beta, int depth, int best_value, Move best_move);
  };
}

#endif
