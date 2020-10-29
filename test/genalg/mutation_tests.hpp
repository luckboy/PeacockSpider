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
#ifndef _MUTATION_TESTS_HPP
#define _MUTATION_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      class MutationTests : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(MutationTests);
        CPPUNIT_TEST(test_mutate_individuals_function_mutate_individuals);
        CPPUNIT_TEST_SUITE_END();
      public:
        void setUp();

        void tearDown();

        void test_mutate_individuals_function_mutate_individuals();
      };
    }
  }
}

#endif
