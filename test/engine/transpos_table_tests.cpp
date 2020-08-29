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
#include "transpos_table_tests.hpp"

using namespace std;

namespace peacockspider
{
  namespace test
  {
    CPPUNIT_TEST_SUITE_REGISTRATION(TranspositionTableTests);

    void TranspositionTableTests::setUp()
    { _M_tt = new TranspositionTable(65536); }

    void TranspositionTableTests::tearDown()
    { delete _M_tt; }
    
    void TranspositionTableTests::test_transposition_table_stores_entry()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x123456), -10, 10, 2, 5, Move(Piece::PAWN, E2, E4, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -10; beta = 10;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->retrieve(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move));
      CPPUNIT_ASSERT_EQUAL(-10, alpha);
      CPPUNIT_ASSERT_EQUAL(10, beta);
      CPPUNIT_ASSERT_EQUAL(5, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE) == best_move);
    }
    
    void TranspositionTableTests::test_transposition_table_stores_two_entries()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x1234), -50, 50, 2, 2, Move(Piece::PAWN, E2, E3, PromotionPiece::NONE)));
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x567890), -100, 100, 4, 10, Move(Piece::PAWN, D2, D4, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -50; beta = 50;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->retrieve(static_cast<HashKey>(0x1234), alpha, beta, 2, best_value, best_move));
      CPPUNIT_ASSERT_EQUAL(-50, alpha);
      CPPUNIT_ASSERT_EQUAL(50, beta);
      CPPUNIT_ASSERT_EQUAL(2, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE) == best_move);
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->retrieve(static_cast<HashKey>(0x567890), alpha, beta, 4, best_value, best_move));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(10, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, D2, D4, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_replaces_entry()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x1234), -10, 10, 2, 5, Move(Piece::PAWN, E2, E4, PromotionPiece::NONE)));
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x121234), -100, 100, 4, 50, Move(Piece::PAWN, D2, D3, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->retrieve(static_cast<HashKey>(0x121234), alpha, beta, 4, best_value, best_move));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(50, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, D2, D3, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_unequal_hash_key()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x1234), -10, 10, 2, 5, Move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -10; beta = 10;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, E2, E4, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve(static_cast<HashKey>(0x121234), alpha, beta, 2, best_value, best_move));
      CPPUNIT_ASSERT_EQUAL(-10, alpha);
      CPPUNIT_ASSERT_EQUAL(10, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_unequal_index()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x1234), -100, 100, 2, 50, Move(Piece::KNIGHT, G1, F3, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, E2, E4, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve(static_cast<HashKey>(0x1235), alpha, beta, 2, best_value, best_move));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_greater_depth()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x1234), -10, 10, 2, 5, Move(Piece::PAWN, D2, D3, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -10; beta = 10;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve(static_cast<HashKey>(0x1234), alpha, beta, 4, best_value, best_move));
      CPPUNIT_ASSERT_EQUAL(-10, alpha);
      CPPUNIT_ASSERT_EQUAL(10, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, D2, D3, PromotionPiece::NONE) == best_move);
    }
    
    void TranspositionTableTests::test_transposition_table_retrieves_entry_for_less_depth()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x567890), -10, 10, 4, 1, Move(Piece::PAWN, E2, E3, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -10; beta = 10;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->retrieve(static_cast<HashKey>(0x567890), alpha, beta, 2, best_value, best_move));
      CPPUNIT_ASSERT_EQUAL(-10, alpha);
      CPPUNIT_ASSERT_EQUAL(10, beta);
      CPPUNIT_ASSERT_EQUAL(1, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_clears_entries()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x1234), -10, 10, 2, 5, Move(Piece::PAWN, D2, D3, PromotionPiece::NONE)));
      _M_tt->clear();
      int alpha, beta, best_value;
      Move best_move;
      alpha = -10; beta = 10;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, E2, E4, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve(static_cast<HashKey>(0x1234), alpha, beta, 2, best_value, best_move));
      CPPUNIT_ASSERT_EQUAL(-10, alpha);
      CPPUNIT_ASSERT_EQUAL(10, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_increases_age()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x5678), -100, 100, 2, 50, Move(Piece::PAWN, D2, D3, PromotionPiece::NONE)));
      _M_tt->increase_age_or_clear();
      int alpha, beta, best_value;
      Move best_move;
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, E2, E4, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve(static_cast<HashKey>(0x5678), alpha, beta, 2, best_value, best_move));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_retrieves_entry_for_upper_bound_value()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x123456), -10, 10, 2, -50, Move(Piece::PAWN, E2, E3, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -20; beta = 10;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->retrieve(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move));
      CPPUNIT_ASSERT_EQUAL(-20, alpha);
      CPPUNIT_ASSERT(10 >= beta);
      CPPUNIT_ASSERT_EQUAL(-50, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_upper_bound_value()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x123456), -10, 10, 2, -15, Move(Piece::PAWN, E2, E3, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -20; beta = 10;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move));
      CPPUNIT_ASSERT_EQUAL(-20, alpha);
      CPPUNIT_ASSERT(10 >= beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE) == best_move);
    }
    
    void TranspositionTableTests::test_transposition_table_retrieves_entry_for_lower_bound_value()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x123456), -10, 10, 2, 50, Move(Piece::PAWN, E2, E3, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -10; beta = 20;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->retrieve(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move));
      CPPUNIT_ASSERT(-10 <= alpha);
      CPPUNIT_ASSERT_EQUAL(20, beta);
      CPPUNIT_ASSERT_EQUAL(50, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE) == best_move);
    }
    
    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_lower_bound_value()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x123456), -10, 10, 2, 15, Move(Piece::PAWN, E2, E3, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -10; beta = 20;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move));
      CPPUNIT_ASSERT(-10 <= alpha);
      CPPUNIT_ASSERT_EQUAL(20, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_retrieves_entry_for_abdada()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x567890), -50, 50, 2, 10, Move(Piece::PAWN, D2, D4, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -50; beta = 50;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x567890), alpha, beta, 2, best_value, best_move, false));
      CPPUNIT_ASSERT_EQUAL(-50, alpha);
      CPPUNIT_ASSERT_EQUAL(50, beta);
      CPPUNIT_ASSERT_EQUAL(10, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, D2, D4, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_abdada_and_unequal_hash_key()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x5678), -100, 100, 4, 50, Move(Piece::KNIGHT, G1, F3, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, E2, E4, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x125678), alpha, beta, 4, best_value, best_move, false));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_abdada_and_unequal_index()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x5678), -10, 10, 4, 5, Move(Piece::KNIGHT, B1, C3, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -10; beta = 10;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, E2, E4, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x5679), alpha, beta, 4, best_value, best_move, false));
      CPPUNIT_ASSERT_EQUAL(-10, alpha);
      CPPUNIT_ASSERT_EQUAL(10, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_abdada_and_greater_depth()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x1234), -100, 100, 2, 50, Move(Piece::PAWN, E2, E3, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x1234), alpha, beta, 4, best_value, best_move, false));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E3, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_retrieves_entry_for_abdada_and_less_depth()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x123456), -100, 100, 4, 10, Move(Piece::PAWN, E2, E4, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, false));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(10, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_retrieves_entry_for_abdada_and_upper_bound_value()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x123456), -10, 10, 2, -40, Move(Piece::PAWN, E2, E4, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -30; beta = 10;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, false));
      CPPUNIT_ASSERT_EQUAL(-30, alpha);
      CPPUNIT_ASSERT(10 >= beta);
      CPPUNIT_ASSERT_EQUAL(-40, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_abdada_and_upper_bound_value()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x123456), -10, 10, 2, -20, Move(Piece::PAWN, E2, E4, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -30; beta = 10;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, false));
      CPPUNIT_ASSERT_EQUAL(-30, alpha);
      CPPUNIT_ASSERT(10 >= beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_retrieves_entry_for_abdada_and_lower_bound_value()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x123456), -10, 10, 2, 40, Move(Piece::PAWN, E2, E4, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -10; beta = 20;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, false));
      CPPUNIT_ASSERT(-10 <= alpha);
      CPPUNIT_ASSERT_EQUAL(20, beta);
      CPPUNIT_ASSERT_EQUAL(40, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_abdada_and_lower_bound_value()
    {
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->store(static_cast<HashKey>(0x123456), -10, 10, 2, 20, Move(Piece::PAWN, E2, E4, PromotionPiece::NONE)));
      int alpha, beta, best_value;
      Move best_move;
      alpha = -10; beta = 30;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, false));
      CPPUNIT_ASSERT(-10 <= alpha);
      CPPUNIT_ASSERT_EQUAL(30, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, E2, E4, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_abdada_and_non_exclusive()
    {
      int alpha, beta, best_value;
      Move best_move;
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, E2, E4, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, false));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_abdada_and_non_exclusive_after_retrieve()
    {
      int alpha, beta, best_value;
      Move best_move;
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, E2, E4, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, false));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, E2, E4, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, false));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
    }
    
    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_abdada_and_exclusive()
    {
      int alpha, beta, best_value;
      Move best_move;
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, E1, E2, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, true));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
    }

    void TranspositionTableTests::test_transposition_table_does_not_retrieve_entry_for_abdada_and_exclusive_after_retrieve()
    {
      int alpha, beta, best_value;
      Move best_move;
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, false));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, E1, E3, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(true, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, true));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(VALUE_ON_EVALUATION, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
    }
    
    void TranspositionTableTests::test_transposition_table_decreases_thread_count()
    {
      int alpha, beta, best_value;
      Move best_move;
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, -1, -1, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, false));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
      _M_tt->decrease_thread_count(static_cast<HashKey>(0x123456));
      alpha = -100; beta = 100;
      best_value = MIN_VALUE;
      best_move = Move(Piece::PAWN, E1, E3, PromotionPiece::NONE);
      CPPUNIT_ASSERT_EQUAL(false, _M_tt->retrieve_for_abdada(static_cast<HashKey>(0x123456), alpha, beta, 2, best_value, best_move, true));
      CPPUNIT_ASSERT_EQUAL(-100, alpha);
      CPPUNIT_ASSERT_EQUAL(100, beta);
      CPPUNIT_ASSERT_EQUAL(MIN_VALUE, best_value);
      CPPUNIT_ASSERT(Move(Piece::PAWN, -1, -1, PromotionPiece::NONE) == best_move);
    }
  }
}
