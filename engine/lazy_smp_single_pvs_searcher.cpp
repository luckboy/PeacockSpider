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
  LazySMPSinglePVSSearcher::LazySMPSinglePVSSearcher(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, const Searcher *main_searcher, const vector<LazySMPThread> &threads, int max_depth, int max_quiescence_depth) :
    SinglePVSSearcherWithTT(eval_fun, transpos_table, max_depth, max_quiescence_depth), _M_main_searcher(main_searcher), _M_threads(threads) {}

  LazySMPSinglePVSSearcher::~LazySMPSinglePVSSearcher() {}

  void LazySMPSinglePVSSearcher::clear()
  { _M_move_order.clear(); }

  void LazySMPSinglePVSSearcher::clear_for_new_game()
  { _M_move_order.clear(); }

  uint64_t LazySMPSinglePVSSearcher::all_nodes() const
  {
    const Searcher *main_searcher = (_M_main_searcher != nullptr ? _M_main_searcher : this);
    uint64_t nodes = main_searcher->nodes();
    for(const LazySMPThread &thread : _M_threads) {
      nodes += thread.searcher->nodes();
    }
    return nodes;
  }
}

