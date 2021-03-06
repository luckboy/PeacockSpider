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
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>
#include "chess.hpp"
#include "eval.hpp"
#include "transpos_table.hpp"

namespace peacockspider
{
  class LazySMPStop;
  class ABDADAThreadCountDecrement;

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

    ~PVLine();

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

    virtual std::uint64_t all_nodes() const;

    virtual unsigned thread_count() const = 0;
    
    virtual int max_quiescence_depth() const = 0;
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
    std::atomic<std::uint64_t> _M_nodes;
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
    
    virtual int max_quiescence_depth() const;
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

  class SingleSearcherWithTT : public SingleSearcher
  {
  protected:
    TranspositionTable *_M_transposition_table;
  public:
    SingleSearcherWithTT(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, int max_depth = MAX_DEPTH, int max_quiescence_depth = MAX_QUIESCENCE_DEPTH);

    virtual ~SingleSearcherWithTT();

    virtual void clear();
    
    virtual void clear_for_new_game();
  protected:
    virtual bool before(int &alpha, int &beta, int depth, int ply, int &best_value, Move &best_move);

    virtual void after(int alpha, int beta, int depth, int ply, int best_value, Move best_move);

    virtual void cutoff(int alpha, int beta, int depth, int ply, int best_value, Move best_move);
  };

  class SinglePVSSearcher : public SingleSearcherBase
  {
  public:
    SinglePVSSearcher(const EvaluationFunction *eval_fun, int max_depth = MAX_DEPTH, int max_quiescence_depth = MAX_QUIESCENCE_DEPTH);

    virtual ~SinglePVSSearcher();

    virtual int search_from_root(int alpha, int beta, int depth, const std::vector<Move> *search_moves, Move &best_move, const std::vector<Board> &boards, const Board *last_board);
  protected:
    virtual bool before(int &alpha, int &beta, int depth, int ply, int &best_value, Move &best_move);

    virtual void after(int alpha, int beta, int depth, int ply, int best_value, Move best_move);

    virtual void cutoff(int alpha, int beta, int depth, int ply, int best_value, Move best_move);

    int search(int alpha, int beta, int depth, int ply, bool can_make_null_move);
  };

  class SinglePVSSearcherWithTT : public SinglePVSSearcher
  {
  protected:
    TranspositionTable *_M_transposition_table;
  public:
    SinglePVSSearcherWithTT(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, int max_depth = MAX_DEPTH, int max_quiescence_depth = MAX_QUIESCENCE_DEPTH);

    virtual ~SinglePVSSearcherWithTT();

    virtual void clear();
    
    virtual void clear_for_new_game();
  protected:
    virtual bool before(int &alpha, int &beta, int depth, int ply, int &best_value, Move &best_move);

    virtual void after(int alpha, int beta, int depth, int ply, int best_value, Move best_move);

    virtual void cutoff(int alpha, int beta, int depth, int ply, int best_value, Move best_move);
  };

  enum class LazySMPCommand
  {
    NO_COMMAND,
    SEARCH,
    QUIT
  };

  enum class LazySMPResult
  {
    NO_RESULT,
    STOP
  };

  struct LazySMPThread
  {
    std::thread thread;
    std::unique_ptr<Searcher> searcher;
    std::mutex mutex;
    std::condition_variable start_condition_variable;
    LazySMPCommand command;
    std::condition_variable stop_condition_variable;
    LazySMPResult result;
    
    LazySMPThread() {}
    
    LazySMPThread(LazySMPThread &&thread) :
      thread(std::move(thread.thread)), searcher(std::move(thread.searcher)), command(thread.command), result(thread.result) {}
  };

  class LazySMPSingleSearcher : public SingleSearcherWithTT
  {
    const Searcher *_M_main_searcher;
    const std::vector<LazySMPThread> &_M_threads;
  public:
    LazySMPSingleSearcher(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, const Searcher *main_searcher, const std::vector<LazySMPThread> &threads, int max_depth, int max_quiescence_depth);

