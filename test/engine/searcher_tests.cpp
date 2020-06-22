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
#include "searcher_tests.hpp"

using namespace std;

namespace peacockspider
{
  namespace test
  {
    void SearcherTests::test_searcher_finds_best_move_for_initial_board()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      Board board;
      vector<Board> boards;
      Move best_move;
      _M_searcher->clear_for_new_game();
      _M_searcher->set_board(board);
      boards.push_back(board);
      int value = _M_searcher->search_from_root(MIN_VALUE, MAX_VALUE, 3, nullptr, best_move, boards, nullptr);
      CPPUNIT_ASSERT(value >= MIN_VALUE && value <= MAX_VALUE);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(best_move));
      CPPUNIT_ASSERT(board.has_legal_move(best_move));
      CPPUNIT_ASSERT(0 < _M_searcher->nodes());
      CPPUNIT_ASSERT(0 < _M_searcher->pv_line().length());
      CPPUNIT_ASSERT(best_move == _M_searcher->pv_line()[0]);
      Board tmp_board = board;
      bool are_pv_line_legal_moves = true;
      for(size_t i = 0; i < _M_searcher->pv_line().length(); i++) {
        Board new_tmp_board;
        tmp_board.generate_pseudolegal_moves(move_pairs);
        if(!move_pairs.contain_move(_M_searcher->pv_line()[i])) {
          are_pv_line_legal_moves = false;
          break;
        }
        if(!tmp_board.make_move(_M_searcher->pv_line()[i], new_tmp_board)) {
          are_pv_line_legal_moves = false;
          break;
        }
        tmp_board = new_tmp_board;
      }
      CPPUNIT_ASSERT(are_pv_line_legal_moves);
    }

    void SearcherTests::test_searcher_finds_best_move_for_white_side_and_pieces()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      Board board("r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 0 4");
      vector<Board> boards;
      Move best_move;
      _M_searcher->clear_for_new_game();
      _M_searcher->set_board(board);
      boards.push_back(board);
      int value = _M_searcher->search_from_root(MIN_VALUE, MAX_VALUE, 3, nullptr, best_move, boards, nullptr);
      CPPUNIT_ASSERT(value >= MIN_VALUE && value <= MAX_VALUE);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(best_move));
      CPPUNIT_ASSERT(board.has_legal_move(best_move));
      CPPUNIT_ASSERT(0 < _M_searcher->nodes());
      CPPUNIT_ASSERT(0 < _M_searcher->pv_line().length());
      CPPUNIT_ASSERT(best_move == _M_searcher->pv_line()[0]);
      Board tmp_board = board;
      bool are_pv_line_legal_moves = true;
      for(size_t i = 0; i < _M_searcher->pv_line().length(); i++) {
        Board new_tmp_board;
        tmp_board.generate_pseudolegal_moves(move_pairs);
        if(!move_pairs.contain_move(_M_searcher->pv_line()[i])) {
          are_pv_line_legal_moves = false;
          break;
        }
        if(!tmp_board.make_move(_M_searcher->pv_line()[i], new_tmp_board)) {
          are_pv_line_legal_moves = false;
          break;
        }
        tmp_board = new_tmp_board;
      }
      CPPUNIT_ASSERT(are_pv_line_legal_moves);
    }

    void SearcherTests::test_searcher_finds_best_move_for_black_side_and_pieces()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      Board board("r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2NP1N2/PPP2PPP/R1BQKB1R b KQkq - 0 4");
      vector<Board> boards;
      Move best_move;
      _M_searcher->clear_for_new_game();
      _M_searcher->set_board(board);
      boards.push_back(board);
      int value = _M_searcher->search_from_root(MIN_VALUE, MAX_VALUE, 3, nullptr, best_move, boards, nullptr);
      CPPUNIT_ASSERT(value >= MIN_VALUE && value <= MAX_VALUE);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(best_move));
      CPPUNIT_ASSERT(board.has_legal_move(best_move));
      CPPUNIT_ASSERT(0 < _M_searcher->nodes());
      CPPUNIT_ASSERT(0 < _M_searcher->pv_line().length());
      CPPUNIT_ASSERT(best_move == _M_searcher->pv_line()[0]);
      Board tmp_board = board;
      bool are_pv_line_legal_moves = true;
      for(size_t i = 0; i < _M_searcher->pv_line().length(); i++) {
        Board new_tmp_board;
        tmp_board.generate_pseudolegal_moves(move_pairs);
        if(!move_pairs.contain_move(_M_searcher->pv_line()[i])) {
          are_pv_line_legal_moves = false;
          break;
        }
        if(!tmp_board.make_move(_M_searcher->pv_line()[i], new_tmp_board)) {
          are_pv_line_legal_moves = false;
          break;
        }
        tmp_board = new_tmp_board;
      }
      CPPUNIT_ASSERT(are_pv_line_legal_moves);
    }

    void SearcherTests::test_searcher_finds_best_move_for_white_side_and_endgame()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      Board board("4k3/8/1p1n4/8/8/5N1P/8/4K3 w - - 0 1");
      vector<Board> boards;
      Move best_move;
      _M_searcher->clear_for_new_game();
      _M_searcher->set_board(board);
      boards.push_back(board);
      int value = _M_searcher->search_from_root(MIN_VALUE, MAX_VALUE, 3, nullptr, best_move, boards, nullptr);
      CPPUNIT_ASSERT(value >= MIN_VALUE && value <= MAX_VALUE);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(best_move));
      CPPUNIT_ASSERT(board.has_legal_move(best_move));
      CPPUNIT_ASSERT(0 < _M_searcher->nodes());
      CPPUNIT_ASSERT(0 < _M_searcher->pv_line().length());
      CPPUNIT_ASSERT(best_move == _M_searcher->pv_line()[0]);
      Board tmp_board = board;
      bool are_pv_line_legal_moves = true;
      for(size_t i = 0; i < _M_searcher->pv_line().length(); i++) {
        Board new_tmp_board;
        tmp_board.generate_pseudolegal_moves(move_pairs);
        if(!move_pairs.contain_move(_M_searcher->pv_line()[i])) {
          are_pv_line_legal_moves = false;
          break;
        }
        if(!tmp_board.make_move(_M_searcher->pv_line()[i], new_tmp_board)) {
          are_pv_line_legal_moves = false;
          break;
        }
        tmp_board = new_tmp_board;
      }
      CPPUNIT_ASSERT(are_pv_line_legal_moves);
    }
    
    void SearcherTests::test_searcher_finds_best_move_for_black_side_and_endgame()
    {
      unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
      MovePairList move_pairs(tmp_move_pairs.get(), 0);
      Board board("4k3/8/1p1n4/8/8/5N1P/4K3/8 b - - 0 1");
      vector<Board> boards;
      Move best_move;
      _M_searcher->clear_for_new_game();
      _M_searcher->set_board(board);
      boards.push_back(board);
      int value = _M_searcher->search_from_root(MIN_VALUE, MAX_VALUE, 3, nullptr, best_move, boards, nullptr);
      CPPUNIT_ASSERT(value >= MIN_VALUE && value <= MAX_VALUE);
      board.generate_pseudolegal_moves(move_pairs);
      CPPUNIT_ASSERT(move_pairs.contain_move(best_move));
      CPPUNIT_ASSERT(board.has_legal_move(best_move));
      CPPUNIT_ASSERT(0 < _M_searcher->nodes());
      CPPUNIT_ASSERT(0 < _M_searcher->pv_line().length());
      CPPUNIT_ASSERT(best_move == _M_searcher->pv_line()[0]);
      Board tmp_board = board;
      bool are_pv_line_legal_moves = true;
      for(size_t i = 0; i < _M_searcher->pv_line().length(); i++) {
        Board new_tmp_board;
        tmp_board.generate_pseudolegal_moves(move_pairs);
        if(!move_pairs.contain_move(_M_searcher->pv_line()[i])) {
          are_pv_line_legal_moves = false;
          break;
        }
        if(!tmp_board.make_move(_M_searcher->pv_line()[i], new_tmp_board)) {
          are_pv_line_legal_moves = false;
          break;
        }
        tmp_board = new_tmp_board;
      }
      CPPUNIT_ASSERT(are_pv_line_legal_moves);
    }
  }
}
