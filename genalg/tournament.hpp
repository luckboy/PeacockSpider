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
#ifndef _TOURNAMENT_HPP
#define _TOURNAMENT_HPP

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <ostream>
#include <queue>
#include <thread>
#include <utility>
#include <vector>
#include "chess.hpp"
#include "game.hpp"
#include "search.hpp"

namespace peacockspider
{
  namespace genalg
  {
    class Table
    {
    protected:
      Table() {}
    public:
      virtual ~Table();

      virtual bool start_tournament(int iter) = 0;

      virtual std::pair<Result, bool> play(int iter, int round, int player1, int *params1, int player2, int *params2) = 0;
    };
    
    class SingleTable : public Table
    {
      std::unique_ptr<EvaluationFunction> _M_white_evaluation_function;
      std::unique_ptr<Searcher> _M_white_searcher;
      std::unique_ptr<Thinker> _M_white_thinker;
      std::unique_ptr<EvaluationFunction> _M_black_evaluation_function;
      std::unique_ptr<Searcher> _M_black_searcher;
      std::unique_ptr<Thinker> _M_black_thinker;
      bool _M_has_game_saving;
      int _M_max_depth;
      unsigned _M_time;
    public:
      SingleTable(int max_depth, unsigned time, std::function<Searcher *(const EvaluationFunction *, int)> fun, bool is_game_saving = true);

      virtual ~SingleTable();

      virtual bool start_tournament(int iter);

      virtual std::pair<Result, bool> play(int iter, int round, int player1, int *params1, int player2, int *params2);
    };

    struct MatchResult
    {
      int scores[2];
    };

    class TournamentResult
    {
      int _M_player_count;
      std::vector<int> _M_scores;
      std::vector<int> _M_sorted_player_indices;
      std::vector<std::vector<MatchResult>> _M_crosstable;
    public:
      TournamentResult(int player_count);

      ~TournamentResult();
      
      int player_count() const
      { return _M_player_count; }

      int score(int i) const
      { return _M_scores[i]; }
      
      int sorted_player_index(int i) const
      { return _M_sorted_player_indices[i]; }

      MatchResult crosstable_match_result(int i, int j) const
      { return _M_crosstable[i][j]; }
      
      void clear();

      void set_game_result(int player1, int player2, int match_game_index, Result result);
      
      void sort_player_indices();
    };

    class Tournament
    {
    protected:
      TournamentResult _M_result;
      std::function<void (int, int, int, int, Result)> _M_tournament_output_function;

      Tournament(int player_count);
    public:
      virtual ~Tournament();

      std::function<void (int, int, int, int, Result)> tournament_output_function() const;

      void set_tournament_output_function(std::function<void (int, int, int, int, Result)> fun);

      const TournamentResult &result() const
      { return _M_result; }

      virtual bool play(int iter, const std::vector<std::shared_ptr<int []>> &param_arrays) = 0;
    };

    class SingleTournament : public Tournament
    {
      std::unique_ptr<Table> _M_table;
    public:
      SingleTournament(int player_count, std::function<Table *()> fun);

      virtual ~SingleTournament();

      virtual bool play(int iter, const std::vector<std::shared_ptr<int []>> &param_arrays);
    };
    
    struct QueueElement
    {
      int round;
      int player1;
      int player2;
      int match_game_index;
      
      QueueElement() {}
      
      QueueElement(int round, int player1, int player2, int match_game_index) :
        round(round), player1(player1), player2(player2), match_game_index(match_game_index) {}
    };

    enum class ParallelCommand
    {
      NO_COMMAND,
      PLAY,
      QUIT
    };
    
    enum class ParallelResult
    {
      NO_RESULT,
      STOP
    };

    struct ParallelThread
    {
      std::thread thread;
      std::unique_ptr<Table> table;
      std::mutex mutex;
      std::condition_variable start_condition_variable;
      ParallelCommand command;
      std::condition_variable stop_condition_variable;
      ParallelResult result;

      ParallelThread() {}

      ParallelThread(ParallelThread &&thread) :
        thread(move(thread.thread)), table(move(thread.table)), command(thread.command), result(thread.result) {}
    };
    
    class ParallelTournament : public Tournament
    {
      std::vector<ParallelThread> _M_threads;
      std::mutex _M_mutex;
      std::queue<QueueElement> _M_queue;
      bool _M_has_error;
      int _M_iter;
      const std::vector<std::shared_ptr<int []>> *_M_param_arrays;
    public:
      ParallelTournament(int player_count, std::function<Table *()> fun, unsigned thread_count);

      virtual ~ParallelTournament();

      virtual bool play(int iter, const std::vector<std::shared_ptr<int []>> &param_arrays);
    };

    std::ostream &operator<<(std::ostream &os, const TournamentResult &result);
  }
}

#endif
