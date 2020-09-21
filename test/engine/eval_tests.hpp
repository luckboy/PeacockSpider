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
#ifndef _EVAL_TESTS_HPP
#define _EVAL_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

namespace peacockspider
{
  namespace test
  {
    class EvaluationTests : public CppUnit::TestFixture
    {
      CPPUNIT_TEST_SUITE(EvaluationTests);
      CPPUNIT_TEST(test_read_evaluation_parameters_function_reads_parent_pair_and_evaluation_parameters);
      CPPUNIT_TEST(test_read_evaluation_parameters_function_reads_parent_pair);
      CPPUNIT_TEST(test_read_evaluation_parameters_function_reads_evaluation_parameters);
      CPPUNIT_TEST(test_read_evaluation_parameters_function_reads_second_parent_pair_and_second_evaluation_parameters);
      CPPUNIT_TEST(test_write_evaluation_parameters_function_writes_parent_pair_and_evaluation_parameters);
      CPPUNIT_TEST(test_skip_evaluation_parameters_function_skips_two_evaluation_parameter_sets);
      CPPUNIT_TEST(test_write_default_evaluation_parameters_function_writes_evaluation_parameters);
      CPPUNIT_TEST_SUITE_END();
    public:
      void setUp();

      void tearDown();

      void test_read_evaluation_parameters_function_reads_parent_pair_and_evaluation_parameters();
      void test_read_evaluation_parameters_function_reads_parent_pair();
      void test_read_evaluation_parameters_function_reads_evaluation_parameters();
      void test_read_evaluation_parameters_function_reads_second_parent_pair_and_second_evaluation_parameters();
      void test_write_evaluation_parameters_function_writes_parent_pair_and_evaluation_parameters();
      void test_skip_evaluation_parameters_function_skips_two_evaluation_parameter_sets();
      void test_write_default_evaluation_parameters_function_writes_evaluation_parameters();
    };
  }
}

#endif
