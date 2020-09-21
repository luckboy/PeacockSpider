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
#include <sstream>
#include "eval_tests.hpp"
#include "eval.hpp"

using namespace std;

namespace peacockspider
{
  namespace test
  {
    CPPUNIT_TEST_SUITE_REGISTRATION(EvaluationTests);

    void EvaluationTests::setUp() {}

    void EvaluationTests::tearDown() {}
    
    void EvaluationTests::test_read_evaluation_parameters_function_reads_parent_pair_and_evaluation_parameters()
    {
      istringstream iss(string("\
1 2\n\
10\n\
20\n\
30\n\
-10\n\
-20\n\
\n\
"));
      ParentPair parent_pair(0, 0);
      int params[5] = { 0, 0, 0, 0, 0 };
      read_evaluation_parameters(iss, &parent_pair, params, 5);
      CPPUNIT_ASSERT_EQUAL(1, parent_pair.first_parent);
      CPPUNIT_ASSERT_EQUAL(2, parent_pair.second_parent);
      CPPUNIT_ASSERT_EQUAL(10, params[0]);
      CPPUNIT_ASSERT_EQUAL(20, params[1]);
      CPPUNIT_ASSERT_EQUAL(30, params[2]);
      CPPUNIT_ASSERT_EQUAL(-10, params[3]);
      CPPUNIT_ASSERT_EQUAL(-20, params[4]);
    }

    void EvaluationTests::test_read_evaluation_parameters_function_reads_parent_pair()
    {
      istringstream iss(string("\
10 20\n\
10\n\
20\n\
30\n\
40\n\
50\n\
\n\
"));
      ParentPair parent_pair(0, 0);
      read_evaluation_parameters(iss, &parent_pair, nullptr, 5);
      CPPUNIT_ASSERT_EQUAL(10, parent_pair.first_parent);
      CPPUNIT_ASSERT_EQUAL(20, parent_pair.second_parent);
    }

    void EvaluationTests::test_read_evaluation_parameters_function_reads_evaluation_parameters()
    {
      istringstream iss(string("\
1 2\n\
100\n\
-100\n\
200\n\
-200\n\
300\n\
\n\
"));
      int params[5] = { 0, 0, 0, 0, 0 };
      read_evaluation_parameters(iss, nullptr, params, 5);
      CPPUNIT_ASSERT_EQUAL(100, params[0]);
      CPPUNIT_ASSERT_EQUAL(-100, params[1]);
      CPPUNIT_ASSERT_EQUAL(200, params[2]);
      CPPUNIT_ASSERT_EQUAL(-200, params[3]);
      CPPUNIT_ASSERT_EQUAL(300, params[4]);
    }

    void EvaluationTests::test_read_evaluation_parameters_function_reads_second_parent_pair_and_second_evaluation_parameters()
    {
      istringstream iss(string("\
1 2\n\
10\n\
20\n\
30\n\
40\n\
50\n\
\n\
3 4\n\
1\n\
2\n\
3\n\
4\n\
5\n\
\n\
"));
      ParentPair parent_pair(0, 0);
      int params[5] = { 0, 0, 0, 0, 0 };
      read_evaluation_parameters(iss, nullptr, nullptr, 5);
      read_evaluation_parameters(iss, &parent_pair, params, 5);
      CPPUNIT_ASSERT_EQUAL(3, parent_pair.first_parent);
      CPPUNIT_ASSERT_EQUAL(4, parent_pair.second_parent);
      CPPUNIT_ASSERT_EQUAL(1, params[0]);
      CPPUNIT_ASSERT_EQUAL(2, params[1]);
      CPPUNIT_ASSERT_EQUAL(3, params[2]);
      CPPUNIT_ASSERT_EQUAL(4, params[3]);
      CPPUNIT_ASSERT_EQUAL(5, params[4]);
    }

    void EvaluationTests::test_write_evaluation_parameters_function_writes_parent_pair_and_evaluation_parameters()
    {
      ostringstream oss;
      ParentPair parent_pair(1, 2);
      int params[5] = { 10, 20, 30, -10, -20 };
      write_evaluation_parameters(oss, parent_pair, params, 5);
      CPPUNIT_ASSERT_EQUAL(string("\
1 2\n\
10\n\
20\n\
30\n\
-10\n\
-20\n\
\n\
"), oss.str());
    }

    void EvaluationTests::test_skip_evaluation_parameters_function_skips_two_evaluation_parameter_sets()
    {
      istringstream iss(string("\
1 2\n\
10\n\
20\n\
30\n\
40\n\
50\n\
\n\
3 4\n\
60\n\
70\n\
80\n\
90\n\
100\n\
\n\
5 6\n\
1\n\
2\n\
3\n\
4\n\
5\n\
\n\
"));
      ParentPair parent_pair(0, 0);
      int params[5] = { 0, 0, 0, 0, 0 };
      skip_evaluation_parameters(iss, 2, 5);
      read_evaluation_parameters(iss, &parent_pair, params, 5);
      CPPUNIT_ASSERT_EQUAL(5, parent_pair.first_parent);
      CPPUNIT_ASSERT_EQUAL(6, parent_pair.second_parent);
      CPPUNIT_ASSERT_EQUAL(1, params[0]);
      CPPUNIT_ASSERT_EQUAL(2, params[1]);
      CPPUNIT_ASSERT_EQUAL(3, params[2]);
      CPPUNIT_ASSERT_EQUAL(4, params[3]);
      CPPUNIT_ASSERT_EQUAL(5, params[4]);
    }

    void EvaluationTests::test_write_default_evaluation_parameters_function_writes_evaluation_parameters()
    {
      ostringstream oss;
      const char *param_names[5] = {
        "EVALUATION_PARAMETER1",
        "EVALUATION_PARAMETER2",
        "EVALUATION_PARAMETER3",
        "EVALUATION_PARAMETER4",
        "EVALUATION_PARAMETER5"
      };
      int params[5] = { 10, 20, 30, -10, -20 };
      write_default_evaluation_parameters(oss, params, param_names, 5);
      CPPUNIT_ASSERT_EQUAL(string("\
// THIS FILE IS GENERATED.\n\
#include \"eval.hpp\"\n\
\n\
namespace peacockspider\n\
{\n\
  int default_evaluation_parameters[MAX_EVALUATION_PARAMETER_COUNT] = {\n\
    10,   // EVALUATION_PARAMETER1\n\
    20,   // EVALUATION_PARAMETER2\n\
    30,   // EVALUATION_PARAMETER3\n\
    -10,  // EVALUATION_PARAMETER4\n\
    -20   // EVALUATION_PARAMETER5\n\
  };\n\
}\n\
"), oss.str());
    }
  }
}