    virtual ~LazySMPSingleSearcher();

    virtual void clear();

    virtual void clear_for_new_game();

    virtual std::uint64_t all_nodes() const;
  };

  class LazySMPSinglePVSSearcher : public SinglePVSSearcherWithTT
  {
    const Searcher *_M_main_searcher;
    const std::vector<LazySMPThread> &_M_threads;
  public:
    LazySMPSinglePVSSearcher(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, const Searcher *main_searcher, const std::vector<LazySMPThread> &threads, int max_depth, int max_quiescence_depth);

    virtual ~LazySMPSinglePVSSearcher();

    virtual void clear();

    virtual void clear_for_new_game();

    virtual std::uint64_t all_nodes() const;
  };

  class LazySMPSearcherBase : public Searcher
  {
    friend LazySMPStop;
  protected:
    TranspositionTable *_M_transposition_table;
    std::unique_ptr<Searcher> _M_main_searcher;
    std::vector<LazySMPThread> _M_threads;
    int _M_alpha;
    int _M_beta;
    int _M_depth;
    const std::vector<Move> *_M_search_moves;
    const std::vector<Board> *_M_boards;
    const Board *_M_last_board;

    LazySMPSearcherBase(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, std::function<Searcher *(const EvaluationFunction *, TranspositionTable *, const Searcher *, const std::vector<LazySMPThread> &, int, int)> fun, unsigned thread_count, int max_depth, int max_quiescence_depth);
  public:
    virtual ~LazySMPSearcherBase();

    virtual const Board &board() const;

    virtual void set_board(const Board &board);
    
    virtual void set_stop_time(const std::chrono::high_resolution_clock::time_point &time);

    virtual void unset_stop_time();
    
    virtual void set_stop_nodes(std::uint64_t nodes);

    virtual void unset_stop_nodes();

    virtual void set_previous_pv_line(const PVLine &pv_line);

    virtual void clear();

    virtual void clear_for_new_game();

    virtual int search_from_root(int alpha, int beta, int depth, const std::vector<Move> *search_moves, Move &best_move, const std::vector<Board> &boards, const Board *last_board);

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
    
    virtual int max_quiescence_depth() const;
  private:
    void stop_threads();
  };

  class LazySMPStop
  {
    LazySMPSearcherBase *_M_searcher;
  public:
    LazySMPStop(LazySMPSearcherBase *searcher) :
      _M_searcher(searcher) {}

    ~LazySMPStop()
    { _M_searcher->stop_threads(); }
  };

  class LazySMPSearcher : public LazySMPSearcherBase
  {
  public:
    LazySMPSearcher(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, unsigned thread_count, int max_depth = MAX_DEPTH, int max_quiescence_depth = MAX_QUIESCENCE_DEPTH);

    virtual ~LazySMPSearcher();
  };
  
  class LazySMPPVSSearcher : public LazySMPSearcherBase
  {
  public:
    LazySMPPVSSearcher(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, unsigned thread_count, int max_depth = MAX_DEPTH, int max_quiescence_depth = MAX_QUIESCENCE_DEPTH);

    virtual ~LazySMPPVSSearcher();
  };

  enum class ABDADACommand
  {
    NO_COMMAND,
    SEARCH,
    QUIT
  };
  
  enum class ABDADAResult
  {
    NO_RESULT = 0,    
    THINKING_STOP = 1,
    PONDERING_STOP = 2,
    VALUE = 4
  };

  inline ABDADAResult operator~(ABDADAResult result)
  { return static_cast<ABDADAResult>(static_cast<int>(result) ^ 7); }
  
  inline ABDADAResult operator&(ABDADAResult result1, ABDADAResult result2)
  { return static_cast<ABDADAResult>(static_cast<int>(result1) & static_cast<int>(result2)); }
  
  inline ABDADAResult operator&=(ABDADAResult &result1, ABDADAResult result2)
  { result1 = result1 & result2; return result1; }

