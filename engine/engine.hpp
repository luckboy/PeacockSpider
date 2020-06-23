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
#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include <condition_variable>
#include <mutex>
#include <thread>
#include "chess.hpp"
#include "search.hpp"

namespace peacockspider
{
  enum class Result
  {
    NONE,
    WHITE_WIN,
    BLACK_WIN,
    DRAW,
    UNFINISHED
  };
  
  class Engine
  {
    enum class Mode
    {
      GAME,
      FORCE,
      ANALISIS
    };

    enum class ThreadCommand
    {
      NO_COMMAND,
      THINK,
      PONDER,
      QUIT
    };

    enum class TimeControlMode
    {
      NONE,
      CLASSICAL,
      INCREMENTAL,
      FIXED_MAX
    };

    struct TimeControl
    {
      TimeControlMode mode;
      unsigned mps;
      unsigned base;
      union
      {
        unsigned inc;
        unsigned time;
      };
    };

    std::mutex _M_mutex;
    std::condition_variable _M_condition_variable;
    Thinker *_M_thinker;
    std::thread _M_thread;
    ThreadCommand _M_thread_command;
    Mode _M_mode;
    Mode _M_previous_mode;
    std::function<void (int, int, unsigned, const Searcher *, const Board *, const Move *move)> _M_thinking_output_function;
    std::function<void (const Board &, Move, const Move *)> _M_move_output_function;
    std::function<void (Result, const std::string &)> _M_result_output_function;
    std::vector<Board> _M_boards;
    Result _M_result;
    std::string _M_result_comment;
    bool _M_has_search_moves;
    std::vector<Move> _M_search_moves;    
    std::unique_ptr<MovePair []> _M_move_pairs;
    std::mutex _M_hint_move_mutex;
    std::mutex _M_limit_mutex;
    TimeControl _M_time_control;
    bool _M_has_remaining_engine_time;
    unsigned _M_remaining_engine_time;
    bool _M_has_remaining_opponent_time;
    unsigned _M_remaining_opponent_time;
    int _M_depth;
    unsigned _M_time;
    std::uint64_t _M_nodes;
    int _M_checkmate_move_count;
    bool _M_pondering_move_flag;
    std::mutex _M_other_mutex;
    bool _M_thinking_output_flag;
    bool _M_auto_pondering_flag;
    bool _M_auto_move_making_flag;
    std::mutex _M_board_mutex;
    Board _M_board;
  public:
    Engine(Thinker *thinker);

    ~Engine();

    void set_thinking_output_function(std::function<void (int, int, unsigned, const Searcher *, const Board *, const Move *)> fun);

    void set_move_output_function(std::function<void (const Board &, Move, const Move *)> fun);

    void set_result_function(std::function<void (Result, const std::string &)> fun);

    void new_game();

    void set_level(unsigned mps, unsigned base, unsigned inc);
    
    void set_time(unsigned time);
    
    void set_depth(int depth);
    
    void set_remaining_engine_time(unsigned time);

    void set_remaining_opponent_time(unsigned time);

    void unset_remaining_engine_time();

    void unset_remaining_opponent_time();

    bool make_move(std::function<bool (const Board &, Move &)> fun);
    
    bool undo();

    bool remove();

    bool set_board(std::function<bool (const Board &, Board &)> fun);

    void set_force_mode();

    void analyze();

    void quit_from_analisis();

    void play_other();

    void go();

    void stop_thinking();

    bool get_hint_move(Move &move);

    void set_result(Result result, const std::string &comment);

    void set_thinking_output_flag(bool flag);
    
    void set_auto_pondering_flag(bool flag);

    void set_auto_move_making_flag(bool flag);

    bool set_board_and_make_moves(std::function<bool (const Board &, Board &, std::vector<Move> &)> fun);

    void go(const std::vector<Move> *search_moves, unsigned white_time, unsigned black_time, unsigned moves_to_go, int depth, std::uint64_t nodes, int checkmate_move_count, unsigned move_time, bool is_pondering);

    void pondering_hit();
    
    void get_board(Board &board);
  private:
    void unsafely_go(bool is_pondering, bool is_time_calculation);

    void unsafely_set_result_for_last_board();

    unsigned unsafely_calculate_time(unsigned moves_to_go);

    void think(Move &best_move);
    
    void ponder();
  };
}

#endif
