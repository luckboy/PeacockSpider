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
#include <atomic>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <mutex>
#include <sstream>
#include <string>
#include "gen_alg_sig.hpp"
#include "tournament.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    namespace
    {
      mutex system_mutex;
      
      string tournament_file_name(int iter)
      {
        ostringstream oss;
        oss << iter << ".pgn";
        return oss.str();
      }
    }
    
    SingleTable::SingleTable(int max_depth, unsigned time, function<Searcher *(const EvaluationFunction *, int)> fun, bool is_game_saving)
      : _M_has_game_saving(is_game_saving), _M_max_depth(max_depth), _M_time(time)
    {
      _M_white_evaluation_function = unique_ptr<EvaluationFunction>(new EvaluationFunction(start_evaluation_parameters));
      _M_white_searcher = unique_ptr<Searcher>(fun(_M_white_evaluation_function.get(), max_depth));
      _M_white_thinker = unique_ptr<Thinker>(new Thinker(_M_white_searcher.get()));
      _M_black_evaluation_function = unique_ptr<EvaluationFunction>(new EvaluationFunction(start_evaluation_parameters));
      _M_black_searcher = unique_ptr<Searcher>(fun(_M_black_evaluation_function.get(), max_depth));
      _M_black_thinker = unique_ptr<Thinker>(new Thinker(_M_black_searcher.get()));
    }

    SingleTable::~SingleTable() {}

    bool SingleTable::start_tournament(int iter)
    {
      if(_M_has_game_saving) {
        lock_guard<mutex> guard(system_mutex);
        ofstream ofs(tournament_file_name(iter));
        if(!ofs.good()) {
          cerr << "Can't open PGN file" << endl;
          return false;
        }
      }
      return true;
    }

    pair<Result, bool> SingleTable::play(int iter, int round, int player1, int *params1, int player2, int *params2)
    {
      vector<Board> boards;
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      boards.reserve(256);
      boards.push_back(Board());
      Game game;
      game.moves().reserve(255);
      {
        ostringstream oss;
        oss << "Peacock Spider genetic algorithm tournament i" << iter;
        game.set_event(oss.str());
      }
      {
        game.set_site("computer");
      }
      {
        lock_guard<mutex> guard(system_mutex);
        time_t t = time(nullptr);
        struct tm *tm = localtime(&t);
        ostringstream oss;
        oss << setw(4) << setfill('0') << (tm->tm_year + 1900) << ".";
        oss << setw(2) << setfill('0') << (tm->tm_mon + 1) << ".";
        oss << setw(2) << setfill('0') << tm->tm_mday;
        game.set_date(oss.str());
      }
      {
        ostringstream oss;
        oss << round;
        game.set_round(oss.str());
      }
      {
        ostringstream oss;
        oss << "Peacock Spider i" << iter << "p" << player1;
        game.set_white(oss.str());
      }
      {
        ostringstream oss;
        oss << "Peacock Spider i" << iter << "p" << player2;
        game.set_black(oss.str());
      }
      _M_white_evaluation_function->set(params1);
      _M_black_evaluation_function->set(params2);
      _M_white_thinker->clear();
      _M_white_thinker->unset_hint_move();
      _M_white_thinker->unset_next_hint_move();
      _M_black_thinker->clear();
      _M_black_thinker->unset_hint_move();
      _M_black_thinker->unset_next_hint_move();
      Result result;
      while(true) {
        Board tmp_board;
        Move move;
        result = Result::UNFINISHED;
        atomic_thread_fence(memory_order_seq_cst);
        if(is_genetic_algorithm_stop != 0) {
          lock_guard<mutex> guard(system_mutex);
          cerr << "Stopped" << endl;
          return make_pair(result, false);
        }
        _M_white_thinker->think(_M_max_depth, _M_time, nullptr, numeric_limits<uint64_t>::max(), 0, move, boards, [](int depth, int value, unsigned ms, const Searcher *searcher) {});
        if(!boards.back().make_move(move, tmp_board)) {
          game.set_result(result);
          break;
        }
        boards.push_back(tmp_board);
        game.moves().push_back(move);
        result = result_for_boards(boards, move_pairs);
        if(result != Result::NONE) {
          game.set_result(result);
          break;
        }
        result = Result::UNFINISHED;
        atomic_thread_fence(memory_order_seq_cst);
        if(is_genetic_algorithm_stop != 0) {
          lock_guard<mutex> guard(system_mutex);
          cerr << "Stopped" << endl;
          return make_pair(result, false);
        }
        _M_black_thinker->think(_M_max_depth, _M_time, nullptr, numeric_limits<uint64_t>::max(), 0, move, boards, [](int depth, int value, unsigned ms, const Searcher *searcher) {});
        if(!boards.back().make_move(move, tmp_board)) {
          game.set_result(result);
          break;
        }
        boards.push_back(tmp_board);
        game.moves().push_back(move);
        result = result_for_boards(boards, move_pairs);
        if(result != Result::NONE) {
          game.set_result(result);
          break;
        }
      }
      if(_M_has_game_saving) {
        lock_guard<mutex> guard(system_mutex);
        ofstream ofs(tournament_file_name(iter), ofstream::app);
        if(!ofs.good()) {
          cerr << "Can't open PGN file" << endl;
          return make_pair(result, false);
        }
        write_pgn(ofs, game);
      }
      return make_pair(result, true);
    }
  }
}
