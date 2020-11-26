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
#include <ios>
#include <iostream>
#include <sstream>
#include <limits>
#include <memory>
#include <new>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include "consts.hpp"
#include "eval.hpp"
#include "fitness.hpp"
#include "gen_alg.hpp"
#include "gen_alg_sig.hpp"
#include "gen_alg_vars.hpp"
#include "generator.hpp"
#include "search.hpp"
#include "tables.hpp"
#include "tournament.hpp"
#include "zobrist.hpp"

using namespace std;
using namespace peacockspider;
using namespace peacockspider::genalg;

namespace
{
  unordered_map<string, function<Searcher *(const EvaluationFunction *, int)>> searcher_functions {
    {
      "single",
      [](const EvaluationFunction *eval_fun, int max_depth) {
        return new SingleSearcher(eval_fun, max_depth);
      }
    },
    {
      "singlepvs",
      [](const EvaluationFunction *eval_fun, int max_depth) {
        return new SinglePVSSearcher(eval_fun, max_depth);
      }
    }
  };
  
  unordered_map<string, function<Tournament *(int, function<Table *()>, unsigned)>> tournament_functions {
    {
      "single",
      [](int player_count, function<Table *()> fun, unsigned thread_count) {
        return new SingleTournament(player_count, fun); 
      }
    },
    {
      "parallel",
      [](int player_count, function<Table *()> fun, unsigned thread_count) {
        return new ParallelTournament(player_count, fun, thread_count); 
      }
    },
  };
  
  struct Configuration
  {
    string searcher_name;
    int max_depth;
    unsigned time;
    int individual_count;
    int best_individual_count;
    int child_count;
    int mutation_count;
  };
  
  void split_field(const string &field, string &field_name, string &field_value)
  {
    auto iter = field.begin();
    while(iter != field.end() && (*iter == ' ' || *iter == '\t')) iter++;
    auto field_name_iter = iter;
    while(iter != field.end() && *iter != ' ' && *iter != '\t') iter++;
    field_name = string(field_name_iter, iter);
    while(iter != field.end() && (*iter == ' ' || *iter == '\t')) iter++;
    auto field_value_iter = iter;
    field_value = string(field_value_iter, field.end());
  }
  
  bool read_configuration(istream &is, Configuration &config)
  {
    do {
      string line;
      getline(is, line);
      string field = line;
      auto iter = line.end();
      if(!line.empty()) {
        iter--;
        if(*iter == '\r') field = string(line.begin(), iter);
      }
      string field_name, field_value;
      split_field(field, field_name, field_value);
      if(!field_name.empty()) {
        if(field_name == "searcher_name") {
          config.searcher_name = field_value;
        } else if(field_name == "max_depth") {
          istringstream iss(field_value);
          iss >> config.max_depth;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return false;
          }
          if(config.max_depth < 1) {
            cerr << "Too small number" << endl;
            return false;
          }
          if(config.max_depth > MAX_DEPTH) {
            cerr << "Too large number" << endl;
            return false;
          }
        } else if(field_name == "time") {
          istringstream iss(field_value);
          iss >> config.time;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return false;
          }
        } else if(field_name == "individual_count") {
          istringstream iss(field_value);
          iss >> config.individual_count;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return false;
          }
          if(config.individual_count < 2) {
            cerr << "Too small number" << endl;
            return false;
          }
        } else if(field_name == "best_individual_count") {
          istringstream iss(field_value);
          iss >> config.best_individual_count;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return false;
          }
          if(config.best_individual_count < 1) {
            cerr << "Too small number" << endl;
            return false;
          }
        } else if(field_name == "child_count") {
          istringstream iss(field_value);
          iss >> config.child_count;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return false;
          }
          if(config.child_count < 1) {
            cerr << "Too small number" << endl;
            return false;
          }
        } else if(field_name == "mutation_count") {
          istringstream iss(field_value);
          iss >> config.mutation_count;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return false;
          }
          if(config.mutation_count < 0) {
            cerr << "Too small number" << endl;
            return false;
          }
        } else {
          cerr << "Incorrect field name" << endl;
          return false;
        }
      }
    } while(!is.eof());
    return true;
  }

  bool load_configuration(Configuration &config)
  {
    ifstream ifs("config.txt");
    if(!ifs.good()) return true;
    return read_configuration(ifs, config);
  }
  
  void write_configuration(ostream &os, const Configuration &config)
  {
    os << "searcher_name " << config.searcher_name << "\n";
    os << "max_depth " << config.max_depth << "\n";
    os << "time " << config.time << "\n";
    os << "individual_count " << config.individual_count << "\n";
    os << "best_individual_count " << config.best_individual_count << "\n";
    os << "child_count " << config.child_count << "\n";
    os << "mutation_count " << config.mutation_count << "\n";
  }
  
  bool save_configuration(const Configuration &config)
  {
    ofstream ofs("config.txt");
    if(!ofs.good()) {
      cerr << "Can't open configuration file" << endl;
      return false;
    }
    write_configuration(ofs, config);
    return true;
  }
  
  enum class Command
  {
    GENETIC_ALGORITHM,
    DISPLAY_INDIVIDUAL,
    GENERATE_DEFAULT_EVAL_PARAMS_CPP_FILE
  };

  int evaluation_parameters[MAX_EVALUATION_PARAMETER_COUNT];
}

