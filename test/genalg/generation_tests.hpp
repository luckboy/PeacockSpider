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
#ifndef _GENERATION_TESTS_HPP
#define _GENERATION_TESTS_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

namespace peacockspider
{
  namespace genalg
  {
    namespace test
    {
      class GenerationTests : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(GenerationTests);
        CPPUNIT_TEST(test_generate_individual_function_generates_individual);
        CPPUNIT_TEST(test_generate_individuals_function_generates_individuals);
        CPPUNIT_TEST_SUITE_END();
      public:
        void setUp();

        void tearDown();

        void test_generate_individual_function_generates_individual();
        void test_generate_individuals_function_generates_individuals();
      };
    }
  }
}

#endif
