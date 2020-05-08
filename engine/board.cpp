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
#include "tables.hpp"

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
  
  bool Board::equal_for_repetitions(const Board &board) const
  {
    return _M_color_bitboards[side_to_index(Side::WHITE)] == board._M_color_bitboards[side_to_index(Side::WHITE)] &&
      _M_color_bitboards[side_to_index(Side::BLACK)] == board._M_color_bitboards[side_to_index(Side::BLACK)] &&
      _M_piece_bitboards[piece_to_index(Piece::PAWN)] == board._M_piece_bitboards[piece_to_index(Piece::PAWN)] &&
      _M_piece_bitboards[piece_to_index(Piece::KNIGHT)] == board._M_piece_bitboards[piece_to_index(Piece::KNIGHT)] &&
      _M_piece_bitboards[piece_to_index(Piece::BISHOP)] == board._M_piece_bitboards[piece_to_index(Piece::BISHOP)] &&
      _M_piece_bitboards[piece_to_index(Piece::ROOK)] == board._M_piece_bitboards[piece_to_index(Piece::ROOK)] &&
      _M_piece_bitboards[piece_to_index(Piece::QUEEN)] == board._M_piece_bitboards[piece_to_index(Piece::QUEEN)] &&
      _M_piece_bitboards[piece_to_index(Piece::KING)] == board._M_piece_bitboards[piece_to_index(Piece::KING)] &&
      _M_king_squares[side_to_index(Side::WHITE)] == board._M_king_squares[side_to_index(Side::WHITE)] &&
      _M_king_squares[side_to_index(Side::BLACK)] == board._M_king_squares[side_to_index(Side::BLACK)] &&
      _M_side == board._M_side &&
      _M_castlings[side_to_index(Side::WHITE)] == board._M_castlings[side_to_index(Side::WHITE)] &&
      _M_castlings[side_to_index(Side::BLACK)] == board._M_castlings[side_to_index(Side::BLACK)] &&
      _M_en_passant_column == board._M_en_passant_column;
  }

  bool Board::has_attack(Side side, Square squ) const
  {
    Side opp_side = ~side;
    if((color_bitboard(opp_side) & piece_bitboard(Piece::PAWN) & tab_pawn_capture_bitboards[side_to_index(side)][squ]) != 0 &&
      (color_bitboard(opp_side) & piece_bitboard(Piece::KNIGHT) & tab_knight_bitboards[squ]) != 0 &&
      (color_bitboard(opp_side) & piece_bitboard(Piece::KING) & tab_king_bitboards[squ]) != 0) return true;
    for(int i = 0; i < 4; i++) {
      int count = tab_bishop_square_counts[squ][i];
      for(int j = 0; j < count; j++) {
        int from = tab_bishop_squares[squ][i][j];
        if(has_color_piece(opp_side, Piece::BISHOP, Piece::QUEEN, squ)) return true;
        if(has_color(side, from)) break;
      }
    }
    for(int i = 0; i < 4; i++) {
      int count = tab_rook_square_counts[squ][i];
      for(int j = 0; j < count; j++) {
        int from = tab_rook_squares[squ][i][j];
        if(has_color_piece(opp_side, Piece::ROOK, Piece::QUEEN, squ)) return true;
        if(has_color(side, from)) break;
      }
    }
    return false;
  }

  void Board::generate_pseudolegal_moves(MovePairList &move_pairs) const
  {
    Bitboard bbd = color_bitboard(_M_side);
    for(Square i = 0; i < 64; i += 4) {
      int bits = bbd & 0xf;
      int count = tab_square_offset_counts[bits];
      for(int j = 0; j < count; j++) {
        Square from = i + tab_square_offsets[bits][j];
        if(has_piece(Piece::PAWN, from)) {
          int cap_squ_count = tab_pawn_capture_square_counts[from][side_to_index(_M_side)];
          for(int k = 0; k < cap_squ_count; k++) {
            Square to = tab_pawn_capture_squares[from][side_to_index(_M_side)][k];
            Square en_passant_squ = (_M_en_passant_column != -1 ? _M_en_passant_column + (_M_side == Side::WHITE ? 050 : 020) : -1);
            if(has_color(~_M_side, to) || to == en_passant_squ) {
              if(from >> 3 == (_M_side == Side::WHITE ? 6 : 1)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::QUEEN)));
                move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::KNIGHT)));
              } else
                move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::NONE)));
            }
          }
          int squ_count = tab_pawn_square_counts[from][side_to_index(_M_side)];
          for(int k = 0; k < squ_count; k++) {
            Square to = tab_pawn_squares[from][side_to_index(_M_side)][k];
            if(has_empty(to)) {
              if(from >> 3 == (_M_side == Side::WHITE ? 6 : 1)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::QUEEN)));
                move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::KNIGHT)));
              } else
                move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::NONE)));
            } else
              break;
          }
        } else if(has_piece(Piece::KNIGHT, from)) {
          int squ_count = tab_knight_square_counts[from];
          for(int k = 0; k < squ_count; k++) {
            Square to = tab_knight_squares[from][k];
            if(has_color(~_M_side, to) || has_empty(to))
              move_pairs.add_move_pair(MovePair(Move(Piece::KNIGHT, from, to, PromotionPiece::NONE)));
          }
        } else if(has_piece(Piece::BISHOP, from)) {
          for(int k = 0; k < 4; k++) {
            int squ_count = tab_bishop_square_counts[from][k];
            for(int l = 0; l < squ_count; l++) {
              Square to = tab_bishop_squares[from][k][l];
              if(has_color(~_M_side, to)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::BISHOP, from, to, PromotionPiece::NONE)));
                break;
              } else if(has_empty(to)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::BISHOP, from, to, PromotionPiece::NONE)));
              } else
                break;
            }
          }
        } else if(has_piece(Piece::ROOK, from)) {
          for(int k = 0; k < 4; k++) {
            int squ_count = tab_rook_square_counts[from][k];
            for(int l = 0; l < squ_count; l++) {
              Square to = tab_rook_squares[from][k][l];
              if(has_color(~_M_side, to)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::ROOK, from, to, PromotionPiece::NONE)));
                break;
              } else if(has_empty(to)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::ROOK, from, to, PromotionPiece::NONE)));
              } else
                break;
            }
          }
        } else if(has_piece(Piece::QUEEN, from)) {
          for(int k = 0; k < 8; k++) {
            int squ_count = tab_queen_square_counts[from][k];
            for(int l = 0; l < squ_count; l++) {
              Square to = tab_queen_squares[from][k][l];
              if(has_color(~_M_side, to)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::QUEEN, from, to, PromotionPiece::NONE)));
                break;
              } else if(has_empty(to)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::QUEEN, from, to, PromotionPiece::NONE)));
              } else
                break;
            }
          }
        } else if(has_piece(Piece::KING, from)) {
          int squ_count = tab_king_square_counts[from];
          for(int k = 0; k < squ_count; k++) {
            int to = tab_king_squares[from][k];
            if(has_color(~_M_side, to) || has_empty(to))
              move_pairs.add_move_pair(MovePair(Move(Piece::KING, from, to, PromotionPiece::NONE)));
          }
        }
      }
      bbd >>= 4;
    }
    if((side_castlings(_M_side) & SideCastlings::SHORT) != SideCastlings::NONE) {
      Bitboard castling_mask = static_cast<Bitboard>(0x60) << (_M_side == Side::WHITE ? 0 : 64 - 8);
      if((color_bitboard(Side::WHITE) | color_bitboard(Side::BLACK)) & castling_mask) {
        Square from = (_M_side == Side::WHITE ? E1 : E8);
        Square to = (_M_side == Side::WHITE ? G1 : G8);
        move_pairs.add_move_pair(MovePair(Move(Piece::KING, from, to, PromotionPiece::NONE)));
      }
    }
    if((side_castlings(_M_side) & SideCastlings::LONG) != SideCastlings::NONE) {
      Bitboard castling_mask = static_cast<Bitboard>(0x0e) << (_M_side == Side::WHITE ? 0 : 64 - 8);
      if((color_bitboard(Side::WHITE) | color_bitboard(Side::BLACK)) & castling_mask) {
        Square from = (_M_side == Side::WHITE ? E1 : E8);
        Square to = (_M_side == Side::WHITE ? C1 : C8);
        move_pairs.add_move_pair(MovePair(Move(Piece::KING, from, to, PromotionPiece::NONE)));
      }
    }
  }

  void Board::generate_pseudolegel_good_moves(MovePairList &move_pairs) const
  {
    Bitboard bbd = color_bitboard(_M_side);
    for(Square i = 0; i < 64; i += 4) {
      int bits = bbd & 0xf;
      int count = tab_square_offset_counts[bits];
      for(int j = 0; j < count; j++) {
        Square from = i + tab_square_offsets[bits][j];
        if(has_piece(Piece::PAWN, from)) {
          int cap_squ_count = tab_pawn_capture_square_counts[from][side_to_index(_M_side)];
          for(int k = 0; k < cap_squ_count; k++) {
            Square to = tab_pawn_capture_squares[from][side_to_index(_M_side)][k];
            Square en_passant_squ = (_M_en_passant_column != -1 ? _M_en_passant_column + (_M_side == Side::WHITE ? 050 : 020) : -1);
            if(has_color(~_M_side, to) || to == en_passant_squ) {
              if(from >> 3 == (_M_side == Side::WHITE ? 6 : 1)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::QUEEN)));
                move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::KNIGHT)));
              } else
                move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::NONE)));
            }
          }
          if(from >> 3 == (_M_side == Side::WHITE ? 6 : 1)) {
            Square to = tab_pawn_squares[from][side_to_index(_M_side)][0];
            if(has_empty(to)) {
              move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::QUEEN)));
              move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::KNIGHT)));
            }
          }
        } else if(has_piece(Piece::KNIGHT, from)) {
          int squ_count = tab_knight_square_counts[from];
          for(int k = 0; k < squ_count; k++) {
            Square to = tab_knight_squares[from][k];
            if(has_color(~_M_side, to))
              move_pairs.add_move_pair(MovePair(Move(Piece::KNIGHT, from, to, PromotionPiece::NONE)));
          }
        } else if(has_piece(Piece::BISHOP, from)) {
          for(int k = 0; k < 4; k++) {
            int squ_count = tab_bishop_square_counts[from][k];
            for(int l = 0; l < squ_count; l++) {
              Square to = tab_bishop_squares[from][k][l];
              if(has_color(~_M_side, to)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::BISHOP, from, to, PromotionPiece::NONE)));
                break;
              } else if(!has_empty(to))
                break;
            }
          }
        } else if(has_piece(Piece::ROOK, from)) {
          for(int k = 0; k < 4; k++) {
            int squ_count = tab_rook_square_counts[from][k];
            for(int l = 0; l < squ_count; l++) {
              Square to = tab_rook_squares[from][k][l];
              if(has_color(~_M_side, to)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::ROOK, from, to, PromotionPiece::NONE)));
                break;
              } else if(!has_empty(to))
                break;
            }
          }
        } else if(has_piece(Piece::QUEEN, from)) {
          for(int k = 0; k < 4; k++) {
            int squ_count = tab_queen_square_counts[from][k];
            for(int l = 0; l < squ_count; l++) {
              Square to = tab_queen_squares[from][k][l];
              if(has_color(~_M_side, to)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::QUEEN, from, to, PromotionPiece::NONE)));
                break;
              } else if(!has_empty(to))
                break;
            }
          }
        } else if(has_piece(Piece::KING, from)) {
          int squ_count = tab_king_square_counts[from];
          for(int k = 0; k < squ_count; k++) {
            Square to = tab_king_squares[from][k];
            if(has_color(~_M_side, to))
              move_pairs.add_move_pair(MovePair(Move(Piece::KING, from, to, PromotionPiece::NONE)));
          }
        }
      }
      bbd >>= 4;
    }
  }

  bool Board::make_move(Move move, Board &board) const
  {
    Square short_castling_dst = (_M_side == Side::WHITE ? G1 : G8);
    Square long_castling_dst = (_M_side == Side::WHITE ? C1 : C8);
    Side opp_side = ~_M_side;
    if(move.piece() == Piece::KING && move.from() == (_M_side == Side::WHITE ? E1 : E8) && move.to() == short_castling_dst) {
      if(in_check()) return false;
      Square rook_src = (_M_side == Side::WHITE ? H1 : H8);
      Square rook_dst = (_M_side == Side::WHITE ? F1 : F8);
      if(has_attack(_M_side, rook_dst)) return false;
      board._M_color_bitboards[side_to_index(_M_side)] = color_bitboard(_M_side);
      board._M_piece_bitboards[piece_to_index(Piece::PAWN)] = piece_bitboard(Piece::PAWN);
      board._M_piece_bitboards[piece_to_index(Piece::KNIGHT)] = piece_bitboard(Piece::KNIGHT);
      board._M_piece_bitboards[piece_to_index(Piece::BISHOP)] = piece_bitboard(Piece::BISHOP);
      board._M_piece_bitboards[piece_to_index(Piece::ROOK)] = piece_bitboard(Piece::ROOK);
      board._M_piece_bitboards[piece_to_index(Piece::QUEEN)] = piece_bitboard(Piece::QUEEN);
      board._M_piece_bitboards[piece_to_index(Piece::KING)] = piece_bitboard(Piece::KING);
      board._M_piece_bitboards[piece_to_index(Piece::KING)] &= ~(static_cast<Bitboard>(1) << move.from());
      board._M_color_bitboards[side_to_index(_M_side)] &= ~(static_cast<Bitboard>(1) << move.from());
      board._M_color_bitboards[side_to_index(_M_side)] |= static_cast<Bitboard>(1) << move.to();
      board._M_color_bitboards[side_to_index(_M_side)] &= ~(static_cast<Bitboard>(1) << rook_src);
      board._M_color_bitboards[side_to_index(_M_side)] |= static_cast<Bitboard>(1) << rook_dst;
      board._M_piece_bitboards[piece_to_index(Piece::KING)] |= static_cast<Bitboard>(1) << move.to();
      board._M_piece_bitboards[piece_to_index(Piece::ROOK)] &= ~(static_cast<Bitboard>(1) << rook_src);
      board._M_piece_bitboards[piece_to_index(Piece::ROOK)] |= static_cast<Bitboard>(1) << rook_dst;
      board._M_king_squares[side_to_index(_M_side)] = move.to();
      board._M_king_squares[side_to_index(opp_side)] = king_square(opp_side);
      board._M_side = opp_side;
      board._M_castlings[side_to_index(_M_side)] = SideCastlings::NONE;
      board._M_castlings[side_to_index(opp_side)] = side_castlings(opp_side);
      board._M_en_passant_column = -1;
      board._M_halfmove_clock = board._M_halfmove_clock + 1;
      board._M_fullmove_number = _M_fullmove_number + (_M_side == Side::BLACK ? 1 : 0); 
    } else if(move.piece() == Piece::KING && move.from() == (_M_side == Side::WHITE ? E1 : E8) && move.to() == long_castling_dst) {
      if(in_check()) return false;
      Square rook_src = (_M_side == Side::WHITE ? A1 : A8);
      Square rook_dst = (_M_side == Side::WHITE ? D1 : D8);
      if(has_attack(_M_side, rook_dst)) return false;
      board._M_color_bitboards[side_to_index(_M_side)] = color_bitboard(_M_side);
      board._M_piece_bitboards[piece_to_index(Piece::PAWN)] = piece_bitboard(Piece::PAWN);
      board._M_piece_bitboards[piece_to_index(Piece::KNIGHT)] = piece_bitboard(Piece::KNIGHT);
      board._M_piece_bitboards[piece_to_index(Piece::BISHOP)] = piece_bitboard(Piece::BISHOP);
      board._M_piece_bitboards[piece_to_index(Piece::ROOK)] = piece_bitboard(Piece::ROOK);
      board._M_piece_bitboards[piece_to_index(Piece::QUEEN)] = piece_bitboard(Piece::QUEEN);
      board._M_piece_bitboards[piece_to_index(Piece::KING)] = piece_bitboard(Piece::KING);
      board._M_color_bitboards[side_to_index(_M_side)] &= ~(static_cast<Bitboard>(1) << move.from());
      board._M_color_bitboards[side_to_index(_M_side)] |= static_cast<Bitboard>(1) << move.to();
      board._M_color_bitboards[side_to_index(_M_side)] &= ~(static_cast<Bitboard>(1) << rook_src);
      board._M_color_bitboards[side_to_index(_M_side)] |= static_cast<Bitboard>(1) << rook_dst;
      board._M_piece_bitboards[piece_to_index(Piece::KING)] &= ~(static_cast<Bitboard>(1) << move.from());
      board._M_piece_bitboards[piece_to_index(Piece::KING)] |= static_cast<Bitboard>(1) << move.to();
      board._M_piece_bitboards[piece_to_index(Piece::ROOK)] &= ~(static_cast<Bitboard>(1) << rook_src);
      board._M_piece_bitboards[piece_to_index(Piece::ROOK)] |= static_cast<Bitboard>(1) << rook_dst;
      board._M_king_squares[side_to_index(_M_side)] = move.to();
      board._M_king_squares[side_to_index(opp_side)] = king_square(opp_side);
      board._M_side = opp_side;
      board._M_castlings[side_to_index(_M_side)] = SideCastlings::NONE;
      board._M_castlings[side_to_index(opp_side)] = side_castlings(opp_side);
      board._M_en_passant_column = -1;
      board._M_halfmove_clock = board._M_halfmove_clock + 1;
      board._M_fullmove_number = _M_fullmove_number + (_M_side == Side::BLACK ? 1 : 0); 
    } else {
      Bitboard src_mask = ~(static_cast<Bitboard>(1) << move.from());
      Bitboard dst_mask = ~(static_cast<Bitboard>(1) << move.to());
      Bitboard dst_bbd = static_cast<Bitboard>(1) << move.to();
      board._M_color_bitboards[side_to_index(_M_side)] = color_bitboard(_M_side) | dst_bbd;
      board._M_color_bitboards[side_to_index(opp_side)] = color_bitboard(opp_side) & dst_mask;
      board._M_piece_bitboards[piece_to_index(Piece::PAWN)] = piece_bitboard(Piece::PAWN) & dst_mask;
      board._M_piece_bitboards[piece_to_index(Piece::KNIGHT)] = piece_bitboard(Piece::KNIGHT) & dst_mask;
      board._M_piece_bitboards[piece_to_index(Piece::BISHOP)] = piece_bitboard(Piece::BISHOP) & dst_mask;
      board._M_piece_bitboards[piece_to_index(Piece::ROOK)] = piece_bitboard(Piece::ROOK) & dst_mask;
      board._M_piece_bitboards[piece_to_index(Piece::QUEEN)] = piece_bitboard(Piece::QUEEN) & dst_mask;
      board._M_piece_bitboards[piece_to_index(Piece::KING)] = piece_bitboard(Piece::KING) & dst_mask;
      board._M_color_bitboards[side_to_index(_M_side)] &= src_mask;
      board._M_piece_bitboards[piece_to_index(move.piece())] &= src_mask;
      if(move.promotion_piece() == PromotionPiece::NONE)
        board._M_piece_bitboards[piece_to_index(move.piece())] |= dst_bbd;
      else
        board._M_piece_bitboards[promotion_piece_to_index(move.promotion_piece())] |= dst_bbd;
      bool is_cap = ((color_bitboard(opp_side) & dst_bbd) != 0);
      Square en_passant_squ = (_M_en_passant_column != -1 ? _M_en_passant_column + (_M_side == Side::WHITE ? 050 : 020) : -1);
      if(move.piece() == Piece::PAWN && move.to() == en_passant_squ) {
        is_cap |= true;
        Bitboard cap_bbd = (_M_side == Side::WHITE ? dst_bbd >> 8 : dst_bbd << 8);
        Bitboard cap_mask = ~cap_bbd;
        board._M_color_bitboards[side_to_index(opp_side)] &= cap_mask;
        board._M_piece_bitboards[piece_to_index(Piece::PAWN)] &= cap_mask;
      }
      board._M_king_squares[side_to_index(_M_side)] = (move.piece() == Piece::KING ? move.to() : king_square(_M_side));
      board._M_king_squares[side_to_index(opp_side)] = king_square(opp_side);
      board._M_side = opp_side;
      switch(move.piece()) {
        case Piece::ROOK:
          if(move.from() == (_M_side == Side::WHITE ? H1 : H8))
            board._M_castlings[side_to_index(_M_side)] &= ~SideCastlings::SHORT;
          else if(move.from() == (_M_side == Side::WHITE ? A1 : A8))
            board._M_castlings[side_to_index(_M_side)] &= ~SideCastlings::LONG;            
          break;
        case Piece::KING:
          board._M_castlings[side_to_index(_M_side)] = SideCastlings::NONE;
          break;
        default:
          break;
      }
      board._M_castlings[side_to_index(opp_side)] = side_castlings(opp_side);
      Row pawn_src_row2 = (_M_side == Side::WHITE ? 1 : 6);
      Row pawn_dst_row2 = (_M_side == Side::WHITE ? 3 : 4);
      if(move.piece() == Piece::PAWN && (move.from() >> 3) == pawn_src_row2 && (move.to() >> 3) == pawn_dst_row2) {
        Square cap_squ = move.from() + (_M_side == Side::WHITE ? -8 : 8);
        if((color_bitboard(opp_side) & piece_bitboard(Piece::PAWN) & tab_pawn_capture_bitboards[side_to_index(_M_side)][cap_squ]) != 0)
          board._M_en_passant_column = move.from() & 7;
        else
          board._M_en_passant_column = -1;
      } else
        board._M_en_passant_column = -1;
      board._M_halfmove_clock = ((!is_cap && move.piece() != Piece::PAWN) ? _M_halfmove_clock + 1 : 0);
      board._M_fullmove_number = _M_fullmove_number + (_M_side == Side::BLACK ? 1 : 0);
    }
    return !board.in_check(_M_side);
  }
}
