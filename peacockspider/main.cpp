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
#include <fstream>
#include <iostream>
#include <memory>
#include <new>
#include <unistd.h>
#include "engine.hpp"
#include "eval.hpp"
#include "protocols.hpp"
#include "search.hpp"
#include "tables.hpp"

using namespace std;
using namespace peacockspider;

int main(int argc, char **argv)
{
  try {
    const char *log_file_name = nullptr;
    int c;
    opterr = 0;
    while((c = getopt(argc, argv, "hl:")) != -1) {
      switch(c) {
        case 'h':
          cout << "Usage: " << argv[0] << " [<option> ...]" << endl;
          cout << endl;
          cout << "Options:" << endl;
          cout << "  -h                    display this text" << endl;
          cout << "  -l <log file name>    write to log file" << endl;
          return 0;
        case 'l':
          log_file_name = optarg;
          break;
        default:
          cerr << "Incorrect option" << endl;
          return 1;
      }
    }
    unique_ptr<ofstream> ols;
    if(log_file_name != nullptr) {
      ols = unique_ptr<ofstream>(new ofstream(log_file_name, ofstream::app));
      if(!ols->good()) {
        cerr << "Can't open log file" << endl;
        return 1;
      }
    }
    initialize_tables();
    unique_ptr<EvaluationFunction> eval_fun(new EvaluationFunction);
    unique_ptr<Searcher> searcher(new SingleSearcher(eval_fun.get()));
    unique_ptr<Thinker> thinker(new Thinker(searcher.get()));
    unique_ptr<Engine> engine(new Engine(thinker.get()));
    return xboard_loop(engine.get(), ols.get(), uci_loop) ? 0 : 1;
  } catch(bad_alloc &e) {
    cerr << "Can't allocate memory" << endl;
    return 1;
  }
}
