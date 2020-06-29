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
#include <limits>
#include "thinker_tests.hpp"

using namespace std;

namespace peacockspider
{
  namespace test
  {
    CPPUNIT_TEST_SUITE_REGISTRATION(ThinkerTests);

    void ThinkerTests::setUp()
    {
      _M_evaluation_function = new EvaluationFunction(start_evaluation_parameters);
      _M_searcher = new SingleSearcher(_M_evaluation_function);
      _M_thinker = new Thinker(_M_searcher);
    }

    void ThinkerTests::tearDown()
    {
      delete _M_thinker;
      delete _M_searcher;
      delete _M_evaluation_function;
    }

    void ThinkerTests::test_thinker_thinks()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      vector<Board> boards;
      Board new_board;
      Move best_move;
      int first_depth = 0;
      int old_depth = 0;
      bool is_ok;
      boards.push_back(Board());
      _M_thinker->clear();
      _M_thinker->unset_hint_move();
      _M_thinker->unset_next_hint_move();
      is_ok = true;
      bool result = _M_thinker->think(4, numeric_limits<unsigned>::max(), nullptr, numeric_limits<uint64_t>::max(), 0, best_move, boards, [&](int depth, int value, unsigned ms, const Searcher *searcher) {
        if(old_depth == 0) first_depth = depth;
        is_ok &= (old_depth <= depth);
        is_ok &= (0 < searcher->nodes());
        is_ok &= (0 < searcher->pv_line().length());
        Board tmp_board = searcher->board();
        Board new_tmp_board;
        for(size_t i = 0; i < searcher->pv_line().length(); i++) {
          tmp_board.generate_pseudolegal_moves(move_pairs);
          is_ok &= move_pairs.contain_move(searcher->pv_line()[i]);
          if(!is_ok) break;
          is_ok &= tmp_board.make_move(searcher->pv_line()[i], new_tmp_board);
          if(!is_ok) break;
          tmp_board = new_tmp_board;
        }
        old_depth = depth;
      });
      CPPUNIT_ASSERT_EQUAL(1, first_depth);
      CPPUNIT_ASSERT_EQUAL(4, old_depth);
      CPPUNIT_ASSERT_EQUAL(true, result);
      CPPUNIT_ASSERT_EQUAL(true, is_ok);
      boards.back().generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(best_move));
      CPPUNIT_ASSERT(boards.back().make_move(best_move, new_board));
      CPPUNIT_ASSERT_EQUAL(true, _M_thinker->has_hint_move());
      new_board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(_M_thinker->hint_move()));
      CPPUNIT_ASSERT(new_board.has_legal_move(_M_thinker->hint_move()));
    }

    void ThinkerTests::test_thinker_ponders()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      vector<Board> boards;
      Board new_board;
      Move best_move;
      int first_depth = 0;
      int old_depth = 0;
      bool is_ok;
      boards.push_back(Board());
      _M_thinker->clear();
      _M_thinker->unset_hint_move();
      _M_thinker->unset_next_hint_move();
      is_ok = true;
      bool result = _M_thinker->think(4, numeric_limits<unsigned>::max(), nullptr, numeric_limits<uint64_t>::max(), 0, best_move, boards, [&](int depth, int value, unsigned ms, const Searcher *searcher) {
        if(old_depth == 0) first_depth = depth;
        is_ok &= (old_depth <= depth);
        is_ok &= (0 < searcher->nodes());
        is_ok &= (0 < searcher->pv_line().length());
        Board board = searcher->board();
        Board new_board;
        for(size_t i = 0; i < searcher->pv_line().length(); i++) {
          board.generate_pseudolegal_moves(move_pairs);
          is_ok &= move_pairs.contain_move(searcher->pv_line()[i]);
          if(!is_ok) break;
          is_ok &= board.make_move(searcher->pv_line()[i], new_board);
          if(!is_ok) break;
          board = new_board;
        }
        old_depth = depth;
      });
      CPPUNIT_ASSERT_EQUAL(1, first_depth);
      CPPUNIT_ASSERT_EQUAL(4, old_depth);
      CPPUNIT_ASSERT_EQUAL(true, result);
      CPPUNIT_ASSERT_EQUAL(true, is_ok);
      boards.back().generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(best_move));
      CPPUNIT_ASSERT(boards.back().make_move(best_move, new_board));
      CPPUNIT_ASSERT_EQUAL(true, _M_thinker->has_hint_move());
      new_board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(_M_thinker->hint_move()));
      CPPUNIT_ASSERT(new_board.has_legal_move(_M_thinker->hint_move()));
      boards.push_back(new_board);
      is_ok = true;
      old_depth = 0;
      _M_thinker->set_pondering_move();
      CPPUNIT_ASSERT_EQUAL(_M_thinker->has_hint_move(), _M_thinker->has_pondering_move());
      CPPUNIT_ASSERT(_M_thinker->hint_move() == _M_thinker->pondering_move());
      result = _M_thinker->ponder(4, nullptr, numeric_limits<uint64_t>::max(), 0, boards, [&](int depth, int value, unsigned ms, const Searcher *searcher) {
        if(old_depth == 0) first_depth = depth;
        is_ok &= (old_depth <= depth);
        is_ok &= (0 < searcher->nodes());
        is_ok &= (0 < searcher->pv_line().length());
        Board tmp_board = searcher->board();
        Board new_tmp_board;
        for(size_t i = 0; i < searcher->pv_line().length(); i++) {
          tmp_board.generate_pseudolegal_moves(move_pairs);
          is_ok &= move_pairs.contain_move(searcher->pv_line()[i]);
          if(!is_ok) break;
          is_ok &= tmp_board.make_move(searcher->pv_line()[i], new_tmp_board);
          if(!is_ok) break;
          tmp_board = new_tmp_board;
        }
        old_depth = depth;
      }, true);
      CPPUNIT_ASSERT_EQUAL(1, first_depth);
      CPPUNIT_ASSERT_EQUAL(4, old_depth);
      CPPUNIT_ASSERT_EQUAL(true, result);
      CPPUNIT_ASSERT_EQUAL(true, is_ok);      
    }
    
    void ThinkerTests::test_thinker_thinks_after_pondering_with_move_hitting()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      vector<Board> boards;
      Board new_board;
      Move best_move;
      int first_depth = 0;
      int old_depth = 0;
      bool is_ok;
      boards.push_back(Board());
      _M_thinker->clear();
      _M_thinker->unset_hint_move();
      _M_thinker->unset_next_hint_move();
      is_ok = true;
      bool result = _M_thinker->think(4, numeric_limits<unsigned>::max(), nullptr, numeric_limits<uint64_t>::max(), 0, best_move, boards, [&](int depth, int value, unsigned ms, const Searcher *searcher) {
        if(old_depth == 0) first_depth = depth;
        is_ok &= (old_depth <= depth);
        is_ok &= (0 < searcher->nodes());
        is_ok &= (0 < searcher->pv_line().length());
        Board tmp_board = searcher->board();
        Board new_tmp_board;
        for(size_t i = 0; i < searcher->pv_line().length(); i++) {
          tmp_board.generate_pseudolegal_moves(move_pairs);
          is_ok &= move_pairs.contain_move(searcher->pv_line()[i]);
          if(!is_ok) break;
          is_ok &= tmp_board.make_move(searcher->pv_line()[i], new_tmp_board);
          if(!is_ok) break;
          tmp_board = new_tmp_board;
        }
        old_depth = depth;
      });
      CPPUNIT_ASSERT_EQUAL(1, first_depth);
      CPPUNIT_ASSERT_EQUAL(4, old_depth);
      CPPUNIT_ASSERT_EQUAL(true, result);
      CPPUNIT_ASSERT_EQUAL(true, is_ok);
      boards.back().generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(best_move));
      CPPUNIT_ASSERT(boards.back().make_move(best_move, new_board));
      CPPUNIT_ASSERT_EQUAL(true, _M_thinker->has_hint_move());
      new_board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(_M_thinker->hint_move()));
      CPPUNIT_ASSERT(new_board.has_legal_move(_M_thinker->hint_move()));
      boards.push_back(new_board);
      is_ok = true;
      old_depth = 0;
      _M_thinker->set_pondering_move();
      CPPUNIT_ASSERT_EQUAL(_M_thinker->has_hint_move(), _M_thinker->has_pondering_move());
      CPPUNIT_ASSERT(_M_thinker->hint_move() == _M_thinker->pondering_move());
      result = _M_thinker->ponder(2, nullptr, numeric_limits<uint64_t>::max(), 0, boards, [&](int depth, int value, unsigned ms, const Searcher *searcher) {
        if(old_depth == 0) first_depth = depth;
        is_ok &= (old_depth <= depth);
        is_ok &= (0 < searcher->nodes());
        is_ok &= (0 < searcher->pv_line().length());
        Board tmp_board = searcher->board();
        Board new_tmp_board;
        for(size_t i = 0; i < searcher->pv_line().length(); i++) {
          tmp_board.generate_pseudolegal_moves(move_pairs);
          is_ok &= move_pairs.contain_move(searcher->pv_line()[i]);
          if(!is_ok) break;
          is_ok &= tmp_board.make_move(searcher->pv_line()[i], new_tmp_board);
          if(!is_ok) break;
          tmp_board = new_tmp_board;
        }
        old_depth = depth;
      }, true);
      CPPUNIT_ASSERT_EQUAL(1, first_depth);
      CPPUNIT_ASSERT_EQUAL(2, old_depth);
      CPPUNIT_ASSERT_EQUAL(true, result);
      CPPUNIT_ASSERT_EQUAL(true, is_ok);
      boards.back().make_move(_M_thinker->hint_move(), new_board);
      boards.push_back(new_board);
      is_ok = true;
      old_depth = 0;
      result = _M_thinker->think(4, numeric_limits<unsigned>::max(), nullptr, numeric_limits<uint64_t>::max(), 0, best_move, boards, [&](int depth, int value, unsigned ms, const Searcher *searcher) {
        if(old_depth == 0) first_depth = depth;
        is_ok &= (old_depth <= depth);
        is_ok &= (0 < searcher->nodes());
        is_ok &= (0 < searcher->pv_line().length());
        Board tmp_board = searcher->board();
        Board new_tmp_board;
        for(size_t i = 0; i < searcher->pv_line().length(); i++) {
          tmp_board.generate_pseudolegal_moves(move_pairs);
          is_ok &= move_pairs.contain_move(searcher->pv_line()[i]);
          if(!is_ok) break;
          is_ok &= tmp_board.make_move(searcher->pv_line()[i], new_tmp_board);
          if(!is_ok) break;
          tmp_board = new_tmp_board;
        }
        old_depth = depth;
      });
      CPPUNIT_ASSERT_EQUAL(3, first_depth);
      CPPUNIT_ASSERT_EQUAL(4, old_depth);
      CPPUNIT_ASSERT_EQUAL(true, result);
      CPPUNIT_ASSERT_EQUAL(true, is_ok);
      boards.back().generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(best_move));
      CPPUNIT_ASSERT(boards.back().make_move(best_move, new_board));
      CPPUNIT_ASSERT_EQUAL(true, _M_thinker->has_hint_move());
      new_board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(_M_thinker->hint_move()));
      CPPUNIT_ASSERT(new_board.has_legal_move(_M_thinker->hint_move()));
    }

    void ThinkerTests::test_thinker_thinks_after_pondering_without_move_hitting()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      vector<Board> boards;
      Board new_board;
      Move best_move;
      int first_depth = 0;
      int old_depth = 0;
      bool is_ok;
      boards.push_back(Board());
      _M_thinker->clear();
      _M_thinker->unset_hint_move();
      _M_thinker->unset_next_hint_move();
      is_ok = true;
      bool result = _M_thinker->think(4, numeric_limits<unsigned>::max(), nullptr, numeric_limits<uint64_t>::max(), 0, best_move, boards, [&](int depth, int value, unsigned ms, const Searcher *searcher) {
        if(old_depth == 0) first_depth = depth;
        is_ok &= (old_depth <= depth);
        is_ok &= (0 < searcher->nodes());
        is_ok &= (0 < searcher->pv_line().length());
        Board tmp_board = searcher->board();
        Board new_tmp_board;
        for(size_t i = 0; i < searcher->pv_line().length(); i++) {
          tmp_board.generate_pseudolegal_moves(move_pairs);
          is_ok &= move_pairs.contain_move(searcher->pv_line()[i]);
          if(!is_ok) break;
          is_ok &= tmp_board.make_move(searcher->pv_line()[i], new_tmp_board);
          if(!is_ok) break;
          tmp_board = new_tmp_board;
        }
        old_depth = depth;
      });
      CPPUNIT_ASSERT_EQUAL(1, first_depth);
      CPPUNIT_ASSERT_EQUAL(4, old_depth);
      CPPUNIT_ASSERT_EQUAL(true, result);
      CPPUNIT_ASSERT_EQUAL(true, is_ok);
      boards.back().generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(best_move));
      CPPUNIT_ASSERT(boards.back().make_move(best_move, new_board));
      CPPUNIT_ASSERT_EQUAL(true, _M_thinker->has_hint_move());
      new_board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(_M_thinker->hint_move()));
      CPPUNIT_ASSERT(new_board.has_legal_move(_M_thinker->hint_move()));
      boards.push_back(new_board);
      is_ok = true;
      old_depth = 0;
      _M_thinker->set_pondering_move();
      CPPUNIT_ASSERT_EQUAL(_M_thinker->has_hint_move(), _M_thinker->has_pondering_move());
      CPPUNIT_ASSERT(_M_thinker->hint_move() == _M_thinker->pondering_move());
      result = _M_thinker->ponder(2, nullptr, numeric_limits<uint64_t>::max(), 0, boards, [&](int depth, int value, unsigned ms, const Searcher *searcher) {
        if(old_depth == 0) first_depth = depth;
        is_ok &= (old_depth <= depth);
        is_ok &= (0 < searcher->nodes());
        is_ok &= (0 < searcher->pv_line().length());
        Board tmp_board = searcher->board();
        Board new_tmp_board;
        for(size_t i = 0; i < searcher->pv_line().length(); i++) {
          tmp_board.generate_pseudolegal_moves(move_pairs);
          is_ok &= move_pairs.contain_move(searcher->pv_line()[i]);
          if(!is_ok) break;
          is_ok &= tmp_board.make_move(searcher->pv_line()[i], new_tmp_board);
          if(!is_ok) break;
          tmp_board = new_tmp_board;
        }
        old_depth = depth;
      }, true);
      CPPUNIT_ASSERT_EQUAL(1, first_depth);
      CPPUNIT_ASSERT_EQUAL(2, old_depth);
      CPPUNIT_ASSERT_EQUAL(true, result);
      CPPUNIT_ASSERT_EQUAL(true, is_ok);
      boards.back().generate_pseudolegal_moves(move_pairs);
      Move other_move;
      for(size_t i = 0; i < move_pairs.length(); i++) {
        if(move_pairs[i].move != _M_thinker->hint_move()) {
          other_move = move_pairs[i].move;
          break;
        }
      }
      boards.back().make_move(other_move, new_board);
      boards.push_back(new_board);
      _M_thinker->discard_hint_move();
      is_ok = true;
      old_depth = 0;
      result = _M_thinker->think(4, numeric_limits<unsigned>::max(), nullptr, numeric_limits<uint64_t>::max(), 0, best_move, boards, [&](int depth, int value, unsigned ms, const Searcher *searcher) {
        if(old_depth == 0) first_depth = depth;
        is_ok &= (old_depth <= depth);
        is_ok &= (0 < searcher->nodes());
        is_ok &= (0 < searcher->pv_line().length());
        Board tmp_board = searcher->board();
        Board new_tmp_board;
        for(size_t i = 0; i < searcher->pv_line().length(); i++) {
          tmp_board.generate_pseudolegal_moves(move_pairs);
          is_ok &= move_pairs.contain_move(searcher->pv_line()[i]);
          if(!is_ok) break;
          is_ok &= tmp_board.make_move(searcher->pv_line()[i], new_tmp_board);
          if(!is_ok) break;
          tmp_board = new_tmp_board;
        }
        old_depth = depth;
      });
      CPPUNIT_ASSERT_EQUAL(1, first_depth);
      CPPUNIT_ASSERT_EQUAL(4, old_depth);
      CPPUNIT_ASSERT_EQUAL(true, result);
      CPPUNIT_ASSERT_EQUAL(true, is_ok);
      boards.back().generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(best_move));
      CPPUNIT_ASSERT(boards.back().make_move(best_move, new_board));
      CPPUNIT_ASSERT_EQUAL(true, _M_thinker->has_hint_move());
      new_board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(_M_thinker->hint_move()));
      CPPUNIT_ASSERT(new_board.has_legal_move(_M_thinker->hint_move()));
    }

    void ThinkerTests::test_thinker_ponders_without_pondering_move()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      vector<Board> boards;
      Board new_board;
      Move best_move;
      int first_depth = 0;
      int old_depth = 0;
      bool is_ok;
      boards.push_back(Board());
      boards.back().make_move(Move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE), new_board);
      boards.push_back(new_board);
      _M_thinker->clear();
      _M_thinker->unset_hint_move();
      _M_thinker->unset_next_hint_move();
      is_ok = true;
      bool result = _M_thinker->ponder(4, nullptr, numeric_limits<uint64_t>::max(), 0, boards, [&](int depth, int value, unsigned ms, const Searcher *searcher) {
        if(old_depth == 0) first_depth = depth;
        is_ok &= (old_depth <= depth);
        is_ok &= (0 < searcher->nodes());
        is_ok &= (0 < searcher->pv_line().length());
        Board tmp_board = searcher->board();
        Board new_tmp_board;
        for(size_t i = 0; i < searcher->pv_line().length(); i++) {
          tmp_board.generate_pseudolegal_moves(move_pairs);
          is_ok &= move_pairs.contain_move(searcher->pv_line()[i]);
          if(!is_ok) break;
          is_ok &= tmp_board.make_move(searcher->pv_line()[i], new_tmp_board);
          if(!is_ok) break;
          tmp_board = new_tmp_board;
        }
        old_depth = depth;
      }, false);
      CPPUNIT_ASSERT_EQUAL(1, first_depth);
      CPPUNIT_ASSERT_EQUAL(4, old_depth);
      CPPUNIT_ASSERT_EQUAL(true, result);
      CPPUNIT_ASSERT_EQUAL(true, is_ok);
    }
  }
}
