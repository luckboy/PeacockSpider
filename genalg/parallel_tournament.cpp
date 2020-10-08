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
#include <iostream>
#include <new>
#include "tournament.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    ParallelTournament::ParallelTournament(int player_count, function<Table *()> fun, unsigned thread_count) :
      Tournament(player_count), _M_has_error(false), _M_iter(0), _M_param_arrays(nullptr)
    {
      for(unsigned i = 0; i < thread_count; i++) {
        _M_threads.push_back(ParallelThread());
        _M_threads.back().table = unique_ptr<Table>(fun());
        _M_threads.back().command = ParallelCommand::NO_COMMAND;
        _M_threads.back().result = ParallelResult::NO_RESULT;        
      }
      for(unsigned i = 0; i < thread_count; i++) {
        _M_threads[i].thread = thread([this, i]() {
          try {
            unique_lock<mutex> lock(_M_threads[i].mutex);
            while(true) {
              while(_M_threads[i].command == ParallelCommand::NO_COMMAND) {
                _M_threads[i].start_condition_variable.wait(lock);
              }
              if(_M_threads[i].command == ParallelCommand::QUIT) break;
              if(_M_threads[i].command == ParallelCommand::PLAY) {
                while(true) {
                  QueueElement elem;
                  {
                    unique_lock<mutex> lock2(_M_mutex);
                    if(_M_queue.empty()) break;
                    elem = _M_queue.front();
                    _M_queue.pop();
                    if(_M_has_error) break;
                  }
                  pair<Result, bool> result_pair;
                  if(elem.match_game_index == 0)
                    result_pair = _M_threads[i].table->play(_M_iter, elem.round, elem.player1, (*_M_param_arrays)[elem.player1].get(), elem.player2, (*_M_param_arrays)[elem.player2].get());
                  else
                    result_pair = _M_threads[i].table->play(_M_iter, elem.round, elem.player2, (*_M_param_arrays)[elem.player2].get(), elem.player1, (*_M_param_arrays)[elem.player1].get());
                  if(!result_pair.second) {
                    unique_lock<mutex> lock2(_M_mutex);
                    _M_has_error = true;
                    break;
                  }
                  {
                    unique_lock<mutex> lock2(_M_mutex);
                    _M_result.set_game_result(elem.player1, elem.player2, elem.match_game_index, result_pair.first);
                  }
                  _M_tournament_output_function(_M_iter, elem.player1, elem.player2, elem.match_game_index, result_pair.first);
                }
              }
              _M_threads[i].command = ParallelCommand::NO_COMMAND;
              _M_threads[i].result = ParallelResult::STOP;
              _M_threads[i].stop_condition_variable.notify_one();
            }
          } catch(bad_alloc &e) {
            cerr << "Can't allocate memory" << endl;
          }
        });
      }
    }
    
    ParallelTournament::~ParallelTournament()
    {
      for(ParallelThread &thread : _M_threads) {
        unique_lock<mutex> lock(thread.mutex);
        thread.command = ParallelCommand::QUIT;
        thread.start_condition_variable.notify_one();
      }
      for(ParallelThread &thread : _M_threads) {
        thread.thread.join();
      }
    }
    
    bool ParallelTournament::play(int iter, const vector<shared_ptr<int []>> &param_arrays)
    {
      if(!_M_threads[0].table->start_tournament(iter)) return false;
      _M_iter = iter;
      _M_param_arrays = &param_arrays;
      _M_result.clear();
      {
        unique_lock<mutex> lock(_M_mutex);
        while(!_M_queue.empty()) {
          _M_queue.pop();
        }
        _M_has_error = false;
        int round = 1;
        for(int player1 = 0; player1 < _M_result.player_count(); player1++) {
          for(int player2 = player1 + 1; player2 < _M_result.player_count(); player2++) {
            for(int match_game_index = 0; match_game_index < 2; match_game_index++) {
              _M_queue.push(QueueElement(round, player1, player2, match_game_index));
              round++;
            }
          }
        }
      }
      for(ParallelThread &thread : _M_threads) {
        unique_lock<mutex> lock(thread.mutex);
        thread.command = ParallelCommand::PLAY;
        thread.start_condition_variable.notify_all();
      }
      for(ParallelThread &thread : _M_threads) {
        unique_lock<mutex> lock(thread.mutex);
        while(thread.result == ParallelResult::NO_RESULT) {
          thread.stop_condition_variable.wait(lock);
        }
        thread.result = ParallelResult::NO_RESULT;
      }
      {
        unique_lock<mutex> lock(_M_mutex);
        if(_M_has_error) return false;
      }
      _M_result.sort_player_indices();
      return true;
    }
  }
}
