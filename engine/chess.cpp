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
#include <cctype>
#include "chess.hpp"

using namespace std;

namespace peacockspider
{
  Square string_to_square(const string &str)
  {
    if(str.length() == 2) {
      Column col = char_to_column(str[0]);
      if(col == -1) return -1;
      Column row = char_to_row(str[1]);
      if(row == -1) return -1;
      return col + (row << 3);
    } else
      return -1;
  }

  string square_to_string(Square squ)
  {
    string str;
    str += column_to_char(squ & 7);
    str += row_to_char(squ >> 3);
    return str;
  }

  Column char_to_column(char c)
  {
    if(c >= 'a' && c <= 'h')
      return c - 'a';
    else
      return -1;
  }

  char column_to_char(Column col)
  { return col + 'a'; }
  
  Row char_to_row(char c)
  {
    if(c >= '1' && c <= '8')
      return c - '1';
    else
      return -1;
  }

  char row_to_char(Row row)
  { return row + '1'; }

  pair<Side, bool> char_to_side_pair(char c)
  {
    switch(c) {
      case 'w':
        return make_pair(Side::WHITE, true);
      case 'b':
        return make_pair(Side::BLACK, true);
      default:
        return make_pair(Side::WHITE, false);
    }
  }

  char side_to_char(Side side)
  {
    switch(side) {
      case Side::WHITE:
        return 'w';
      case Side::BLACK:
        return 'b';
      default:
        return 0;
    }
  }

  pair<Piece, bool> char_to_piece_pair(char c)
  {
    switch(c) {
      case 'P':
        return make_pair(Piece::PAWN, true);
      case 'N':
        return make_pair(Piece::KNIGHT, true);
      case 'B':
        return make_pair(Piece::BISHOP, true);
      case 'R':
        return make_pair(Piece::ROOK, true);
      case 'Q':
        return make_pair(Piece::QUEEN, true);
      case 'K':
        return make_pair(Piece::KING, true);
      default:
        return make_pair(Piece::PAWN, false);
    }
  }

  char piece_to_char(Piece piece)
  {
    switch(piece) {
      case Piece::PAWN:
        return 'P';
      case Piece::KNIGHT:
        return 'N';
      case Piece::BISHOP:
        return 'B';
      case Piece::ROOK:
        return 'R';
      case Piece::QUEEN:
        return 'Q';
      case Piece::KING:
        return 'K';
      default:
        return 0;
    }
  }

  PromotionPiece char_to_promotion_piece(char c)
  {
    switch(c) {
      case 'N':
        return PromotionPiece::KNIGHT;
      case 'B':
        return PromotionPiece::BISHOP;
      case 'R':
        return PromotionPiece::ROOK;
      case 'Q':
        return PromotionPiece::QUEEN;
      default:
        return PromotionPiece::NONE;
    }
  }

  char promotion_piece_to_char(PromotionPiece promotion_piece)
  {
    switch(promotion_piece) {
      case PromotionPiece::NONE:
        return 0;
      case PromotionPiece::KNIGHT:
        return 'N';
      case PromotionPiece::BISHOP:
        return 'B';
      case PromotionPiece::ROOK:
        return 'R';
      case PromotionPiece::QUEEN:
        return 'Q';
      default:
        return 0;
    }
  }
  
  bool is_column_char(char c)
  { return c >= 'a' && c <= 'h'; }
  
  bool is_row_char(char c)
  { return c >= '1' && c <= '8'; }

  size_t repetitions(const Board &board, const vector<Board> &boards)
  {
    size_t count = 0;
    for(size_t i = boards.size(); i > 0; i--) {
      if(board.equal_for_repetitions(boards[i - 1])) count++;
    }
    return count;
  }

  size_t repetitions(const Board &board, const vector<Board> &boards, const Board *last_board)
  {
    size_t count = 0;
    if(last_board != nullptr && board.equal_for_repetitions(*last_board)) count++;
    for(size_t i = boards.size(); i > 0; i--) {
      if(board.equal_for_repetitions(boards[i - 1])) count++;
    }
    return count;
  }

  Result result_for_boards(const vector<Board> &boards, MovePairList &move_pairs)
  {
    if(!boards.empty() && boards.back().in_checkmate(move_pairs)) {
      if(boards.back().side() == Side::WHITE)
        return Result::BLACK_WIN;
      else
        return Result::WHITE_WIN;
    } else if(!boards.empty() && boards.back().in_stalemate(move_pairs)) {
      return Result::DRAW;
    } else if(!boards.empty() && boards.back().halfmove_clock() >= 100) {
      return Result::DRAW;
    } else if(!boards.empty() && repetitions(boards.back(), boards) >= 3) {
      return Result::DRAW;
    } else
      return Result::NONE;
  }

  ostream &operator<<(ostream &os, const PrefixAndBoard &pab)
  {
    for(Row row = 7; row >= 0; row++) {
      os << pab.prefix << "  ";
      for(Column col = 0; col < 8; col++) {
        os << "+---";
      }
      os << "+" << endl;
      os << pab.prefix << row_to_char(row) << " ";
      for(Column col = 0; col < 8; col++) {
        Color color = pab.board.color(col + (row << 3));
        Piece piece = pab.board.piece(col + (row << 3));
        os << "| ";
        switch(color) {
          case Color::WHITE:
            os << static_cast<char>(toupper(piece_to_char(piece)));
            break;
          case Color::BLACK:
            os << static_cast<char>(tolower(piece_to_char(piece)));
            break;
          default:
            os << ' ';
            break;
        }
        os << " ";
      }
      os << "|" << endl;
    }
    os << pab.prefix << "  ";
    for(Column col = 0; col < 8; col++) {
      os << "+---";
    }
    os << "+" << endl;
    os << pab.prefix << "  ";
    for(Column col = 0; col < 8; col++) {
      os << "  " << column_to_char(col) << " ";
    }
    os << endl;
    os << pab.prefix << pab.board.to_string() << endl;
    return os;
  }
}
