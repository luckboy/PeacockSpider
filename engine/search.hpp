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
#ifndef _SEARCH_HPP
#define _SEARCH_HPP

#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include "chess.hpp"
#include "eval.hpp"

namespace peacockspider
{
  const int MAX_VALUE = 30000;
  const int MIN_VALUE = -30000;

  const int MOVE_SCORE_PV = 2000000000;
  const int MOVE_SCORE_BEST_MOVE = 1500000000;
  const int MOVE_SCORE_GOOD_MOVE = 1000000000;
  const int MOVE_SCORE_HISTORY = 500000000;
  const int MOVE_SCORE_NONE = 0;

  class ThinkingStopException
  {
    char _M_x;
  };

  class PonderingStopException
  {
    char _M_x;
  };
  
  class SearchingStopException
  {
    char _M_x;
  };
  
  class PVLine
  {
    std::unique_ptr<Move []> _M_moves;
    std::size_t _M_length;
  public:
    PVLine() :
      _M_moves(nullptr), _M_length(0) {}

    PVLine(std::size_t max_length);

    PVLine &operator=(const PVLine &pv_line);

    std::size_t length() const
    { return _M_length; }
    
    Move operator[](std::size_t i) const
    { return _M_moves[i]; }

    void clear()
    { _M_length = 0; }

    void update(Move move, const PVLine &pv_line);

    void set_moves(Move *moves)
    { _M_moves = std::unique_ptr<Move []>(moves); }
  };

  class MoveOrder
  {
    PVLine _M_previous_pv_line;
    int _M_history[2][64][64];
  public:
    MoveOrder(std::size_t max_pv_line_length) :
      _M_previous_pv_line(max_pv_line_length) {}

    int move_score(Move move, int ply, const Board &board, const EvaluationFunction *eval_fun, Move *best_move) const;

    void set_move_scores(MovePairList &move_pairs, int ply, const Board &board, const EvaluationFunction *eval_fun, Move *best_move) const;
    
    void clear();

    void set_previous_pv_line(const PVLine &pv_line);
    
    void increase_history_for_alpha(Side side, Square from, Square to, int depth)
    { _M_history[side_to_index(side)][from][to] += depth; }
    
    void increase_history_for_cutoff(Side side, Square from, Square to, int depth)
    { _M_history[side_to_index(side)][from][to] += depth * 3; }
  };

  class Searcher
  {
  protected:
    Searcher() {}
  public:
    virtual ~Searcher();

    virtual const Board &board() const = 0;

    virtual void set_board(const Board &board) = 0;

    void set_time(unsigned ms);
    
    virtual void set_stop_time(const std::chrono::high_resolution_clock::time_point &time) = 0;

    virtual void unset_stop_time() = 0;
    
    virtual void set_stop_nodes(std::uint64_t nodes) = 0;

    virtual void unset_stop_nodes() = 0;

    virtual void set_previous_pv_line(const PVLine &pv_line) = 0;

    virtual void clear() = 0;

    virtual void clear_for_new_game();

    virtual int search_from_root(int alpha, int beta, int depth, const std::vector<Move> *search_moves, Move &best_move, const std::vector<Board> &boards, const Board *last_board) = 0;

    virtual void set_pondering_flag(bool flag) = 0;
    
    virtual void clear_thinking_stop_flag() = 0;
    
    virtual void clear_pondering_stop_flag() = 0;

    virtual void clear_searching_stop_flag() = 0;
    
    virtual void stop_thinking() = 0;

    virtual void stop_pondering() = 0;
    
    virtual void stop_searching() = 0;

    virtual void set_non_stop_flag(bool flag) = 0;
    
    virtual const PVLine &pv_line() const = 0;
    
    virtual std::uint64_t nodes() const = 0;

    virtual unsigned thread_count() const = 0;
  };

  struct SearchStackElement
  {
    Board board;
    MovePairList move_pairs;
    PVLine pv_line;
  };

  class SingleSearcherBase : public Searcher
  {
  protected:
    const EvaluationFunction *_M_evaluation_function;
    std::unique_ptr<MovePair []> _M_move_pairs;
    std::unique_ptr<SearchStackElement []> _M_stack;
    int _M_max_quiescence_depth;
    MoveOrder _M_move_order;
    std::uint64_t _M_nodes;
    bool _M_has_stop_time;
    std::chrono::high_resolution_clock::time_point _M_stop_time;
    bool _M_has_stop_nodes;
    std::uint64_t _M_stop_nodes;
    bool _M_pondering_flag;
    std::atomic<bool> _M_thinking_stop_flag;
    std::atomic<bool> _M_pondering_stop_flag;
    std::atomic<bool> _M_searching_stop_flag;
    bool _M_non_stop_flag;
  
