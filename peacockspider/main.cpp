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
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <new>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include "consts.hpp"
#include "engine.hpp"
#include "eval.hpp"
#include "protocols.hpp"
#include "search.hpp"
#include "tables.hpp"
#include "transpos_table.hpp"
#include "zobrist.hpp"

using namespace std;
using namespace peacockspider;

namespace
{
  unordered_map<string, function<Searcher *(const EvaluationFunction *, unique_ptr<TranspositionTable> &, size_t, unsigned)>> searcher_functions {
    {
      "single",
      [](const EvaluationFunction *eval_fun, unique_ptr<TranspositionTable> &transpos_table,  size_t tt_entry_count, unsigned thread_count) {
        return new SingleSearcher(eval_fun);
      }
    },
    {
      "singlewithtt",
      [](const EvaluationFunction *eval_fun, unique_ptr<TranspositionTable> &transpos_table,  size_t tt_entry_count, unsigned thread_count) {
        transpos_table = unique_ptr<TranspositionTable>(new TranspositionTable(tt_entry_count));
        return new SingleSearcherWithTT(eval_fun, transpos_table.get());
      }
    },
    {
      "singlepvs",
      [](const EvaluationFunction *eval_fun, unique_ptr<TranspositionTable> &transpos_table, size_t tt_entry_count, unsigned thread_count) {
        return new SinglePVSSearcher(eval_fun);
      }
    },
    {
      "singlepvswithtt",
      [](const EvaluationFunction *eval_fun, unique_ptr<TranspositionTable> &transpos_table,  size_t tt_entry_count, unsigned thread_count) {
        transpos_table = unique_ptr<TranspositionTable>(new TranspositionTable(tt_entry_count));
        return new SinglePVSSearcherWithTT(eval_fun, transpos_table.get());
      }
    },
    {
      "lazysmp",
      [](const EvaluationFunction *eval_fun, unique_ptr<TranspositionTable> &transpos_table,  size_t tt_entry_count, unsigned thread_count) {
        transpos_table = unique_ptr<TranspositionTable>(new TranspositionTable(tt_entry_count));
        return new LazySMPSearcher(eval_fun, transpos_table.get(), thread_count);
      }
    },
    {
      "lazysmppvs",
      [](const EvaluationFunction *eval_fun, unique_ptr<TranspositionTable> &transpos_table,  size_t tt_entry_count, unsigned thread_count) {
        transpos_table = unique_ptr<TranspositionTable>(new TranspositionTable(tt_entry_count));
        return new LazySMPPVSSearcher(eval_fun, transpos_table.get(), thread_count);
      }
    },
    {
      "abdada",
      [](const EvaluationFunction *eval_fun, unique_ptr<TranspositionTable> &transpos_table,  size_t tt_entry_count, unsigned thread_count) {
        transpos_table = unique_ptr<TranspositionTable>(new TranspositionTable(tt_entry_count));
        return new ABDADASearcher(eval_fun, transpos_table.get(), thread_count);
      }
    },
    {
      "abdadapvs",
      [](const EvaluationFunction *eval_fun, unique_ptr<TranspositionTable> &transpos_table,  size_t tt_entry_count, unsigned thread_count) {
        transpos_table = unique_ptr<TranspositionTable>(new TranspositionTable(tt_entry_count));
        return new ABDADAPVSSearcher(eval_fun, transpos_table.get(), thread_count);
      }
    }
  };
}

int main(int argc, char **argv)
{
  try {
    const char *log_file_name = nullptr;
    const char *searcher_name = "single";
    size_t tt_entry_count = (32 * 1024 * 1024) / sizeof(TranspositionTableEntry);
    unsigned thread_count = 1;
    int c;
    opterr = 0;
    while((c = getopt(argc, argv, "hl:np:s:t:")) != -1) {
      switch(c) {
        case 'h':
          cout << "Usage: " << argv[0] << " [<option> ...]" << endl;
          cout << endl;
          cout << "Options:" << endl;
          cout << "  -h                    display this text" << endl;
          cout << "  -l <log file name>    write to log file" << endl;
          cout << "  -n                    set number of threads as number of all processors" << endl;
          cout << "  -p <number>           set number of threads" << endl;
          cout << "  -s <searcher name>    set searcher" << endl;
          cout << "  -t <size>             set transposition table size in megabytes" << endl;
          cout << endl;
          cout << "Searchers:" << endl;
          cout << "  single                single searcher for Alpha-Beta (default)" << endl;
          cout << "  singlewithtt          single searcher with TT for Alpha-Beta" << endl;
          cout << "  singlepvs             single searcher for PVS" << endl;
          cout << "  singlepvswithtt       single searcher with TT for PVS" << endl;
          cout << "  lazysmp               Lazy SMP searcher for Alpha-Beta" << endl;
          cout << "  lazysmppvs            Lazy SMP searcher for PVS" << endl;
          cout << "  abdada                ABDADA searcher for Alpha-Beta" << endl;
          cout << "  abdadapvs             ABDADA searcher for PVS" << endl;
          return 0;
        case 'l':
          log_file_name = optarg;
          break;
        case 'n':
          thread_count = thread::hardware_concurrency();
          if(thread_count == 0) thread_count = 1;
          if(thread_count > MAX_THREAD_COUNT) thread_count = MAX_THREAD_COUNT;
          break;
        case 'p':
        {
          string str(optarg);
          istringstream iss(str);
          iss >> thread_count;
          if(iss.fail() || !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return  1;
          }
          if(thread_count <= 0) {
            cerr << "Too small number" << endl;
            return 1;
          }
          if(thread_count > MAX_THREAD_COUNT) {
            cerr << "Too large number" << endl;
            return 1;
          }
          break;
        }
        case 's':
          searcher_name = optarg;
          break;
        case 't':
        {
          string str(optarg);
          istringstream iss(str);
          size_t tt_size;
          iss >> tt_size;
          if(iss.fail() || !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return  1;
          }
          if(tt_size <= 0) {
            cerr << "Too small number" << endl;
            return 1;
          }
          tt_entry_count = (tt_size * 1024 * 1024) / sizeof(TranspositionTableEntry);
          break;
        }
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
    function<Searcher *(const EvaluationFunction *, unique_ptr<TranspositionTable> &, size_t, unsigned)> searcher_fun;
    auto iter = searcher_functions.find(string(searcher_name));
    if(iter != searcher_functions.end()) {
      searcher_fun = iter->second;
    } else {
      cerr << "Can't find searcher" << endl;
      return 1;
    }
    uint64_t zobrist_seed = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    initialize_tables();
    initialize_zobrist(zobrist_seed);
    unique_ptr<EvaluationFunction> eval_fun(new EvaluationFunction);
    unique_ptr<TranspositionTable> transpos_table;
    unique_ptr<Searcher> searcher(searcher_fun(eval_fun.get(), transpos_table, tt_entry_count, thread_count));
    unique_ptr<Thinker> thinker(new Thinker(searcher.get()));
    unique_ptr<Engine> engine(new Engine(thinker.get()));
    return xboard_loop(engine.get(), ols.get(), uci_loop) ? 0 : 1;
  } catch(bad_alloc &e) {
    cerr << "Can't allocate memory" << endl;
    return 1;
  }
}
