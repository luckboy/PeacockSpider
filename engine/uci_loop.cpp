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
#include <sstream>
#include <string>
#include <unordered_map>
#include "protocols.hpp"

using namespace std;

namespace peacockspider
{
  namespace
  {
    void print_for_uci_command(ostream *ols)
    {
      print_line(ols, "");
      print_line(ols, "id name Peacock Spider");
      print_line(ols, "id author Lukasz Szpakowski");
      print_line(ols, "uciok");
    }

    unordered_map<string, function<bool (Engine *, const vector<string> &, ostream *, MovePairList &)>> command_map {
      {
        "uci",
        [](Engine *engine, const vector<string> &args, ostream *ols, MovePairList &move_pairs) {
          print_for_uci_command(ols);
          return true;
        }
      },
      {
        "debug",
        [](Engine *engine, const vector<string> &args, ostream *ols, MovePairList &move_pairs) {
          return true;
        }
      },
      {
        "isready",
        [](Engine *engine, const vector<string> &args, ostream *ols, MovePairList &move_pairs) {
          print_line(ols, "readyok");
          return true;
        }
      },
      {
        "setoption",
        [](Engine *engine, const vector<string> &args, ostream *ols, MovePairList &move_pairs) {
          return true;
        }
      },
      {
        "ucinewgame",
        [](Engine *engine, const vector<string> &args, ostream *ols, MovePairList &move_pairs) {
          engine->new_game();
          return true;
        }
      },
      {
        "position",
        [](Engine *engine, const vector<string> &args, ostream *ols, MovePairList &move_pairs) {
          engine->set_board_and_make_moves([&args, &move_pairs](const Board &old_board, Board &new_board, vector<Move> &moves) {
            size_t i = 0;
            moves.clear();
            if(args.size() - i >= 1 && args[i] == "startpos") {
              new_board = Board();
              i++;
            } else if(args.size() - i >= 7 && args[i] == "fen") {
              string fen;
              for(size_t j = 0; j < 6; j++) {
                fen += args[i + j + 1];
                if(j + 1 < 6) fen += " ";
              }
              if(!new_board.set(fen)) return false;
              i += 7;
            } else
              return false;
            if(args.size() - i >= 1 && args[i] == "moves") {
              Board tmp_board = new_board;
              for(size_t j = 0; j < args.size() - i - 1; j++) {
                Board new_tmp_board;
                Move move;
                if(!move.set_can(args[i + j + 1], tmp_board, move_pairs)) return false;
                if(!tmp_board.make_move(move, new_tmp_board)) return false;
                tmp_board = new_tmp_board;
                moves.push_back(move);
              }
            }
            return true;
          });
          return true;
        }
      },
      {
        "go",
        [](Engine *engine, const vector<string> &args, ostream *ols, MovePairList &move_pairs) {
          vector<Move> tmp_moves;
          vector<Move> *search_moves = nullptr;
          unsigned white_time = numeric_limits<unsigned>::max();
          unsigned black_time = numeric_limits<unsigned>::max();
          unsigned moves_to_go = numeric_limits<unsigned>::max();
          int depth = MAX_DEPTH;
          uint64_t nodes = numeric_limits<uint64_t>::max();
          int checkmate_move_count = 0;
          unsigned move_time = numeric_limits<unsigned>::max();
          bool is_infinite = false;
          bool is_pondering = false;
          for(size_t i = 0; i < args.size(); i++) {
            if(args.size() - i >= 1 && args[i] == "searchmoves") {
              if(engine->get_board_for_search_moves([&i, &args, &tmp_moves, &move_pairs](const Board &board) {
                size_t j;
                tmp_moves.clear();
                for(j = 0; j < args.size() - i - 1; j++) {
                  Move move;
                  if(!move.set_can(args[i + j + 1], board, move_pairs)) break;
                  tmp_moves.push_back(move);
                }
                i += j;
                return true;
              })) search_moves = &tmp_moves;
            } else if(args.size() - i >= 1 && args[i] == "ponder") {
              is_pondering = true;
            } else if(args.size() - i >= 2 && args[i] == "wtime") {
              int tmp;
              istringstream iss(args[i + 1]);
              iss >> tmp;
              if(tmp < 0) tmp = 0;
              white_time =  static_cast<unsigned>(tmp);
              i++;
            } else if(args.size() - i >= 2 && args[i] == "btime") {
              int tmp;
              istringstream iss(args[i + 1]);
              iss >> tmp;
              if(tmp < 0) tmp = 0;
              black_time =  static_cast<unsigned>(tmp);
              i++;
            } else if(args.size() - i >= 2 && args[i] == "winc") {
              i++;
            } else if(args.size() - i >= 2 && args[i] == "binc") {
            } else if(args.size() - i >= 2 && args[i] == "movestogo") {
              istringstream iss(args[i + 1]);
              iss >> moves_to_go;
              i++;
            } else if(args.size() - i >= 2 && args[i] == "depth") {
              istringstream iss(args[i + 1]);
              iss >> depth;
              if(depth < 1) depth = 1;
              if(depth > MAX_DEPTH) depth = MAX_DEPTH;
              i++;
            } else if(args.size() - i >= 2 && args[i] == "nodes") {
              istringstream iss(args[i + 1]);
              iss >> nodes;
              i++;
            } else if(args.size() - i >= 2 && args[i] == "mate") {
              istringstream iss(args[i + 1]);
              iss >> checkmate_move_count;
              if(checkmate_move_count < 0) checkmate_move_count = 0;
              i++;
            } else if(args.size() - i >= 2 && args[i] == "movetime") {
              istringstream iss(args[i + 1]);
              iss >> move_time;
              i++;
            } else if(args.size() - i >= 1 && args[i] == "infinite") {
              is_infinite = true;
            }
          }
          engine->go(search_moves, white_time, black_time, moves_to_go, depth, nodes, checkmate_move_count, move_time, is_infinite, is_pondering);
          return true;
        }
      },
      {
        "stop",
        [](Engine *engine, const vector<string> &args, ostream *ols, MovePairList &move_pairs) {
          engine->stop_thinking();
          return true;
        }
      },
      {
        "ponderhit",
        [](Engine *engine, const vector<string> &args, ostream *ols, MovePairList &move_pairs) {
          engine->pondering_hit();
          return true;
        }
      },
      {
        "quit",
        [](Engine *engine, const vector<string> &args, ostream *ols, MovePairList &move_pairs) {
          return false;
        }
      }
    };
  }

