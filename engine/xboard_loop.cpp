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
    const char *input_prefix = "input: ";
    const char *output_prefix = "output: ";
    const char *board_prefix = "board: ";

    const char *prompt = "Peacock Spider> ";
    const char *edit_prompt = "Peacock Spider:edit>";
    
    const char *features[] = {
      "ping=1",
      "setboard=1",
      "playother=1",
      "time=1",
      "draw=0",
      "sigint=0",
      "sigterm=0",
      "reuse=1",
      "analyze=1",
      "myname=\"Peacock Spider\"",
      "veriants=\"normal\"",
      "colors=0",
      "name=1",
      "done=1",
      nullptr
    };

    void print_line(ostream *ols, const string &str)
    {
      unique_lock<mutex> output_lock(output_mutex);
      cout << str << endl;
      if(ols != nullptr) {
        *ols << output_prefix;
        *ols << str << endl;
      }
    }

    void print_illegal_move(ostream *ols, const string &move_str)
    {
      unique_lock<mutex> output_lock(output_mutex);
      cout << "Illegal move: " << move_str << endl;
      if(ols != nullptr) {
        *ols << output_prefix;
        *ols << "Illegal move: " << move_str << endl;
      }
    }
    
    void print_error(ostream *ols, const string &error_type, const string &cmd_line)
    {
      unique_lock<mutex> output_lock(output_mutex);
      cout << "Error (" << error_type << "): " << cmd_line << endl;
      if(ols != nullptr) {
        *ols << output_prefix;
        *ols << "Error (" << error_type << "): " << cmd_line << endl;
      }
    }
    
    bool editor_loop(const Board &old_board, Board &new_board, bool is_prompt, ostream *ols)
    {
      new_board = old_board;
      Color color = Color::WHITE;
      while(true) {
        string cmd_line;
        if(is_prompt) {
          unique_lock<mutex> output_lock(output_mutex);
          cout << edit_prompt;
          cout.flush();
        }
        getline(cin, cmd_line);
        if(cin.fail()) {
          cerr << "I/O error" << endl;
          break;
        }
        if(ols != nullptr) {
          unique_lock<mutex> output_lock(output_mutex);
          *ols << input_prefix;
          *ols << cmd_line << endl;
        }
        if(cmd_line == ".") break;
        if(cmd_line == "c") {
          color = (color == Color::WHITE ? Color::BLACK : Color::WHITE);
        } else if(cmd_line == "#") {
          for(Square squ = 0; squ < 64; squ++) {
            new_board.set_color(squ, Color::EMPTY);
            new_board.unset_piece(squ);
          }
          new_board.set_side_castlings(Side::WHITE, SideCastlings::NONE);
          new_board.set_side_castlings(Side::BLACK, SideCastlings::NONE);
          new_board.set_en_passant_column(-1);
        } else if(!cmd_line.empty() && cmd_line[0] == 'x') {
          Square squ = string_to_square(string(cmd_line.begin() + 1, cmd_line.end()));
          if(squ != -1) {
            new_board.set_color(squ, Color::EMPTY);
            new_board.unset_piece(squ);
          } else
            print_error(ols, "invalid square", cmd_line);
        } else if(!cmd_line.empty()) {
          pair<Piece, bool> piece_pair = char_to_piece_pair(cmd_line[0]);
          if(piece_pair.second) {
            Square squ = string_to_square(string(cmd_line.begin() + 1, cmd_line.end()));
            if(squ != -1) {
              new_board.set_color(squ, color);
              new_board.set_piece(squ, piece_pair.first);
            } else
              print_error(ols, "invalid square", cmd_line);
          } else
            print_error(ols, "invalid piece", cmd_line);
        }
      }
      new_board.set_king_square(Side::WHITE, -1);
      new_board.set_king_square(Side::BLACK, -1);
      for(Square squ = 0; squ < 64; squ++) {
        switch(new_board.color(squ)) {
          case Color::WHITE:
            if(new_board.piece(squ) == Piece::KING) {
              if(new_board.king_square(Side::WHITE) == -1)
                new_board.set_king_square(Side::WHITE, squ);
              else
                return false;
            }
            break;
          case Color::BLACK:
            if(new_board.piece(squ) == Piece::KING) {
              if(new_board.king_square(Side::BLACK) == -1)
                new_board.set_king_square(Side::BLACK, squ);
              else
                return false;
            }
            break;
          default:
            break;
        }
      }
      if(!new_board.has_color_piece(Side::WHITE, Piece::KING, E1)) {
        new_board.set_side_castlings(Side::WHITE, SideCastlings::NONE);
      }
      if(!new_board.has_color_piece(Side::WHITE, Piece::ROOK, H1)) {
        new_board.set_side_castlings(Side::WHITE, new_board.side_castlings(Side::WHITE) & ~SideCastlings::SHORT);
      }
      if(!new_board.has_color_piece(Side::WHITE, Piece::ROOK, A1)) {
        new_board.set_side_castlings(Side::WHITE, new_board.side_castlings(Side::WHITE) & ~SideCastlings::LONG);
      }
      if(!new_board.has_color_piece(Side::BLACK, Piece::KING, E8)) {
        new_board.set_side_castlings(Side::BLACK, SideCastlings::NONE);
      }
      if(!new_board.has_color_piece(Side::BLACK, Piece::ROOK, H8)) {
        new_board.set_side_castlings(Side::BLACK, new_board.side_castlings(Side::BLACK) & ~SideCastlings::SHORT);
      }
      if(!new_board.has_color_piece(Side::BLACK, Piece::ROOK, A8)) {
        new_board.set_side_castlings(Side::BLACK, new_board.side_castlings(Side::BLACK) & ~SideCastlings::LONG);
      }
      if(new_board.en_passant_column() != -1) {
        Square en_passant_squ = new_board.en_passant_column() + (new_board.side() == Side::WHITE ? 050 : 020);
        if(!new_board.has_empty(en_passant_squ)) new_board.set_en_passant_column(-1);
        Square cap_squ = en_passant_squ + (new_board.side() == Side::WHITE ? -8 : 8);
        if(!new_board.has_color_piece(new_board.side(), Piece::PAWN, cap_squ)) new_board.set_en_passant_column(-1);
        if((new_board.color_bitboard(new_board.side()) & new_board.piece_bitboard(Piece::PAWN) & tab_pawn_capture_bitboards[side_to_index(~new_board.side())][en_passant_squ]) == 0)
          new_board.set_en_passant_column(-1);
      }
      return true;
    }

    unordered_map<string, function<bool (Engine *, bool, const string &, ostream *, const string &, MovePairList &)>> analysis_command_map {
      {
        "undo",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->undo(true);
          return true;
        }
      },
      {
        "new",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_board([](const Board &old_board, Board &new_board) {
            new_board = Board();
            return true;
          }, true);
          return true;
        }
      },
      {
        "setboard",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          if(!engine->set_board([&arg_str](const Board &old_board, Board &new_board) {
            return new_board.set(arg_str);
          }, true)) print_error(ols, "invalid fen", cmd_line);
          return true;
        }
      },
      {
        "edit",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          if(!engine->set_board([is_prompt, ols](const Board &old_board, Board &new_board) {
            return editor_loop(old_board, new_board, is_prompt, ols);
          }, true)) print_error(ols, "invalid position", cmd_line);
          return true;
        }
      },
      {
        "exit",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return false;
        }
      },
      {
        ".",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          print_line(ols, "stat01...");
          return true;
        }
      },
      {
        "bk",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          print_line(ols, "");
          print_line(ols, "");
          return true;
        }
      },
      {
        "hint",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return true;
        }
      }
    };
    
    void analysis_loop(Engine *engine, bool is_prompt, ostream *ols, MovePairList &move_pairs)
    {
      while(true) {
        string cmd_line;
        if(is_prompt) {
          unique_lock<mutex> output_lock(output_mutex);
          cout << edit_prompt;
          cout.flush();
        }
        getline(cin, cmd_line);
        if(cin.fail()) {
          cerr << "I/O error" << endl;
          break;
        }
        if(ols != nullptr) {
          unique_lock<mutex> output_lock(output_mutex);
          *ols << input_prefix;
          *ols << cmd_line << endl;
        }
        string cmd_name, arg_str;
        split_command_line(cmd_line, cmd_name, arg_str);
        auto iter = analysis_command_map.find(cmd_line);
        if(iter != analysis_command_map.end()) {
          if(!(iter->second)(engine, is_prompt, arg_str, ols, cmd_line, move_pairs)) break;
        } else {
          if(!engine->make_move([&cmd_line, &move_pairs](const Board &board, Move &move) {
            if(!move.set_can(cmd_line, board, move_pairs)) {
              if(!move.set_san(cmd_line, board, move_pairs)) return false;
            }
            return true;
          }, true)) print_illegal_move(ols, cmd_line);
        }
      }
    }
    
    unordered_map<string, function<bool (Engine *, bool &, const string &, ostream *, const string &, MovePairList &)>> command_map {
      {
        "xboard",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          print_line(ols, "");
          is_prompt = false;
          return true;
        }
      },
      {
        "protover",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          istringstream iss(arg_str);
          int version;
          iss >> version;
          if(iss.fail() || !iss.eof()) {
            print_error(ols, "incorrect number", cmd_line);
            return true;
          }
          if(version >= 2) {
            for(int i = 0; features[i] != nullptr; i++) {
              print_line(ols, features[i]);
            }
          }
          return true;
        }
      },
      {
        "accepted",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return true;
        }
      },
      {
        "rejected",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return true;
        }
      },
      {
        "new",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->new_game();
          return true;
        }
      },
      {
        "quit",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return false;
        }
      },
      {
        "random",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return true;
        }
      },
      {
        "force",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_force_mode();
          return true;
        }
      },
      {
        "go",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->go();
          return true;
        }
      },
      {
        "playother",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->play_other();
          return true;
        }
      },
      {
        "white",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_board([](const Board &old_board, Board &new_board) {
            new_board = old_board;
            new_board.set_side(Side::WHITE);
            if(old_board.side() != new_board.side()) new_board.set_en_passant_column(-1);
            return true;
          });
          return true;
        }
      },
      {
        "black",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_board([](const Board &old_board, Board &new_board) {
            new_board = old_board;
            new_board.set_side(Side::BLACK);
            if(old_board.side() != new_board.side()) new_board.set_en_passant_column(-1);
            return true;
          });
          return true;
        }
      },
      {
        "level",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          vector<string> args;
          split_argument_string(arg_str, args);
          if(args.size() < 3) {
            print_error(ols, "too few arguments", cmd_line);
            return true;
          }
          if(args.size() > 3) {
            print_error(ols, "too many arguments", cmd_line);
            return true;
          }
          istringstream mps_iss(args[0]);
          unsigned mps;
          mps_iss >> mps;
          if(mps_iss.fail() || !mps_iss.eof()) {
            print_error(ols, "incorrect number", cmd_line);
            return true;
          }
          auto iter = find(args[1].begin(), args[1].end(), ':');
          string base_min_str(args[1].begin(), iter);
          istringstream base_min_iss(base_min_str);
          unsigned base_min;
          base_min_iss >> base_min;
          if(base_min_iss.fail() || !base_min_iss.eof()) {
            print_error(ols, "incorrect number", cmd_line);
            return true;
          }
          unsigned base_sec = 0;
          if(iter != args[1].end()) {
            string base_sec_str(iter + 1, args[1].end());
            istringstream base_sec_iss(base_sec_str);
            base_sec_iss >> base_sec;
            if(base_min_iss.fail() || !base_min_iss.eof()) {
              print_error(ols, "incorrect number", cmd_line);
              return true;
            }
          }
          unsigned base = ((base_min * 60) + base_sec) * 1000;
          istringstream inc_iss(args[2]);
          unsigned inc;
          inc_iss >> inc;
          if(inc_iss.fail() || !inc_iss.eof()) {
            print_error(ols, "incorrect number", cmd_line);
            return true;
          }
          inc *= 1000;
          engine->set_level(mps, base, inc);
          return true;
        }
      },
      {
        "st",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          istringstream iss(arg_str);
          unsigned time;
          iss >> time;
          if(iss.fail() || !iss.eof()) {
            print_error(ols, "incorrect number", cmd_line);
            return true;
          }
          time *= 1000;
          engine->set_time(time);
          return true;
        }
      },
      {
        "sd",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          istringstream iss(arg_str);
          int depth;
          iss >> depth;
          if(iss.fail() || !iss.eof()) {
            print_error(ols, "incorrect number", cmd_line);
            return true;
          }
          if(depth < 1) depth = 1;
          if(depth > MAX_DEPTH) depth = MAX_DEPTH;
          engine->set_depth(depth);
          return true;
        }
      },
      {
        "time",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          istringstream iss(arg_str);
          int time;
          iss >> time;
          if(iss.fail() || !iss.eof()) {
            print_error(ols, "incorrect number", cmd_line);
            return true;
          }
          if(time < 0) time = 0;
          time *= 10;
          engine->set_remaining_engine_time(static_cast<unsigned>(time));
          return true;
        }
      },
      {
        "otim",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          istringstream iss(arg_str);
          int time;
          iss >> time;
          if(iss.fail() || !iss.eof()) {
            print_error(ols, "incorrect number", cmd_line);
            return true;
          }
          if(time < 0) time = 0;
          time *= 10;
          engine->set_remaining_opponent_time(static_cast<unsigned>(time));
          return true;
        }
      },
      {
        "?",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->stop_thinking();
          return true;
        }
      },
      {
        "ping",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          istringstream iss(arg_str);
          unsigned n;
          iss >> n;
          if(iss.fail() || !iss.eof()) {
            print_error(ols, "incorrect number", cmd_line);
            return true;
          }
          unique_lock<mutex> output_lock(output_mutex);
          cout << "pong " << n << endl;
          if(ols != nullptr) {
            *ols << output_prefix;
            *ols << "pong " << n << endl;
          }
          return true;
        }
      },
      {
        "draw",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return true;
        }
      },
      {
        "result",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          auto iter = arg_str.begin();
          auto result_iter = iter;
          while(iter != arg_str.end() && *iter != ' ' && *iter != '\t') iter++;
          string result_str(result_iter, iter);
          while(iter != arg_str.end() && (*iter == ' ' || *iter == '\t')) iter++;
          if(iter == arg_str.end() || *iter != '{') {
            print_error(ols, "invalid result comment", cmd_line);
            return true;
          } else
            iter++;
          auto end_iter = arg_str.end();
          if(end_iter == arg_str.begin()) {
            print_error(ols, "invalid result comment", cmd_line);
            return true;
          }
          end_iter--;
          if(*end_iter != '}') {
            print_error(ols, "invalid result comment", cmd_line);
            return true;
          }
          string result_comment(iter, end_iter);
          Result result = string_to_result(result_str);
          if(result == Result::NONE) {
            print_error(ols, "invalid result", cmd_line);
            return true;
          }
          engine->set_result(result, result_comment);
          return true;
        }
      },
      {
        "setboard",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          if(!engine->set_board([&arg_str](const Board &old_board, Board &new_board) {
            return new_board.set(arg_str);
          })) print_error(ols, "invalid fen", cmd_line);
          return true;
        }
      },
      {
        "edit",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          if(!engine->set_board([is_prompt, ols](const Board &old_board, Board &new_board) {
            return editor_loop(old_board, new_board, is_prompt, ols);
          })) print_error(ols, "invalid position", cmd_line);
          return true;
        }
      },
      {
        "hint",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          Move hint_move;
          if(engine->get_hint_move(hint_move)) print_line(ols, "Hint: " + hint_move.to_can_string());
          return true;
        }
      },
      {
        "bk",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          print_line(ols, "");
          print_line(ols, "");
          return true;
        }
      },
      {
        "undo",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->undo();
          return true;
        }
      },
      {
        "remove",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->remove();
          return true;
        }
      },
      {
        "hard",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_auto_pondering_flag(true);
          return true;
        }
      },
      {
        "easy",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_auto_pondering_flag(false);
          return true;
        }
      },
      {
        "post",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_thinking_output_flag(true);
          return true;
        }
      },
      {
        "nopost",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_thinking_output_flag(false);
          return true;
        }
      },
      {
        "analyze",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->analyze();
          analysis_loop(engine, is_prompt, ols, move_pairs);
          engine->quit_from_analysis();
          return true;
        }
      },
      {
        "name",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return true;
        }
      },
      {
        "computer",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return true;
        }
      },
      {
        "display",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          Board board;
          engine->get_board(board);
          unique_lock<mutex> output_lock(output_mutex);
          cout << board << endl;
          if(ols != nullptr) *ols << prefix_and_board(output_prefix, board) << endl;
          return true;
        }
      }
    };
  }
  
  void xboard_loop(Engine *engine, ostream *ols, function<bool (Engine *, const string &, ostream *)> fun)
  {
    unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
    MovePairList move_pairs;
    unique_ptr<MovePair []> tmp_thread_move_pairs(new MovePair[MAX_MOVE_COUNT]);
    MovePairList thread_move_pairs;
    OutputFunctionSettings settings(engine,
      [ols, &thread_move_pairs](int depth, int value, unsigned ms, const Searcher *searcher, const Board *pondering_board, const Move *pondering_move) {
        unique_lock<mutex> output_lock(output_mutex);
        cout << depth << " " << value << " " << ((ms + 9) / 10) << " " << searcher->nodes();
        if(ols != nullptr) {
          *ols << output_prefix;
          *ols << depth << " " << value << " " << ((ms + 9) / 10) << " " << searcher->nodes();
        }
        if(pondering_board != nullptr && pondering_move != nullptr) {
          cout << " (";
          if(ols != nullptr) *ols << " (";
          string move_str = pondering_move->to_san_string(*pondering_board, thread_move_pairs);
          cout << move_str;
          if(ols != nullptr) *ols << move_str;
          cout << ")";
          if(ols != nullptr) *ols << ")";
        }
        Board board = searcher->board();
        for(size_t i = 0; i < searcher->pv_line().length(); i++) {
          Board new_board;
          cout << " ";
          if(ols != nullptr) *ols << " ";
          string move_str = searcher->pv_line()[i].to_san_string(board, thread_move_pairs);
          cout << move_str;
          if(ols != nullptr) *ols << move_str;
          if(!board.make_move(searcher->pv_line()[i], new_board)) break;
          board = new_board;
        }
        cout << endl;
        if(ols != nullptr) *ols << endl;
      },
      [ols](const Board &board, Move move, const Move *pondering_move) {
        print_line(ols, string("move ") + move.to_can_string());
      },
      [ols](Result result, const string &comment) {
        print_line(ols, result_to_string(result) + " {" + comment + "}");
      },
      [ols](const Board &board) {
        if(ols != nullptr) {
          unique_lock<mutex> output_lock(output_mutex);
          *ols << prefix_and_board(board_prefix, board) << endl;
        }
      });
    bool is_prompt = true;
    while(true) {
      string cmd_line;
      if(prompt) {
        unique_lock<mutex> output_lock(output_mutex);
        cout << prompt;
        cout.flush();
      }
      getline(cin, cmd_line);
      if(cin.fail()) {
        cerr << "I/O error" << endl;
        break;
      }
      if(ols != nullptr) {
        unique_lock<mutex> output_lock(output_mutex);
        *ols << input_prefix;
        *ols << cmd_line << endl;
      }
      string cmd_name, arg_str;
      split_command_line(cmd_line, cmd_name, arg_str);
      auto iter = command_map.find(cmd_line);
      if(iter != command_map.end()) {
        if(!(iter->second)(engine, is_prompt, arg_str, ols, cmd_line, move_pairs)) break;
      } else {
        if(fun(engine, cmd_name, ols)) break;
        if(!engine->make_move([&cmd_line, &move_pairs](const Board &board, Move &move) {
          if(!move.set_can(cmd_line, board, move_pairs)) {
            if(!move.set_san(cmd_line, board, move_pairs)) return false;
          }
          return true;
        })) print_illegal_move(ols, cmd_line);
      }
    }
  }
}