    SingleSearcherBase(const EvaluationFunction *eval_fun, int max_depth, int max_quiescence_depth);
  public:
    virtual ~SingleSearcherBase();

    virtual const Board &board() const;

    virtual void set_board(const Board &board);
    
    virtual void set_stop_time(const std::chrono::high_resolution_clock::time_point &time);

    virtual void unset_stop_time();
    
    virtual void set_stop_nodes(std::uint64_t nodes);

    virtual void unset_stop_nodes();

    virtual void set_previous_pv_line(const PVLine &pv_line);
    
    virtual void clear();
    
    virtual void set_pondering_flag(bool flag);

    virtual void clear_thinking_stop_flag();

    virtual void clear_pondering_stop_flag();

    virtual void clear_searching_stop_flag();

    virtual void stop_thinking();

    virtual void stop_pondering();
    
    virtual void stop_searching();

    virtual void set_non_stop_flag(bool flag);
    
    virtual const PVLine &pv_line() const;

    virtual std::uint64_t nodes() const;

    virtual unsigned thread_count() const;
  protected:
    virtual void check_stop();
    
    void check_stop_for_nodes()
    { if((_M_nodes & 1023) == 0) check_stop(); }

    int quiescence_search(int alpha, int beta, int depth, int ply);
  };

  class SingleSearcher : public SingleSearcherBase
  {
  public:
    SingleSearcher(const EvaluationFunction *eval_fun, int max_depth = MAX_DEPTH, int max_quiescence_depth = MAX_QUIESCENCE_DEPTH);

    virtual ~SingleSearcher();

    virtual int search_from_root(int alpha, int beta, int depth, const std::vector<Move> *search_moves, Move &best_move, const std::vector<Board> &boards, const Board *last_board);
  protected:
    virtual bool before(int &alpha, int &beta, int depth, int ply, int &best_value, Move &best_move);

    virtual void after(int alpha, int beta, int depth, int ply, int best_value, Move best_move);

    virtual void cutoff(int alpha, int beta, int depth, int ply, int best_value, Move best_move);

    int search(int alpha, int beta, int depth, int ply);
  };

  class Thinker
  {
    Searcher *_M_searcher;
    std::unique_ptr<MovePair> _M_move_pairs;
    int _M_depth;
    int _M_alpha;
    int _M_beta;
    int _M_value;
    bool _M_has_second_search;
    bool _M_must_continue;
    bool _M_has_pondering;
    bool _M_has_best_move;
    Move _M_best_move;
    bool _M_has_hint_move;
    Move _M_hint_move;
    bool _M_has_next_hint_move;
    Move _M_next_hint_move;
    bool _M_has_pondering_move;
    Move _M_pondering_move;
  public:
    Thinker(Searcher *searcher);

    void clear_stop_flags()
    {
      _M_searcher->clear_thinking_stop_flag();
      _M_searcher->clear_pondering_stop_flag();
      _M_searcher->clear_searching_stop_flag();
    }

    void stop_thinking()
    { _M_searcher->stop_thinking(); }

    void stop_pondering()
    { _M_searcher->stop_pondering(); }

    void discard_hint_move()
    { _M_must_continue = false; }

    void clear();
    
    void set_pondering_move()
    {
      _M_has_pondering_move = _M_has_hint_move;
      _M_pondering_move = _M_hint_move;
    }
    
    void unset_hint_move()
    { _M_has_hint_move = false; }

    void unset_next_hint_move()
    { _M_has_next_hint_move = false; }
  private:
    bool think(int max_depth, unsigned ms, const std::vector<Move> *search_moves, std::uint64_t nodes, int checkmate_move_count, Move &best_move, const std::vector<Board> &boards, const Board *last_board, std::function<void (int, int, unsigned, const Searcher *)> fun);
  public:
    bool think(int max_depth, unsigned ms, const std::vector<Move> *search_moves, std::uint64_t nodes, int checkmate_move_count, Move &best_move, const std::vector<Board> &boards, std::function<void (int, int, unsigned, const Searcher *)> fun)
    { return think(max_depth, ms, search_moves, nodes, checkmate_move_count, best_move, boards, nullptr, fun); }

    bool ponder(int max_depth, const std::vector<Move> *search_moves, std::uint64_t nodes, int checkmate_move_count, const std::vector<Board> &boards, std::function<void (int, int, unsigned, const Searcher *)> fun, bool is_pondering_move = true);
  private:
    bool search(int alpha, int beta, const std::vector<Move> *search_moves, Move &best_move, const std::vector<Board> &boards, const Board *last_board, std::function<void (int, int, unsigned, const Searcher *)> fun);
  public:
    bool has_hint_move() const
    { return _M_has_hint_move; }

    Move hint_move() const
    { return _M_hint_move; }
  };
}

#endif
