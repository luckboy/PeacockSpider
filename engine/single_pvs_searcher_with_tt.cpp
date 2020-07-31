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
  SinglePVSSearcherWithTT::SinglePVSSearcherWithTT(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, int max_depth, int max_quiescence_depth) :
    SinglePVSSearcher(eval_fun, max_depth, max_quiescence_depth), _M_transposition_table(transpos_table) {}

  SinglePVSSearcherWithTT::~SinglePVSSearcherWithTT() {}
  
  void SinglePVSSearcherWithTT::clear()
  {
    _M_move_order.clear();
    _M_transposition_table->increase_age_or_clear();
  }

  void SinglePVSSearcherWithTT::clear_for_new_game()
  {
    _M_move_order.clear();
    _M_transposition_table->clear();
  }
  
  bool SinglePVSSearcherWithTT::before(int &alpha, int &beta, int depth, int ply, int &best_value, Move &best_move)
  { return _M_transposition_table->retrieve(_M_stack[ply].board.hash_key(), alpha, beta, depth, best_value, best_move); }

  void SinglePVSSearcherWithTT::after(int alpha, int beta, int depth, int ply, int best_value, Move best_move)
  { _M_transposition_table->store(_M_stack[ply].board.hash_key(), alpha, beta, depth, best_value, best_move); }

  void SinglePVSSearcherWithTT::cutoff(int alpha, int beta, int depth, int ply, int best_value, Move best_move)
  { _M_transposition_table->store(_M_stack[ply].board.hash_key(), alpha, beta, depth, best_value, best_move); }
}
