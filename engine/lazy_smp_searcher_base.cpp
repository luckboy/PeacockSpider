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
  LazySMPSearcherBase::LazySMPSearcherBase(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, function<Searcher *(const EvaluationFunction *, TranspositionTable *, const Searcher *, const vector<LazySMPThread> &, int, int)> fun, unsigned thread_count, int max_depth, int max_quiescence_depth) :
    _M_transposition_table(transpos_table)
  {
    _M_main_searcher = unique_ptr<Searcher>(fun(eval_fun, transpos_table, nullptr, _M_threads, max_depth, max_quiescence_depth));
    for(unsigned i = 0; i < thread_count - 1; i++) {
      _M_threads.push_back(LazySMPThread());
      _M_threads.back().searcher = unique_ptr<Searcher>(fun(eval_fun, transpos_table, _M_main_searcher.get(), _M_threads, max_depth + 1, max_quiescence_depth));
      _M_threads.back().command = LazySMPCommand::NO_COMMAND;
      _M_threads.back().result = LazySMPResult::NO_RESULT;
      _M_threads.back().thread = thread([this, i]() {
        unique_lock<mutex> lock(_M_threads[i].mutex);
        while(true) {
          while(_M_threads[i].command == LazySMPCommand::NO_COMMAND) {
            _M_threads[i].start_condition_variable.wait(lock);
          }
          if(_M_threads[i].command == LazySMPCommand::QUIT) break;
          if(_M_threads[i].command == LazySMPCommand::SEARCH) {
            Move best_move;
            int depth = _M_depth + (i % 2 == 0 ? 1 : 0);
            _M_threads[i].searcher->search_from_root(_M_alpha, _M_beta, depth, _M_search_moves, best_move, *_M_boards, _M_last_board);
          }
          _M_threads[i].command = LazySMPCommand::NO_COMMAND;
          _M_threads[i].result = LazySMPResult::STOP;
          _M_threads[i].stop_condition_variable.notify_one();
        }
      });
    }
  }

  LazySMPSearcherBase::~LazySMPSearcherBase()
  {
    for(LazySMPThread &thread : _M_threads) {
      thread.searcher->stop_searching();
    }
    for(LazySMPThread &thread : _M_threads) {
      unique_lock<mutex> lock(thread.mutex);
      thread.command = LazySMPCommand::QUIT;
      thread.start_condition_variable.notify_one();
    }
    for(LazySMPThread &thread : _M_threads) {
      thread.thread.join();
    }
  }

  const Board &LazySMPSearcherBase::board() const
  { return _M_main_searcher->board(); }

  void LazySMPSearcherBase::set_board(const Board &board)
  {
    _M_main_searcher->set_board(board);
    for(LazySMPThread &thread : _M_threads) {
      thread.searcher->set_board(board);
    }
  }
    
  void LazySMPSearcherBase::set_stop_time(const chrono::high_resolution_clock::time_point &time)
  { _M_main_searcher->set_stop_time(time); }

  void LazySMPSearcherBase::unset_stop_time()
  { _M_main_searcher->unset_stop_nodes(); }

  void LazySMPSearcherBase::set_stop_nodes(uint64_t nodes)
  { _M_main_searcher->set_stop_nodes(nodes); }

  void LazySMPSearcherBase::unset_stop_nodes()
  { _M_main_searcher->unset_stop_nodes(); }

  void LazySMPSearcherBase::set_previous_pv_line(const PVLine &pv_line)
  {
    _M_main_searcher->set_previous_pv_line(pv_line);
    for(LazySMPThread &thread : _M_threads) {
      thread.searcher->set_previous_pv_line(pv_line);
    }
  }

  void LazySMPSearcherBase::clear()
  {
    _M_transposition_table->increase_age_or_clear();
    _M_main_searcher->clear();
    for(LazySMPThread &thread : _M_threads) {
      thread.searcher->clear();
    }
  }

  void LazySMPSearcherBase::clear_for_new_game()
  {
    _M_transposition_table->clear();
    _M_main_searcher->clear();
    for(LazySMPThread &thread : _M_threads) {
      thread.searcher->clear();
    }
  }

  int LazySMPSearcherBase::search_from_root(int alpha, int beta, int depth, const vector<Move> *search_moves, Move &best_move, const vector<Board> &boards, const Board *last_board)
  {
    _M_alpha = alpha;
    _M_beta = beta;
    _M_depth = depth;
    _M_search_moves = search_moves;
    _M_boards = &boards;
    _M_last_board = last_board;
    for(LazySMPThread &thread : _M_threads) {
      unique_lock<mutex> lock(thread.mutex);
      thread.searcher->clear_searching_stop_flag();
      thread.command = LazySMPCommand::SEARCH;
      thread.start_condition_variable.notify_one();
    }
    LazySMPStop stop(this);
    return _M_main_searcher->search_from_root(alpha, beta, depth, search_moves, best_move, boards, last_board);
  }

  void LazySMPSearcherBase::set_pondering_flag(bool flag)
  { _M_main_searcher->set_pondering_flag(flag); }

  void LazySMPSearcherBase::clear_thinking_stop_flag()
  { _M_main_searcher->clear_thinking_stop_flag(); }

  void LazySMPSearcherBase::clear_pondering_stop_flag()
  { _M_main_searcher->clear_pondering_stop_flag(); }

  void LazySMPSearcherBase::clear_searching_stop_flag()
  { _M_main_searcher->clear_searching_stop_flag(); }

  void LazySMPSearcherBase::stop_thinking()
  { _M_main_searcher->stop_thinking(); }

  void LazySMPSearcherBase::stop_pondering()
  { _M_main_searcher->stop_pondering(); }
    
  void LazySMPSearcherBase::stop_searching()
  { _M_main_searcher->stop_searching(); }

  void LazySMPSearcherBase::set_non_stop_flag(bool flag)
  { _M_main_searcher->set_non_stop_flag(flag); }

  const PVLine &LazySMPSearcherBase::pv_line() const
  { return _M_main_searcher->pv_line(); }

  uint64_t LazySMPSearcherBase::nodes() const
  { return _M_main_searcher->all_nodes(); }

  unsigned LazySMPSearcherBase::thread_count() const
  { return _M_threads.size() + 1; }

  int LazySMPSearcherBase::max_quiescence_depth() const
  { return _M_main_searcher->max_quiescence_depth(); }

  void LazySMPSearcherBase::stop_threads()
  {
    for(LazySMPThread &thread : _M_threads) {
      thread.searcher->stop_searching();
    }
    for(LazySMPThread &thread : _M_threads) {
      unique_lock<mutex> lock(thread.mutex);
      while(thread.result == LazySMPResult::NO_RESULT) {
        thread.stop_condition_variable.wait(lock);
      }
      thread.result = LazySMPResult::NO_RESULT;
    }
  }
}
