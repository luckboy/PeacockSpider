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
#include <csignal>
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
    const char *prompt = "Peacock Spider> ";
    const char *editing_prompt = "Peacock Spider:edit> ";
    
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

    bool is_prompt_newline;
    bool must_write_prompt;

    void print_illegal_move(ostream *ols, const string &move_str)
    {
      unique_lock<mutex> output_lock(output_mutex);
      cout << "Illegal move: " << move_str << endl;
      if(ols != nullptr) {
        *ols << output_prefix;
        *ols << "Illegal move: " << move_str << endl;
        ols->flush();
      }
    }
    
    void print_error(ostream *ols, const string &error_type, const string &cmd_line)
    {
      unique_lock<mutex> output_lock(output_mutex);
      cout << "Error (" << error_type << "): " << cmd_line << endl;
      if(ols != nullptr) {
        *ols << output_prefix;
        *ols << "Error (" << error_type << "): " << cmd_line << endl;
        ols->flush();
      }
    }
    
    pair<bool, bool> editing_loop(const Board &old_board, Board &new_board, bool is_prompt, ostream *ols)
    {
      new_board = old_board;
      Color color = Color::WHITE;
      while(true) {
        string cmd_line;
        if(is_prompt) {
          unique_lock<mutex> output_lock(output_mutex);
          cout << editing_prompt;
          cout.flush();
        }
        getline(cin, cmd_line);
        if(cin.fail()) {
          cerr << "I/O error" << endl;
          return make_pair(false, false);
        }
        if(ols != nullptr) {
          unique_lock<mutex> output_lock(output_mutex);
          *ols << input_prefix;
          *ols << cmd_line << endl;
          ols->flush();
        }
        if(cmd_line.empty()) continue;
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
      int white_piece_count = 0;
      int black_piece_count = 0;
      new_board.set_king_square(Side::WHITE, -1);
      new_board.set_king_square(Side::BLACK, -1);
      for(Square squ = 0; squ < 64; squ++) {
        switch(new_board.color(squ)) {
          case Color::WHITE:
            white_piece_count++;
            if(new_board.piece(squ) == Piece::KING) {
              if(new_board.king_square(Side::WHITE) == -1)
                new_board.set_king_square(Side::WHITE, squ);
              else
                return make_pair(false, true);
            }
            break;
          case Color::BLACK:
            black_piece_count++;
            if(new_board.piece(squ) == Piece::KING) {
              if(new_board.king_square(Side::BLACK) == -1)
                new_board.set_king_square(Side::BLACK, squ);
              else
                return make_pair(false, true);
            }
            break;
          default:
            break;
        }
      }
      if(new_board.king_square(Side::WHITE) == -1) return make_pair(false, true);
      if(new_board.king_square(Side::BLACK) == -1) return make_pair(false, true);
      if(white_piece_count > 16) return make_pair(false, true);
      if(black_piece_count > 16) return make_pair(false, true);
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
      new_board.set_halfmove_clock(0);
      new_board.set_fullmove_number(1);
      new_board.update_hash_key();
      return make_pair(true, true);
    }

    unordered_map<string, function<pair<bool, bool> (Engine *, bool, const string &, ostream *, const string &, MovePairList &)>> analysis_command_map {
      {
        "undo",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->undo(true);
          return make_pair(true, true);
        }
      },
      {
        "new",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_board([](const Board &old_board, Board &new_board) {
            new_board = Board();
            return true;
          }, true);
          return make_pair(true, true);
        }
      },
      {
        "setboard",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          if(!engine->set_board([&arg_str](const Board &old_board, Board &new_board) {
            return new_board.set(arg_str);
          }, true)) print_error(ols, "invalid fen", cmd_line);
          return make_pair(true, true);
        }
      },
      {
        "edit",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          bool is_success = true;
          if(!engine->set_board([is_prompt, ols, &is_success](const Board &old_board, Board &new_board) {
            pair<bool, bool> tmp_pair = editing_loop(old_board, new_board, is_prompt, ols);
            is_success = tmp_pair.second;
            return tmp_pair.first;
          }, true)) {
            if(is_success) print_error(ols, "invalid position", cmd_line);
          }
          return make_pair(is_success, is_success);
        }
      },
      {
        "exit",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return make_pair(false, true);
        }
      },
      {
        ".",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          print_line(ols, "stat01...");
          return make_pair(true, true);
        }
      },
      {
        "bk",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          print_line(ols, "");
          print_line(ols, "");
          return make_pair(true, true);
        }
      },
      {
        "hint",
        [](Engine *engine, bool is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return make_pair(true, true);
        }
      }
    };
    
    bool analysis_loop(Engine *engine, bool is_prompt, ostream *ols, MovePairList &move_pairs)
    {
      while(true) {
        string cmd_line;
        if(is_prompt) {
          unique_lock<mutex> output_lock(output_mutex);
          cout << prompt;
          cout.flush();
          is_prompt_newline = true;
        }
        getline(cin, cmd_line);
        if(cin.fail()) {
          cerr << "I/O error" << endl;
          return false;
        }
        {
          unique_lock<mutex> output_lock(output_mutex);
          is_prompt_newline = false;
          must_write_prompt = false;
        }
        if(ols != nullptr) {
          unique_lock<mutex> output_lock(output_mutex);
          *ols << input_prefix;
          *ols << cmd_line << endl;
          ols->flush();
        }
        string cmd_name, arg_str;
        split_command_line(cmd_line, cmd_name, arg_str);
        if(cmd_name.empty()) continue;
        auto iter = analysis_command_map.find(cmd_line);
        if(iter != analysis_command_map.end()) {
          pair<bool, bool> tmp_pair = (iter->second)(engine, is_prompt, arg_str, ols, cmd_line, move_pairs);
          if(!tmp_pair.first) return tmp_pair.second;
        } else {
          if(!engine->make_move([&cmd_name, &arg_str, &move_pairs](const Board &board, Move &move) {
            if(!arg_str.empty()) return false;
            if(!move.set_can(cmd_name, board, move_pairs)) {
              if(!move.set_san(cmd_name, board, move_pairs)) return false;
            }
            return true;
          }, true)) print_illegal_move(ols, cmd_line);
        }
      }
      return true;
    }
    
    unordered_map<string, function<pair<bool, bool> (Engine *, bool &, const string &, ostream *, const string &, MovePairList &)>> command_map {
      {
        "xboard",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          print_line(ols, "");
          is_prompt = false;
          signal(SIGINT, SIG_IGN);
          signal(SIGTERM, SIG_IGN);
          return make_pair(true, true);
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
            return make_pair(true, true);
          }
          if(version >= 2) {
            for(int i = 0; features[i] != nullptr; i++) {
              print_line(ols, string("feature ") + features[i]);
            }
          }
          return make_pair(true, true);
        }
      },
      {
        "accepted",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return make_pair(true, true);
        }
      },
      {
        "rejected",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return make_pair(true, true);
        }
      },
      {
        "new",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->new_game();
          return make_pair(true, true);
        }
      },
      {
        "quit",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return make_pair(false, true);
        }
      },
      {
        "random",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return make_pair(true, true);
        }
      },
      {
        "force",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_force_mode();
          return make_pair(true, true);
        }
      },
      {
        "go",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->go();
          return make_pair(true, true);
        }
      },
      {
        "playother",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->play_other();
          return make_pair(true, true);
        }
      },
      {
        "white",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_board([](const Board &old_board, Board &new_board) {
            new_board = old_board;
            new_board.set_side(Side::WHITE);
            if(old_board.side() != new_board.side()) new_board.set_en_passant_column(-1);
            new_board.set_halfmove_clock(0);
            new_board.set_fullmove_number(1);
            new_board.update_hash_key();
            return true;
          });
          return make_pair(true, true);
        }
      },
      {
        "black",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_board([](const Board &old_board, Board &new_board) {
            new_board = old_board;
            new_board.set_side(Side::BLACK);
            if(old_board.side() != new_board.side()) new_board.set_en_passant_column(-1);
            new_board.set_halfmove_clock(0);
            new_board.set_fullmove_number(1);
            new_board.update_hash_key();
            return true;
          });
          return make_pair(true, true);
        }
      },
      {
        "level",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          vector<string> args;
          split_argument_string(arg_str, args);
          if(args.size() < 3) {
            print_error(ols, "too few arguments", cmd_line);
            return make_pair(true, true);
          }
          if(args.size() > 3) {
            print_error(ols, "too many arguments", cmd_line);
            return make_pair(true, true);
          }
          istringstream mps_iss(args[0]);
          unsigned mps;
          mps_iss >> mps;
          if(mps_iss.fail() || !mps_iss.eof()) {
            print_error(ols, "incorrect number", cmd_line);
            return make_pair(true, true);
          }
          auto iter = find(args[1].begin(), args[1].end(), ':');
          string base_min_str(args[1].begin(), iter);
          istringstream base_min_iss(base_min_str);
          unsigned base_min;
          base_min_iss >> base_min;
          if(base_min_iss.fail() || !base_min_iss.eof()) {
            print_error(ols, "incorrect number", cmd_line);
            return make_pair(true, true);
          }
          unsigned base_sec = 0;
          if(iter != args[1].end()) {
            string base_sec_str(iter + 1, args[1].end());
            istringstream base_sec_iss(base_sec_str);
            base_sec_iss >> base_sec;
            if(base_min_iss.fail() || !base_min_iss.eof()) {
              print_error(ols, "incorrect number", cmd_line);
              return make_pair(true, true);
            }
          }
          unsigned base = ((base_min * 60) + base_sec) * 1000;
          istringstream inc_iss(args[2]);
          unsigned inc;
          inc_iss >> inc;
          if(inc_iss.fail() || !inc_iss.eof()) {
            print_error(ols, "incorrect number", cmd_line);
            return make_pair(true, true);
          }
          inc *= 1000;
          engine->set_level(mps, base, inc);
          return make_pair(true, true);
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
            return make_pair(true, true);
          }
          time *= 1000;
          engine->set_time(time);
          return make_pair(true, true);
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
            return make_pair(true, true);
          }
          if(depth < 1) depth = 1;
          if(depth > MAX_DEPTH) depth = MAX_DEPTH;
          engine->set_depth(depth);
          return make_pair(true, true);
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
            return make_pair(true, true);
          }
          if(time < 0) time = 0;
          time *= 10;
          engine->set_remaining_engine_time(static_cast<unsigned>(time));
          return make_pair(true, true);
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
            return make_pair(true, true);
          }
          if(time < 0) time = 0;
          time *= 10;
          engine->set_remaining_opponent_time(static_cast<unsigned>(time));
          return make_pair(true, true);
        }
      },
      {
        "?",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->stop_thinking();
          return make_pair(true, true);
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
            return make_pair(true, true);
          }
          unique_lock<mutex> output_lock(output_mutex);
          cout << "pong " << n << endl;
          if(ols != nullptr) {
            *ols << output_prefix;
            *ols << "pong " << n << endl;
            ols->flush();
          }
          return make_pair(true, true);
        }
      },
      {
        "draw",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return make_pair(true, true);
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
            return make_pair(true, true);
          } else
            iter++;
          auto end_iter = arg_str.end();
          if(end_iter == arg_str.begin()) {
            print_error(ols, "invalid result comment", cmd_line);
            return make_pair(true, true);
          }
          end_iter--;
          if(*end_iter != '}') {
            print_error(ols, "invalid result comment", cmd_line);
            return make_pair(true, true);
          }
          string result_comment(iter, end_iter);
          Result result = string_to_result(result_str);
          if(result == Result::NONE) {
            print_error(ols, "invalid result", cmd_line);
            return make_pair(true, true);
          }
          engine->set_result(result, result_comment);
          return make_pair(true, true);
        }
      },
      {
        "setboard",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          if(!engine->set_board([&arg_str](const Board &old_board, Board &new_board) {
            return new_board.set(arg_str);
          })) print_error(ols, "invalid fen", cmd_line);
          return make_pair(true, true);
        }
      },
      {
        "edit",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          bool is_success = true;
          if(!engine->set_board([is_prompt, ols, &is_success](const Board &old_board, Board &new_board) {
            pair<bool, bool> tmp_pair = editing_loop(old_board, new_board, is_prompt, ols);
            is_success = tmp_pair.second;
            return tmp_pair.first;
          })) {
            if(is_success) print_error(ols, "invalid position", cmd_line);
          }
          return make_pair(is_success, is_success);
        }
      },
      {
        "hint",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          Move hint_move;
          if(engine->get_hint_move(hint_move)) print_line(ols, "Hint: " + hint_move.to_can_string());
          return make_pair(true, true);
        }
      },
      {
        "bk",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          print_line(ols, "");
          print_line(ols, "");
          return make_pair(true, true);
        }
      },
      {
        "undo",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->undo();
          return make_pair(true, true);
        }
      },
      {
        "remove",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->remove();
          return make_pair(true, true);
        }
      },
      {
        "hard",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_auto_pondering_flag(true);
          return make_pair(true, true);
        }
      },
      {
        "easy",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_auto_pondering_flag(false);
          return make_pair(true, true);
        }
      },
      {
        "post",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_thinking_output_flag(true);
          return make_pair(true, true);
        }
      },
      {
        "nopost",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->set_thinking_output_flag(false);
          return make_pair(true, true);
        }
      },
      {
        "analyze",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          engine->analyze();
          bool is_success = analysis_loop(engine, is_prompt, ols, move_pairs);
          engine->quit_from_analysis();
          return make_pair(is_success, is_success);
        }
      },
      {
        "name",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return make_pair(true, true);
        }
      },
      {
        "computer",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          return make_pair(true, true);
        }
      },
      {
        "display",
        [](Engine *engine, bool &is_prompt, const string &arg_str, ostream *ols, const string &cmd_line, MovePairList &move_pairs) {
          Board board;
          engine->get_board(board);
          unique_lock<mutex> output_lock(output_mutex);
          cout << board << endl;
          if(ols != nullptr) {
            *ols << prefix_and_board(output_prefix, board) << endl;
            ols->flush();
          }
          return make_pair(true, true);
        }
      }
    };
  }
  
  bool xboard_loop(Engine *engine, ostream *ols, function<pair<bool, bool> (Engine *, const string &, ostream *)> fun)
  {
    unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
    MovePairList move_pairs(tmp_move_pairs.get(), 0);
    unique_ptr<MovePair []> tmp_thread_move_pairs(new MovePair[MAX_MOVE_COUNT]);
    MovePairList thread_move_pairs(tmp_thread_move_pairs.get(), 0);
    OutputFunctionSettings settings(engine,
      [ols, &thread_move_pairs](int depth, int value, unsigned ms, const Searcher *searcher, const Board *pondering_board, const Move *pondering_move) {
        unique_lock<mutex> output_lock(output_mutex);
        if(is_prompt_newline) cout << endl;
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
        if(ols != nullptr) {
          *ols << endl;
          ols->flush();
        }
        if(is_prompt_newline) must_write_prompt = true;
        is_prompt_newline = false;
      },
      [ols](const Board &board, Move move, const Move *pondering_move) {
        unique_lock<mutex> output_lock(output_mutex);
        if(is_prompt_newline) cout << endl;
        unsafely_print_line(ols, string("move ") + move.to_can_string());
        if(is_prompt_newline || must_write_prompt) {
          cout << prompt;
          cout.flush();
          is_prompt_newline = true;
          must_write_prompt = false;
        }
      },
      [ols](Result result, const string &comment) {
        unique_lock<mutex> output_lock(output_mutex);
        if(is_prompt_newline) cout << endl;
        unsafely_print_line(ols, result_to_string(result) + " {" + comment + "}");
        if(is_prompt_newline || must_write_prompt) {
          cout << prompt;
          cout.flush();
          is_prompt_newline = true;
          must_write_prompt = false;
        }
      },
      [ols](const Board &board) {
        if(ols != nullptr) {
          unique_lock<mutex> output_lock(output_mutex);
          *ols << prefix_and_board(board_prefix, board) << endl;
          ols->flush();
        }
      });
    bool is_prompt = true;
    {
      unique_lock<mutex> output_lock(output_mutex);
      is_prompt_newline = false;
      must_write_prompt = false;
    }
    while(true) {
      string cmd_line;
      if(is_prompt) {
        unique_lock<mutex> output_lock(output_mutex);
        cout << prompt;
        cout.flush();
        is_prompt_newline = true;
      }
      getline(cin, cmd_line);
      if(cin.fail()) {
        cerr << "I/O error" << endl;
        return false;
      }
      {
        unique_lock<mutex> output_lock(output_mutex);
        is_prompt_newline = false;
        must_write_prompt = false;
      }
      if(ols != nullptr) {
        unique_lock<mutex> output_lock(output_mutex);
        *ols << input_prefix;
        *ols << cmd_line << endl;
        ols->flush();
      }
      string cmd_name, arg_str;
      split_command_line(cmd_line, cmd_name, arg_str);
      if(cmd_name.empty()) continue;
      auto iter = command_map.find(cmd_name);
      if(iter != command_map.end()) {
        pair<bool, bool> tmp_pair = (iter->second)(engine, is_prompt, arg_str, ols, cmd_line, move_pairs);
        if(!tmp_pair.first) return tmp_pair.second;
      } else {
        pair<bool, bool> tmp_pair = fun(engine, cmd_line, ols);
        if(tmp_pair.first) return tmp_pair.second;
        if(!engine->make_move([&cmd_name, &arg_str, &move_pairs](const Board &board, Move &move) {
          if(!arg_str.empty()) return false;
          if(!move.set_can(cmd_name, board, move_pairs)) {
            if(!move.set_san(cmd_name, board, move_pairs)) return false;
          }
          return true;
        })) print_illegal_move(ols, cmd_line);
      }
    }
    return true;
  }
}
