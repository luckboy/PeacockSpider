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
#include "search.hpp"

using namespace std;

namespace peacockspider
{
  ABDADASingleSearcherBase::ABDADASingleSearcherBase(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, const vector<ABDADAThread> &threads, int max_depth, int max_quiescence_depth) :
    SingleSearcherBase(eval_fun, max_depth, max_quiescence_depth), _M_transposition_table(transpos_table), _M_threads(threads) {}
  
  ABDADASingleSearcherBase::~ABDADASingleSearcherBase() {}

  uint64_t ABDADASingleSearcherBase::all_nodes() const
  {
    uint64_t nodes = 0;
    for(const ABDADAThread &thread : _M_threads) {
      nodes += thread.searcher->nodes();
    }
    return nodes;
  }

  void ABDADASingleSearcherBase::decrease_thread_count(int ply)
  { _M_transposition_table->decrease_thread_count(_M_stack[ply].board.hash_key()); }
}
