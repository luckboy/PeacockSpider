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
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <chrono>
#include <iostream>
#include <sstream>
#include "tables.hpp"
#include "zobrist.hpp"

using namespace std;
using namespace peacockspider;

int main(int argc, char **argv)
{
  uint64_t zobrist_seed;
  if(argc >= 2) {
    string str(argv[1]);
    istringstream iss(str);
    iss >> zobrist_seed;
  } else
    zobrist_seed = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
  cout << "zobrist seed: " << zobrist_seed << endl;
  cout << "Testing engine ..." << endl;
  initialize_tables();
  initialize_zobrist(zobrist_seed);
  CppUnit::TextUi::TestRunner runner;  
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  bool result = runner.run();
  cout << "zobrist seed: " << zobrist_seed << endl;
  return result ? 0 : 1;
}