  inline ABDADAResult operator|(ABDADAResult result1, ABDADAResult result2)
  { return static_cast<ABDADAResult>(static_cast<int>(result1) | static_cast<int>(result2)); }
  
  inline ABDADAResult operator|=(ABDADAResult &result1, ABDADAResult result2)
  { result1 = result1 | result2; return result1; }

  inline ABDADAResult operator^(ABDADAResult result1, ABDADAResult result2)
  { return static_cast<ABDADAResult>(static_cast<int>(result1) ^ static_cast<int>(result2)); }
  
  inline ABDADAResult operator^=(ABDADAResult &result1, ABDADAResult result2)
  { result1 = result1 ^ result2; return result1; }
  
  struct ABDADAThread
  {
    std::thread thread;
    std::unique_ptr<Searcher> searcher;
    std::mutex mutex;
    std::condition_variable start_condition_variable;
    ABDADACommand command;
    std::condition_variable stop_condition_variable;
    ABDADAResult result;
    int value;
    Move best_move;
    
    ABDADAThread() {}
    
    ABDADAThread(ABDADAThread &&thread) :
      thread(std::move(thread.thread)), searcher(std::move(thread.searcher)), command(thread.command), result(thread.result), value(thread.value) {}
  };

  class ABDADASingleSearcherBase : public SingleSearcherBase
  {
    friend ABDADAThreadCountDecrement;
  protected:
    TranspositionTable *_M_transposition_table;
    const std::vector<ABDADAThread> &_M_threads;

    ABDADASingleSearcherBase(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, const std::vector<ABDADAThread> &threads, int max_depth, int max_quiescence_depth);
  public:
    virtual ~ABDADASingleSearcherBase();

    virtual std::uint64_t all_nodes() const;
  protected:
    virtual void decrease_thread_count(int ply);
  };

  class ABDADAThreadCountDecrement
  {
    ABDADASingleSearcherBase *_M_searcher;
    int _M_ply;
  public:
    ABDADAThreadCountDecrement(ABDADASingleSearcherBase *searcher, int ply) :
      _M_searcher(searcher), _M_ply(ply) {}

    ~ABDADAThreadCountDecrement()
    { _M_searcher->decrease_thread_count(_M_ply); }
  };
  
  class ABDADASingleSearcher : public ABDADASingleSearcherBase
  {
  public:
    ABDADASingleSearcher(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, const std::vector<ABDADAThread> &threads, int max_depth, int max_quiescence_depth);

    virtual ~ABDADASingleSearcher();

    virtual int search_from_root(int alpha, int beta, int depth, const std::vector<Move> *search_moves, Move &best_move, const std::vector<Board> &boards, const Board *last_board);
  protected:
    virtual bool before(int &alpha, int &beta, int depth, int ply, int &best_value, Move &best_move, bool is_exclusive);

    virtual void after(int alpha, int beta, int depth, int ply, int best_value, Move best_move);

    virtual void cutoff(int alpha, int beta, int depth, int ply, int best_value, Move best_move);

    int search(int alpha, int beta, int depth, int ply, bool is_exclusive_node);
  };

  class ABDADASinglePVSSearcher : public ABDADASingleSearcherBase
  {
  public:
    ABDADASinglePVSSearcher(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, const std::vector<ABDADAThread> &threads, int max_depth, int max_quiescence_depth);

    virtual ~ABDADASinglePVSSearcher();

    virtual int search_from_root(int alpha, int beta, int depth, const std::vector<Move> *search_moves, Move &best_move, const std::vector<Board> &boards, const Board *last_board);
  protected:
    virtual bool before(int &alpha, int &beta, int depth, int ply, int &best_value, Move &best_move, bool is_exclusive);

    virtual void after(int alpha, int beta, int depth, int ply, int best_value, Move best_move);

    virtual void cutoff(int alpha, int beta, int depth, int ply, int best_value, Move best_move);