  pair<bool, bool> uci_loop(Engine *engine, const string &first_cmd_line, ostream *ols)
  {
    string first_cmd_name, first_arg_str;
    split_command_line(first_cmd_line, first_cmd_name, first_arg_str);
    if(first_cmd_name == "uci") {
      print_for_uci_command(ols);
    } else
      return make_pair(false, true);
    engine->stop_thinking();
    engine->stop_pondering();
    engine->set_thinking_output_flag(true);
    engine->set_auto_pondering_flag(false);
    engine->set_auto_move_making_flag(false);
    unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
    MovePairList move_pairs(tmp_move_pairs.get(), 0);
    OutputFunctionSettings settings(engine,
      [ols](int depth, int value, unsigned ms, const Searcher *searcher, const Board *pondering_board, const Move *pondering_move) {
        unique_lock<mutex> output_lock(output_mutex);
        int selective_depth = depth + MAX_QUIESCENCE_DEPTH;
        int64_t nps = searcher->nodes() * 1000 / (ms > 0 ? ms : 1);
        cout << "info depth " << depth << " seldepth " << selective_depth;
        if(ols != nullptr) {
          *ols << output_prefix;
          *ols << "info depth " << depth << " seldepth " << selective_depth;
        }
        cout << " score cp " << value;
        if(ols != nullptr) *ols << " score cp " << value;
        cout << " time " << ms;
        if(ols != nullptr) *ols << " time " << ms;
        cout << " nodes " << searcher->nodes();
        if(ols != nullptr) *ols << " nodes " << searcher->nodes();
        cout << " nps " << nps;
        if(ols != nullptr) *ols << " nps " << nps;
        cout << " pv";
        if(ols != nullptr) *ols << " pv";
        for(size_t i = 0; i < searcher->pv_line().length(); i++) {
          string move_str = searcher->pv_line()[i].to_can_string();
          cout << " " << move_str;
          if(ols != nullptr) *ols << " " << move_str;
        }
        cout << endl;
        if(ols != nullptr) *ols << endl;
      },
      [ols](const Board &board, Move move, const Move *pondering_move) {
        unique_lock<mutex> output_lock(output_mutex);
        string move_str = move.to_can_string();
        cout << "bestmove " << move_str;
        if(ols != nullptr) {
          *ols << output_prefix;
          *ols << "bestmove " << move_str;
        }
        if(pondering_move != nullptr) {
          string pondering_move_str = pondering_move->to_can_string();
          cout << " ponder " << pondering_move_str;
          if(ols != nullptr) *ols << " ponder " << pondering_move_str;
        }
        cout << endl;
        if(ols != nullptr) *ols << endl;
      },
      [](Result result, const string &comment) {},
      [ols](const Board &board) {
        if(ols != nullptr) {
          unique_lock<mutex> output_lock(output_mutex);
          *ols << prefix_and_board(board_prefix, board) << endl;
        }
      });
    while(true) {
      string cmd_line;
      getline(cin, cmd_line);
      if(cin.fail()) {
        cerr << "I/O error" << endl;
        return make_pair(true, false);
      }
      if(ols != nullptr) {
        unique_lock<mutex> output_lock(output_mutex);
        *ols << input_prefix;
        *ols << cmd_line << endl;
      }
      string cmd_name, arg_str;
      split_command_line(cmd_line, cmd_name, arg_str);
      if(cmd_name.empty()) continue;
      auto iter = command_map.find(cmd_name);
      if(iter != command_map.end()) {
        vector<string> args;
        split_argument_string(arg_str, args);
        if(!(iter->second)(engine, args, ols, move_pairs)) break;
      } else
        print_line(ols, string("Unknown command: ") + cmd_line);
    }
    return make_pair(true, true);
  }
}
