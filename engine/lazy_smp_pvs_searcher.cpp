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
  LazySMPPVSSearcher::LazySMPPVSSearcher(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, unsigned thread_count, int max_depth, int max_quiescence_depth) :
    LazySMPSearcherBase(
      eval_fun,
      transpos_table,
      [](const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, const Searcher *main_searcher, const vector<LazySMPThread> &threads, int max_depth, int max_quiescence_depth) {
        return new LazySMPSinglePVSSearcher(eval_fun, transpos_table, main_searcher, threads, max_depth, max_quiescence_depth);
      },
      thread_count,
      max_depth,
      max_quiescence_depth) {}

  LazySMPPVSSearcher::~LazySMPPVSSearcher() {}
}