    int search(int alpha, int beta, int depth, int ply, bool can_make_null_move, bool is_exclusive_node);
  };

  class ABDADASearcherBase : public Searcher
  {
  protected:
    TranspositionTable *_M_transposition_table;
    std::vector<ABDADAThread> _M_threads;
    ABDADAThread *_M_best_thread;
    int _M_alpha;
    int _M_beta;
    int _M_depth;
    const std::vector<Move> *_M_search_moves;
    const std::vector<Board> *_M_boards;
    const Board *_M_last_board;

    ABDADASearcherBase(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, std::function<Searcher *(const EvaluationFunction *, TranspositionTable *, const std::vector<ABDADAThread> &, int, int)> fun, unsigned thread_count, int max_depth, int max_quiescence_depth);
  public:
    virtual ~ABDADASearcherBase();

    virtual const Board &board() const;

    virtual void set_board(const Board &board);
    
    virtual void set_stop_time(const std::chrono::high_resolution_clock::time_point &time);

    virtual void unset_stop_time();
    
    virtual void set_stop_nodes(std::uint64_t nodes);

    virtual void unset_stop_nodes();

    virtual void set_previous_pv_line(const PVLine &pv_line);

    virtual void clear();

    virtual void clear_for_new_game();

    virtual int search_from_root(int alpha, int beta, int depth, const std::vector<Move> *search_moves, Move &best_move, const std::vector<Board> &boards, const Board *last_board);

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
    
    virtual int max_quiescence_depth() const;
  };

  class ABDADASearcher : public ABDADASearcherBase
  {
  public:
    ABDADASearcher(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, unsigned thread_count, int max_depth = MAX_DEPTH, int max_quiescence_depth = MAX_QUIESCENCE_DEPTH);

    virtual ~ABDADASearcher();
  };

  class ABDADAPVSSearcher : public ABDADASearcherBase
  {
  public:
    ABDADAPVSSearcher(const EvaluationFunction *eval_fun, TranspositionTable *transpos_table, unsigned thread_count, int max_depth = MAX_DEPTH, int max_quiescence_depth = MAX_QUIESCENCE_DEPTH);

    virtual ~ABDADAPVSSearcher();
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

    bool has_hint_move() const
    { return _M_has_hint_move; }

    Move hint_move() const
    { return _M_hint_move; }

    void unset_hint_move()
    { _M_has_hint_move = false; }

    void unset_next_hint_move()
    { _M_has_next_hint_move = false; }

    bool has_pondering_move() const
    { return _M_has_pondering_move; }

    Move pondering_move() const
    { return _M_pondering_move; }

    void set_pondering_move()
    {
      _M_has_pondering_move = _M_has_hint_move;
      _M_pondering_move = _M_hint_move;
    }
  private:
    bool think(int max_depth, unsigned ms, const std::vector<Move> *search_moves, std::uint64_t nodes, int checkmate_move_count, Move &best_move, const std::vector<Board> &boards, const Board *last_board, std::function<void (int, int, unsigned, const Searcher *)> fun);
  public:
    bool think(int max_depth, unsigned ms, const std::vector<Move> *search_moves, std::uint64_t nodes, int checkmate_move_count, Move &best_move, const std::vector<Board> &boards, std::function<void (int, int, unsigned, const Searcher *)> fun)
    { return think(max_depth, ms, search_moves, nodes, checkmate_move_count, best_move, boards, nullptr, fun); }

    bool ponder(int max_depth, const std::vector<Move> *search_moves, std::uint64_t nodes, int checkmate_move_count, const std::vector<Board> &boards, std::function<void (int, int, unsigned, const Searcher *)> fun, bool is_pondering_move = true);
  private:
    bool search(int alpha, int beta, const std::vector<Move> *search_moves, Move &best_move, const std::vector<Board> &boards, const Board *last_board, std::function<void (int, int, unsigned, const Searcher *)> fun);
  };
}

#endif