int main(int argc, char **argv)
{
  try {
    Configuration config;
    Command cmd = Command::GENETIC_ALGORITHM;
    int iter_count = 100;
    const char *tournament_name = "parallel";
    bool can_display_eval_params = false;
    bool can_save_game = true;
    bool can_save_tournament_result = true;
    bool can_save_eval_params = true;
    unsigned thread_count = 1;
    streamoff eval_skipping_count = 0;
    config.searcher_name = string("singlepvs");
    config.max_depth = 6;
    config.time = numeric_limits<unsigned>::max();
    config.individual_count = 8;
    config.best_individual_count = 2;
    config.child_count = 4;
    config.mutation_count = 4;
    if(!load_configuration(config)) return 1;
    int c;
    opterr = 0;
    while((c = getopt(argc, argv, "a:b:c:d:eg:hi:jm:nop:s:t:T:uvw")) != -1) {
      switch(c) {
        case 'a':
        {
          string str(optarg);
          istringstream iss(str);
          iss >> config.individual_count;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return 1;
          }
          if(config.individual_count < 2) {
            cerr << "Too small number" << endl;
            return 1;
          }
          break;
        }
        case 'b':
        {
          string str(optarg);
          istringstream iss(str);
          iss >> config.best_individual_count;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return 1;
          }
          if(config.best_individual_count < 1) {
            cerr << "Too small number" << endl;
            return 1;
          }
          break;
        }
        case 'c':
        {
          string str(optarg);
          istringstream iss(str);
          iss >> config.child_count;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return 1;
          }
          if(config.child_count < 1) {
            cerr << "Too small number" << endl;
            return 1;
          }
          break;
        }
        case 'd':
        {
          string str(optarg);
          istringstream iss(str);
          iss >> config.max_depth;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return 1;
          }
          if(config.max_depth < 1) {
            cerr << "Too small number" << endl;
            return 1;
          }
          if(config.max_depth > MAX_DEPTH) {
            cerr << "Too large number" << endl;
            return 1;
          }
          break;
        }
        case 'e':
          can_display_eval_params = true;
          break;
        case 'g':
        {
          string str(optarg);
          istringstream iss(str);
          iss >> eval_skipping_count;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return 1;
          }
          break;
        }
        case 'h':
          cout << "Usage: " << argv[0] << " [<option> ...]" << endl;
          cout << endl;
          cout << "Options:" << endl;
          cout << "  -a <number>           set number of all individuals (by default 8)" << endl;
          cout << "  -b <number>           set number of best individuals (by default 2)" << endl;
          cout << "  -c <number>           set number of children (by default 4)" << endl;
          cout << "  -d <depth>            set maximal depth (by default 6)" << endl;
          cout << "  -e                    display evaluation parameters with individual" << endl;
          cout << "  -g <number>           skip evaluation parameters" << endl;
          cout << "  -h                    display this text" << endl;
          cout << "  -i <iterations>       set number of iterations (by default 100)" << endl;
          cout << "  -j                    display individual" << endl;
          cout << "  -m <number>           set number of mutations" << endl;
          cout << "  -n                    set number of threads as number of all processors" << endl;
          cout << "  -o                    generate default_eval_params.cpp file" << endl;
          cout << "  -p <number>           set number of threads" << endl;
          cout << "  -s <searcher name>    set searcher" << endl;
          cout << "  -t <time>             set time in milliseconds" << endl;
          cout << "  -T <tournament name>  set tournament" << endl;
          cout << "  -u                    don't save games" << endl;
          cout << "  -v                    don't save torunament results" << endl;
          cout << "  -w                    don't save evaluation parameters without last" << endl;
          cout << endl;
          cout << "Searchers:" << endl;
          cout << "  single                single searcher for Alpha-Beta" << endl;
          cout << "  singlepvs             single searcher for PVS (default)" << endl;
          cout << "Tournaments:" << endl;
          cout << "  single                single tournament" << endl;
          cout << "  parallel              parallel tournament (default)" << endl;
          cout << "Files:" << endl;
          cout << "  conifg.txt            auto generated configuration file" << endl;
          cout << "  iter.txt              file with number of iteration" << endl;
          cout << "  <iteration>.eps       evaluation parameter file" << endl;
          cout << "  <iteration>.pgn       tournament file" << endl;
          cout << "  <iteration>.txt       tournament result file" << endl;
          return 0;
        case 'i':
        {
          string str(optarg);
          istringstream iss(str);
          iss >> iter_count;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return 1;
          }
          if(iter_count < 0) {
            cerr << "Too small number" << endl;
            return 1;
          }
          break;
        }
        case 'j':
          cmd = Command::DISPLAY_INDIVIDUAL;
          break;
        case 'm':
        {
          string str(optarg);
          istringstream iss(str);
          iss >> config.mutation_count;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return 1;
          }
          if(config.mutation_count < 0) {
            cerr << "Too small number" << endl;
            return 1;
          }
          break;
        }
        case 'n':
          thread_count = thread::hardware_concurrency();
          if(thread_count == 0) thread_count = 1;
          break;
        case 'o':
          cmd = Command::GENERATE_DEFAULT_EVAL_PARAMS_CPP_FILE;
          break;
        case 'p':
        {
          string str(optarg);
          istringstream iss(str);
          iss >> thread_count;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return 1;
          }
          if(thread_count <= 0) {
            cerr << "Too small number" << endl;
            return 1;
          }
          break;
        }
        case 's':
          config.searcher_name = string(optarg);
          break;
        case 't':
        {
          string str(optarg);
          istringstream iss(str);
          iss >> config.time;
          if(iss.fail() && !iss.eof()) {
            cerr << "Incorrect number" << endl;
            return 1;
          }
          break;
        }
        case 'T':
          tournament_name = optarg;
          break;
        case 'u':
          can_save_game = false;
          break;
        case 'v':
          can_save_tournament_result = false;
          break;
        case 'w':
          can_save_eval_params = false;
          break;
        default:
          cerr << "Incorrect option" << endl;
          return 1;          
      }
    }
    if(config.best_individual_count + config.child_count > config.individual_count) {
      cerr << "Too small number of all individuals" << endl;
      return 1;
    }
    if(!save_configuration(config)) return 1;
    switch(cmd) {
      case Command::GENETIC_ALGORITHM:
      {
        function<Searcher *(const EvaluationFunction *, int)> searcher_fun;
        auto iter = searcher_functions.find(config.searcher_name);
        if(iter != searcher_functions.end()) {
          searcher_fun = iter->second;
        } else {
          cerr << "Can't find searcher" << endl;
          return 1;
        }
        function<Tournament *(int, function<Table *()>, unsigned)> tournament_fun;
        auto iter2 = tournament_functions.find(string(tournament_name));
        if(iter2 != tournament_functions.end()) {
          tournament_fun = iter2->second;
        } else {
          cerr << "Can't find tournament" << endl;
          return 1;
        }
        uint32_t generator_seed = chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count();
        uint64_t zobrist_seed = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        initialize_genetic_algorithm_signal();
        initialize_tables();
        initialize_zobrist(zobrist_seed);        
        initialize_generator(generator_seed);
        initialize_genetic_algorithm_variables();
        unique_ptr<Tournament> tournament = unique_ptr<Tournament>(tournament_fun(config.individual_count, [searcher_fun, &config, can_save_game]() {
          return new SingleTable(config.max_depth, config.time, searcher_fun, can_save_game);
        }, thread_count));
        unique_ptr<FitnessFunction> fitness_fun(new FitnessFunction(tournament.get()));
        unique_ptr<Selector> selector(new RouletteWheelSelector(fitness_fun.get()));
        return genetic_algorithm(selector.get(), iter_count, config.best_individual_count, config.child_count, config.mutation_count, can_save_tournament_result, can_save_eval_params) ? 0 : 1;
      }
      case Command::DISPLAY_INDIVIDUAL:
      {
        ParentPair parent_pair;
        {
          ostringstream oss;
          oss << iter_count << ".eps";
          ifstream ifs(oss.str());
          if(!ifs.good()) {
            cerr << "Can't open evaluation file" << endl;
            return 1;
          }
          skip_evaluation_parameters(ifs, eval_skipping_count);
          if(ifs.fail()) {
            cerr << "I/O error" << endl;
            return 1;
          }
          read_evaluation_parameters(ifs, &parent_pair, evaluation_parameters);
          if(ifs.fail()) {
            cerr << "I/O error" << endl;
            return 1;
          }
        }
        cout << "Peacock Spider i" << iter_count << "p" << eval_skipping_count << endl;
        cout << endl;
        cout << "Parents:" << endl;
        cout << "  " << parent_pair.first_parent << " " << parent_pair.second_parent << endl;
        if(can_display_eval_params) {
          cout << endl;
          cout << "Evaluation parameters:" << endl;
          for(size_t i = 0; i < MAX_EVALUATION_PARAMETER_COUNT; i++) {
            ostringstream oss2;
            oss2 << evaluation_parameters[i];
            string str = oss2.str();
            cout << "  " << str;
            for(int j = 0; j < 6 - static_cast<int>(str.length()); j++) {
              cout << " ";
            }
            cout << "# " << evaluation_parameter_names[i] << endl;
          }
        }
        return 0;
      }
      case Command::GENERATE_DEFAULT_EVAL_PARAMS_CPP_FILE:
      {
        {
          ostringstream oss;
          oss << iter_count << ".eps";
          ifstream ifs(oss.str());
          if(!ifs.good()) {
            cerr << "Can't open evaluation file" << endl;
            return 1;
          }
          skip_evaluation_parameters(ifs, eval_skipping_count);
          if(ifs.fail()) {
            cerr << "I/O error" << endl;
            return 1;
          }
          read_evaluation_parameters(ifs, nullptr, evaluation_parameters);
          if(ifs.fail()) {
            cerr << "I/O error" << endl;
            return 1;
          }
        }
        {
          ofstream ofs("default_eval_params.cpp");
          if(!ofs.good()) {
            cerr << "Can't open default evaluation file" << endl;
            return 1;
          }
          write_default_evaluation_parameters(ofs, evaluation_parameters);
        }
        return 0;
      }
      default:
        cerr << "Incorrect command" << endl;
        return 1;
    }
  } catch(bad_alloc &e) {
    cerr << "Can't allocate memory" << endl;
    return 1;
  }
}
