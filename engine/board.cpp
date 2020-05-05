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
#include "chess.hpp"

using namespace std;

namespace peacockspider
{
  Board::Board()
  {
    _M_color_bitboards[side_to_index(Side::WHITE)] = static_cast<Bitboard>(0xffff) << 0;
    _M_color_bitboards[side_to_index(Side::BLACK)] = static_cast<Bitboard>(0xffff) << (64 - 16);
    _M_piece_bitboards[piece_to_index(Piece::PAWN)] = static_cast<Bitboard>(0xff00) << 0;
    _M_piece_bitboards[piece_to_index(Piece::PAWN)] |= static_cast<Bitboard>(0x00ff) << (64 - 16);
    _M_piece_bitboards[piece_to_index(Piece::KNIGHT)] = static_cast<Bitboard>(0x0042) << 0;
    _M_piece_bitboards[piece_to_index(Piece::KNIGHT)] |= static_cast<Bitboard>(0x4200) << (64 - 16);
    _M_piece_bitboards[piece_to_index(Piece::BISHOP)] = static_cast<Bitboard>(0x0024) << 0;
    _M_piece_bitboards[piece_to_index(Piece::BISHOP)] |= static_cast<Bitboard>(0x2400) << (64 - 16);
    _M_piece_bitboards[piece_to_index(Piece::ROOK)] = static_cast<Bitboard>(0x0081) << 0;
    _M_piece_bitboards[piece_to_index(Piece::ROOK)] |= static_cast<Bitboard>(0x8100) << (64 - 16);
    _M_piece_bitboards[piece_to_index(Piece::QUEEN)] = static_cast<Bitboard>(0x0008) << 0;
    _M_piece_bitboards[piece_to_index(Piece::QUEEN)] |= static_cast<Bitboard>(0x0800) << (64 - 16);
    _M_piece_bitboards[piece_to_index(Piece::KING)] = static_cast<Bitboard>(0x0010) << 0;
    _M_piece_bitboards[piece_to_index(Piece::KING)] |= static_cast<Bitboard>(0x1000) << (64 - 16);
    _M_king_squares[side_to_index(Side::WHITE)] = 004;
    _M_king_squares[side_to_index(Side::BLACK)] = 074;
    _M_side = Side::WHITE;
    _M_castlings[side_to_index(Side::WHITE)] = SideCastlings::SHORT | SideCastlings::LONG;
    _M_castlings[side_to_index(Side::BLACK)] = SideCastlings::SHORT | SideCastlings::LONG;
    _M_en_passant_column = -1;
    _M_halfmove_clock = 0;
    _M_fullmove_number = 1;
  }
  
  bool Board::has_attack(Side side, Square squ) const
  {
    // Not implemented.
    return false;
  }

  void Board::generate_pseudo_legal_moves(MovePairList &move_pairs) const
  {
    // Not implemented.
  }

  void Board::generate_pseudo_legel_good_moves(MovePairList &move_pairs) const
  {
    // Not implemented.
  }

  bool Board::make_move(Move move, Board &board) const
  {
    // Not implemented.
    return false;
  }
}
