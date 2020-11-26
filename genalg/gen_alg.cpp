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
#include <algorithm>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include "eval.hpp"
#include "gen_alg.hpp"
#include "gen_alg_vars.hpp"
#include "tournament.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    namespace
    {
      mutex output_mutex;

      string tournament_result_file_name(int iter)
      {
        ostringstream oss;
        oss << iter << ".txt";
        return oss.str();
      }

      string evaluation_parameter_file_name(int iter)
      {
        ostringstream oss;
        oss << iter << ".eps";
        return oss.str();
      }
    }

    bool genetic_algorithm(Selector *selector, int iter_count, int best_individual_count, int child_count, int mutation_count, bool can_save_tournament_result, bool can_save_eval_params)
    {
      int iter;
      vector<Individual> individuals;
      OutputFunctionSettings settings(selector,
        [](int iter, int player1, int player2, int match_game_index, Result result) {
          unique_lock<mutex> lock(mutex);
          cout << ".";
          cout.flush();
        },
        [can_save_tournament_result](int iter, const TournamentResult &result) {
          cout << endl;
          cout << endl;
          cout << result << endl;
          cout << endl;
          if(can_save_tournament_result) {
            ofstream ofs(tournament_result_file_name(iter));
            if(!ofs.good()) {
              cerr << "Can't open tournament result file" << endl;
              return false;
            }
            ofs << result << endl;
          }
          return true;
        });
      {
        ifstream ifs("iter.txt");
        if(ifs.good()) {
          ifs >> iter;
          if(ifs.fail()) {
            cerr << "I/O error" << endl;
            return false;
          }
        } else {
          iter = 0;
          ofstream ofs("iter.txt");
          if(!ofs.good()) {
            cerr << "Can't open iteration file" << endl;
            return false;
          }
          ofs << iter << endl;
        }
      }
      {
        ifstream ifs(evaluation_parameter_file_name(iter));
        if(ifs.good()) {
          read_individuals(ifs, selector->individual_count(), individuals);
          if(ifs.fail()) {
            cerr << "I/O error" << endl;
            return false;
          }
        } else if(iter == 0) {
          Individual individual(ParentPair(-1, -1), shared_ptr<int []>(new int[max_gene_count]));
          copy(start_evaluation_parameters, start_evaluation_parameters + max_gene_count, individual.genes.get());
          individuals.push_back(individual);
          vector<Individual> generated_individuals;
          generate_individuals(selector->individual_count() - 1, generated_individuals);
          individuals.insert(individuals.end(), generated_individuals.begin(), generated_individuals.end());
          if(can_save_eval_params) {
            ofstream ofs(evaluation_parameter_file_name(iter));
            if(!ofs.good()) {
              cerr << "Can't open evaluation file" << endl;
              return false;
            }
            write_individuals(ofs, individuals);
          }
        } else {
          cerr << "Can't open evaluation file" << endl;
          return false;
        }
      }
      for(; iter < iter_count; iter++) {
        cout << "Iteration: " << iter << endl;
        cout << endl;
        cout << "Playing tournament ..." << endl;
        vector<Individual> new_individuals;
        if(!genetic_algorithm_iterate(selector, iter, individuals, new_individuals, best_individual_count, child_count, mutation_count)) return false;
        individuals = new_individuals;
        if(can_save_eval_params || iter + 1 >= iter_count) {
          ofstream ofs(evaluation_parameter_file_name(iter + 1));
          if(!ofs.good()) {
            cerr << "Can't open evaluation file" << endl;
            return false;
          }
          write_individuals(ofs, individuals);
        }
        ofstream ofs("iter.txt");
        if(!ofs.good()) {
          cerr << "Can't open iteration file" << endl;
          return false;
        }
        ofs << (iter + 1) << endl;
      }
      return true;
    }
  }
}
