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
#ifndef _TRANSPOS_TABLE_TESTS_HPP
#define _TRANSPOS_TABLE_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "transpos_table.hpp"

namespace peacockspider
{
  namespace test
  {
    class TranspositionTableTests : public CppUnit::TestFixture
    {
      CPPUNIT_TEST_SUITE(TranspositionTableTests);
      CPPUNIT_TEST(test_transposition_table_stores_entry);
      CPPUNIT_TEST(test_transposition_table_stores_two_entries);
      CPPUNIT_TEST(test_transposition_table_replaces_entry);
      CPPUNIT_TEST(test_transposition_table_does_not_retrieve_entry_for_unequal_hash_key);
      CPPUNIT_TEST(test_transposition_table_does_not_retrieve_entry_for_unequal_index);
      CPPUNIT_TEST(test_transposition_table_does_not_retrieve_entry_for_greater_depth);
      CPPUNIT_TEST(test_transposition_table_retrieves_entry_for_less_depth);
      CPPUNIT_TEST(test_transposition_table_clears_entries);
      CPPUNIT_TEST(test_transposition_table_increases_age);
      CPPUNIT_TEST(test_transposition_table_retrieves_entry_for_upper_bound_value);
      CPPUNIT_TEST(test_transposition_table_does_not_retrieve_entry_for_upper_bound_value);
      CPPUNIT_TEST(test_transposition_table_retrieves_entry_for_lower_bound_value);
      CPPUNIT_TEST(test_transposition_table_does_not_retrieve_entry_for_lower_bound_value);
      CPPUNIT_TEST_SUITE_END();

      TranspositionTable *_M_tt;
    public:
      void setUp();

      void tearDown();

      void test_transposition_table_stores_entry();
      void test_transposition_table_stores_two_entries();
      void test_transposition_table_replaces_entry();
      void test_transposition_table_does_not_retrieve_entry_for_unequal_hash_key();
      void test_transposition_table_does_not_retrieve_entry_for_unequal_index();
      void test_transposition_table_does_not_retrieve_entry_for_greater_depth();
      void test_transposition_table_retrieves_entry_for_less_depth();
      void test_transposition_table_clears_entries();
      void test_transposition_table_increases_age();
      void test_transposition_table_retrieves_entry_for_upper_bound_value();
      void test_transposition_table_does_not_retrieve_entry_for_upper_bound_value();
      void test_transposition_table_retrieves_entry_for_lower_bound_value();
      void test_transposition_table_does_not_retrieve_entry_for_lower_bound_value();
    };
  }
}

#endif
