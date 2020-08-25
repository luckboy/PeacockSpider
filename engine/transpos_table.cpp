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
#include <mutex>
#include "transpos_table.hpp"

using namespace std;

namespace peacockspider
{
  TranspositionTable::TranspositionTable(size_t count) :
    _M_entries(new TranspositionTableEntry[count]), _M_entry_count(count), _M_age(0) {}

  TranspositionTable::~TranspositionTable() {}

  void TranspositionTable::clear()
  {
    for(size_t i = 0; i < _M_entry_count; i++) {
      _M_entries[i].set_hash_key(0);
      _M_entries[i].set_value_type(ValueType::NONE);
      _M_entries[i].set_age(0);
    }
    _M_age = 0;
  }
 
  void TranspositionTable::increase_age_or_clear()
  {
    _M_age++;
    if(_M_age == 0) {
      clear();
      _M_age++;
    }
  }

  bool TranspositionTable::retrieve(HashKey hash_key, int &alpha, int &beta, int depth, int &best_value, Move &best_move)
  {
    size_t i = hash_key % _M_entry_count;
    lock_guard<Spinlock> guard(_M_entries[i].spinlock());
    best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
    if(_M_entries[i].age() == _M_age && _M_entries[i].value_type() != ValueType::NONE && _M_entries[i].hash_key() == hash_key) {
      best_move = _M_entries[i].best_move();
      if(_M_entries[i].depth() >= depth) {
        switch(_M_entries[i].value_type()) {
          case ValueType::EXACT:
            best_value = _M_entries[i].value();
            return true;
          case ValueType::UPPER_BOUND:
            if(_M_entries[i].value() <= alpha) {
              best_value = _M_entries[i].value();
              return true;
            }
            if(_M_entries[i].value() < beta) beta = _M_entries[i].value();
            break;
          case ValueType::LOWER_BOUND:
            if(_M_entries[i].value() >= beta) {
              best_value = _M_entries[i].value();
              return true;
            }
            if(_M_entries[i].value() > alpha) alpha = _M_entries[i].value();
            break;
          default:
            break;
        }
      }
    }
    return false;
  }

  bool TranspositionTable::store(HashKey hash_key, int alpha, int beta, int depth, int best_value, Move best_move)
  {
    size_t i = hash_key % _M_entry_count;
    lock_guard<Spinlock> guard(_M_entries[i].spinlock());
    _M_entries[i].set_hash_key(hash_key);
    _M_entries[i].set_depth(depth);
    _M_entries[i].set_value(best_value);
    _M_entries[i].set_best_move(best_move);
    if(best_value > alpha && best_value < beta)
      _M_entries[i].set_value_type(ValueType::EXACT);
    else if(best_value <= alpha)
      _M_entries[i].set_value_type(ValueType::UPPER_BOUND);
    else if(best_value >= beta)
      _M_entries[i].set_value_type(ValueType::LOWER_BOUND);
    else
      _M_entries[i].set_value_type(ValueType::NONE);
    _M_entries[i].set_age(_M_age);
    return true;
  }
}
