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
#include <ios>
#include <sstream>
#include "consts.hpp"
#include "game.hpp"

using namespace std;

namespace peacockspider
{
  ostream &write_pgn(ostream &os, const Game &game)
  {
    os << "[Event \"" << game.event() << "\"]\n";
    os << "[Site \"" << game.site() << "\"]\n";
    os << "[Date \"" << game.date() << "\"]\n";
    os << "[Round \"" << game.round() << "\"]\n";
    os << "[White \"" << game.white() << "\"]\n";
    os << "[Black \"" << game.black() << "\"]\n";
    os << "[Result \"" <<  result_to_string(game.result()) << "\"]\n";
    if(game.board() != nullptr)
      os << "[FEN \"" << game.board()->to_string() << "\"]\n";
    os << "\n";
    unique_ptr<MovePair []> tmp_move_pairs(new MovePair[MAX_MOVE_COUNT]);
    MovePairList move_pairs(tmp_move_pairs.get(), 0);
    Board board;
    if(game.board() != nullptr) board = *(game.board());
    size_t column = 0;
    bool is_first = true;
    bool is_first_line_char = true;
    for(Move move : game.moves()) {
      Board tmp_board;
      board.generate_pseudolegal_moves(move_pairs);
      if(!move_pairs.contain_move(move)) {
        os.setstate(ios::failbit);
        return os;
      }
      if(!board.make_move(move, tmp_board)) {
        os.setstate(ios::failbit);
        return os;
      }
      string move_str = move.to_san_string(board, move_pairs);
      string fullmove_number_str;
      if(board.side() == Side::WHITE) {
        ostringstream oss;
        oss << board.fullmove_number();
        fullmove_number_str = oss.str() + ".";
      }
      if(board.side() == Side::BLACK && is_first) {
        ostringstream oss;
        oss << board.fullmove_number();
        fullmove_number_str = oss.str() + "...";
      }
      if(!fullmove_number_str.empty()) {
        if(is_first_line_char || column + fullmove_number_str.length() + 1 <= 80) {
          if(!is_first_line_char) os << " ";
          column += fullmove_number_str.length() + (!is_first_line_char ? 1 : 0);
          is_first_line_char = false;
        } else {
          os << '\n';
          column = fullmove_number_str.length();
        }
        os << fullmove_number_str;
      }
      if(is_first_line_char || column + move_str.length() + 1 <= 80) {
        if(!is_first_line_char) os << " ";
        column += move_str.length() + (!is_first_line_char ? 1 : 0);
        is_first_line_char = false;
      } else {
        os << '\n';
        column = move_str.length();
      }
      os << move_str;
      board = tmp_board;
      is_first = false;
    }
    string result_str = result_to_string(game.result());
    if(is_first_line_char || column + result_str.length() + 1 <= 80) {
      if(!is_first_line_char) os << " ";
      column += result_str.length() + (!is_first_line_char ? 1 : 0);
      is_first_line_char = false;
    } else {
      os << '\n';
      column = result_str.length();
    }
    os << result_str << '\n';
    os << '\n';
    return os;
  }
}
