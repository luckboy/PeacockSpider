/*
 * Peacock Spider - Chess engine.
 * Copyright (C) 2020-2021 Łukasz Szpakowski
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
#include <sstream>
#include "chess.hpp"
#include "tables.hpp"
#include "zobrist.hpp"

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
    update_hash_key();
  }
  
  Board::Board(const string &str)
  { if(!unsafely_set(str)) throw Exception("invalid fen"); }

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
      _M_en_passant_column == board._M_en_passant_column &&
      _M_hash_key == board._M_hash_key;
  }

  void Board::update_hash_key()
  {
    _M_hash_key = 0;
    for(Square squ = 0; squ < 64; squ++) {
      switch(color(squ)) {
        case Color::WHITE:
          _M_hash_key ^= zobrist[side_to_index(Side::WHITE)][piece_to_index(piece(squ))][squ];
          break;
        case Color::BLACK:
          _M_hash_key ^= zobrist[side_to_index(Side::BLACK)][piece_to_index(piece(squ))][squ];
          break;
        default:
          break;
      }
    }
    _M_hash_key ^= (_M_side == Side::WHITE ? zobrist_white_side : 0);
    _M_hash_key ^= zobrist_castlings[side_to_index(Side::WHITE)][side_castlings_to_index(side_castlings(Side::WHITE))];
    _M_hash_key ^= zobrist_castlings[side_to_index(Side::BLACK)][side_castlings_to_index(side_castlings(Side::BLACK))];
    _M_hash_key ^= zobrist_en_passant_column[_M_en_passant_column + 1];
  }

  bool Board::has_attack(Side side, Square squ) const
  {
    Side opp_side = ~side;
    if((color_bitboard(opp_side) & piece_bitboard(Piece::PAWN) & tab_pawn_capture_bitboards[side_to_index(side)][squ]) != 0 ||
      (color_bitboard(opp_side) & piece_bitboard(Piece::KNIGHT) & tab_knight_bitboards[squ]) != 0 ||
      (color_bitboard(opp_side) & piece_bitboard(Piece::KING) & tab_king_bitboards[squ]) != 0) return true;
    for(int i = 0; i < 4; i++) {
      int count = tab_bishop_square_counts[squ][i];
      for(int j = 0; j < count; j++) {
        int from = tab_bishop_squares[squ][i][j];
        if(has_color_piece(opp_side, Piece::BISHOP, Piece::QUEEN, from)) return true;
        if(!has_empty(from)) break;
      }
    }
    for(int i = 0; i < 4; i++) {
      int count = tab_rook_square_counts[squ][i];
      for(int j = 0; j < count; j++) {
        int from = tab_rook_squares[squ][i][j];
        if(has_color_piece(opp_side, Piece::ROOK, Piece::QUEEN, from)) return true;
        if(!has_empty(from)) break;
      }
    }
    return false;
  }

  void Board::generate_pseudolegal_moves(MovePairList &move_pairs) const
  {
    move_pairs.clear();
    Bitboard bbd = color_bitboard(_M_side);
    for(Square i = 0; i < 64; i += 4) {
      int bits = bbd & 0xf;
      int count = tab_square_offset_counts[bits];
      for(int j = 0; j < count; j++) {
        Square from = i + tab_square_offsets[bits][j];
        if(has_piece(Piece::PAWN, from)) {
          int cap_squ_count = tab_pawn_capture_square_counts[side_to_index(_M_side)][from];
          for(int k = 0; k < cap_squ_count; k++) {
            Square to = tab_pawn_capture_squares[side_to_index(_M_side)][from][k];
            Square en_passant_squ = (_M_en_passant_column != -1 ? _M_en_passant_column + (_M_side == Side::WHITE ? 050 : 020) : -1);
            if(has_color(~_M_side, to) || to == en_passant_squ) {
              if(from >> 3 == (_M_side == Side::WHITE ? 6 : 1)) {
                move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::QUEEN)));
                move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::KNIGHT)));
              } else
                move_pairs.add_move_pair(MovePair(Move(Piece::PAWN, from, to, PromotionPiece::NONE)));
            }
          }
          int squ_count = tab_pawn_square_counts[side_to_index(_M_side)][from];
          for(int k = 0; k < squ_count; k++) {
            Square to = tab_pawn_squares[side_to_index(_M_side)][from][k];
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
      if(((color_bitboard(Side::WHITE) | color_bitboard(Side::BLACK)) & castling_mask) == 0) {
        Square from = (_M_side == Side::WHITE ? E1 : E8);
        Square to = (_M_side == Side::WHITE ? G1 : G8);
        move_pairs.add_move_pair(MovePair(Move(Piece::KING, from, to, PromotionPiece::NONE)));
      }
    }
    if((side_castlings(_M_side) & SideCastlings::LONG) != SideCastlings::NONE) {
      Bitboard castling_mask = static_cast<Bitboard>(0x0e) << (_M_side == Side::WHITE ? 0 : 64 - 8);
      if(((color_bitboard(Side::WHITE) | color_bitboard(Side::BLACK)) & castling_mask) == 0) {
        Square from = (_M_side == Side::WHITE ? E1 : E8);
        Square to = (_M_side == Side::WHITE ? C1 : C8);
        move_pairs.add_move_pair(MovePair(Move(Piece::KING, from, to, PromotionPiece::NONE)));
      }
    }
  }

  void Board::generate_pseudolegal_good_moves(MovePairList &move_pairs) const
  {
    move_pairs.clear();
    Bitboard bbd = color_bitboard(_M_side);
    for(Square i = 0; i < 64; i += 4) {
      int bits = bbd & 0xf;
      int count = tab_square_offset_counts[bits];
      for(int j = 0; j < count; j++) {
        Square from = i + tab_square_offsets[bits][j];
        if(has_piece(Piece::PAWN, from)) {
          int cap_squ_count = tab_pawn_capture_square_counts[side_to_index(_M_side)][from];
          for(int k = 0; k < cap_squ_count; k++) {
            Square to = tab_pawn_capture_squares[side_to_index(_M_side)][from][k];
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
            Square to = tab_pawn_squares[side_to_index(_M_side)][from][0];
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
          for(int k = 0; k < 8; k++) {
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
      board.set_color_bitboard(Side::WHITE, color_bitboard(Side::WHITE));
      board.set_color_bitboard(Side::BLACK, color_bitboard(Side::BLACK));
      board.set_piece_bitboard(Piece::PAWN, piece_bitboard(Piece::PAWN));
      board.set_piece_bitboard(Piece::KNIGHT, piece_bitboard(Piece::KNIGHT));
      board.set_piece_bitboard(Piece::BISHOP, piece_bitboard(Piece::BISHOP));
      board.set_piece_bitboard(Piece::ROOK, piece_bitboard(Piece::ROOK));
      board.set_piece_bitboard(Piece::QUEEN, piece_bitboard(Piece::QUEEN));
      board.set_piece_bitboard(Piece::KING, piece_bitboard(Piece::KING));
      board.and_color_bitboard(_M_side, ~(static_cast<Bitboard>(1) << move.from()));
      board.or_color_bitboard(_M_side, static_cast<Bitboard>(1) << move.to());
      board.and_color_bitboard(_M_side, ~(static_cast<Bitboard>(1) << rook_src));
      board.or_color_bitboard(_M_side, static_cast<Bitboard>(1) << rook_dst);
      board.and_piece_bitboard(Piece::KING, ~(static_cast<Bitboard>(1) << move.from()));
      board.or_piece_bitboard(Piece::KING, static_cast<Bitboard>(1) << move.to());
      board.and_piece_bitboard(Piece::ROOK, ~(static_cast<Bitboard>(1) << rook_src));
      board.or_piece_bitboard(Piece::ROOK, static_cast<Bitboard>(1) << rook_dst);
      board.set_king_square(_M_side, move.to());
      board.set_king_square(opp_side, king_square(opp_side));
      board._M_side = opp_side;
      board.set_side_castlings(_M_side, SideCastlings::NONE);
      board.set_side_castlings(opp_side, side_castlings(opp_side));
      board._M_en_passant_column = -1;
      board._M_halfmove_clock = _M_halfmove_clock + 1;
      board._M_fullmove_number = _M_fullmove_number + (_M_side == Side::BLACK ? 1 : 0); 
      board._M_hash_key = _M_hash_key;
      board._M_hash_key ^= zobrist[side_to_index(_M_side)][piece_to_index(Piece::KING)][move.from()];
      board._M_hash_key ^= zobrist[side_to_index(_M_side)][piece_to_index(Piece::KING)][move.to()];
      board._M_hash_key ^= zobrist[side_to_index(_M_side)][piece_to_index(Piece::ROOK)][rook_src];
      board._M_hash_key ^= zobrist[side_to_index(_M_side)][piece_to_index(Piece::ROOK)][rook_dst];
      board._M_hash_key ^= zobrist_white_side;
      board._M_hash_key ^= zobrist_castlings[side_to_index(_M_side)][side_castlings_to_index(side_castlings(_M_side))];
      board._M_hash_key ^= zobrist_castlings[side_to_index(_M_side)][side_castlings_to_index(board.side_castlings(_M_side))];
      board._M_hash_key ^= zobrist_en_passant_column[_M_en_passant_column + 1];
      board._M_hash_key ^= zobrist_en_passant_column[board._M_en_passant_column + 1];
    } else if(move.piece() == Piece::KING && move.from() == (_M_side == Side::WHITE ? E1 : E8) && move.to() == long_castling_dst) {
      if(in_check()) return false;
      Square rook_src = (_M_side == Side::WHITE ? A1 : A8);
      Square rook_dst = (_M_side == Side::WHITE ? D1 : D8);
      if(has_attack(_M_side, rook_dst)) return false;
      board.set_color_bitboard(Side::WHITE, color_bitboard(Side::WHITE));
      board.set_color_bitboard(Side::BLACK, color_bitboard(Side::BLACK));
      board.set_piece_bitboard(Piece::PAWN, piece_bitboard(Piece::PAWN));
      board.set_piece_bitboard(Piece::KNIGHT, piece_bitboard(Piece::KNIGHT));
      board.set_piece_bitboard(Piece::BISHOP, piece_bitboard(Piece::BISHOP));
      board.set_piece_bitboard(Piece::ROOK, piece_bitboard(Piece::ROOK));
      board.set_piece_bitboard(Piece::QUEEN, piece_bitboard(Piece::QUEEN));
      board.set_piece_bitboard(Piece::KING, piece_bitboard(Piece::KING));
      board.and_color_bitboard(_M_side, ~(static_cast<Bitboard>(1) << move.from()));
      board.or_color_bitboard(_M_side, static_cast<Bitboard>(1) << move.to());
      board.and_color_bitboard(_M_side, ~(static_cast<Bitboard>(1) << rook_src));
      board.or_color_bitboard(_M_side, static_cast<Bitboard>(1) << rook_dst);
      board.and_piece_bitboard(Piece::KING, ~(static_cast<Bitboard>(1) << move.from()));
      board.or_piece_bitboard(Piece::KING, static_cast<Bitboard>(1) << move.to());
      board.and_piece_bitboard(Piece::ROOK, ~(static_cast<Bitboard>(1) << rook_src));
      board.or_piece_bitboard(Piece::ROOK, static_cast<Bitboard>(1) << rook_dst);
      board.set_king_square(_M_side, move.to());
      board.set_king_square(opp_side, king_square(opp_side));
      board._M_side = opp_side;
      board.set_side_castlings(_M_side, SideCastlings::NONE);
      board.set_side_castlings(opp_side, side_castlings(opp_side));
      board._M_en_passant_column = -1;
      board._M_halfmove_clock = _M_halfmove_clock + 1;
      board._M_fullmove_number = _M_fullmove_number + (_M_side == Side::BLACK ? 1 : 0); 
      board._M_hash_key = _M_hash_key;
      board._M_hash_key ^= zobrist[side_to_index(_M_side)][piece_to_index(Piece::KING)][move.from()];
      board._M_hash_key ^= zobrist[side_to_index(_M_side)][piece_to_index(Piece::KING)][move.to()];
      board._M_hash_key ^= zobrist[side_to_index(_M_side)][piece_to_index(Piece::ROOK)][rook_src];
      board._M_hash_key ^= zobrist[side_to_index(_M_side)][piece_to_index(Piece::ROOK)][rook_dst];
      board._M_hash_key ^= zobrist_white_side;
      board._M_hash_key ^= zobrist_castlings[side_to_index(_M_side)][side_castlings_to_index(side_castlings(_M_side))];
      board._M_hash_key ^= zobrist_castlings[side_to_index(_M_side)][side_castlings_to_index(board.side_castlings(_M_side))];
      board._M_hash_key ^= zobrist_en_passant_column[_M_en_passant_column + 1];
      board._M_hash_key ^= zobrist_en_passant_column[board._M_en_passant_column + 1];
    } else {
      Bitboard src_mask = ~(static_cast<Bitboard>(1) << move.from());
      Bitboard dst_mask = ~(static_cast<Bitboard>(1) << move.to());
      Bitboard dst_bbd = static_cast<Bitboard>(1) << move.to();
      size_t dst_piece_idx;
      board.set_color_bitboard(_M_side, color_bitboard(_M_side) | dst_bbd);
      board.set_color_bitboard(opp_side, color_bitboard(opp_side) & dst_mask);
      board.set_piece_bitboard(Piece::PAWN, piece_bitboard(Piece::PAWN) & dst_mask);
      board.set_piece_bitboard(Piece::KNIGHT, piece_bitboard(Piece::KNIGHT) & dst_mask);
      board.set_piece_bitboard(Piece::BISHOP, piece_bitboard(Piece::BISHOP) & dst_mask);
      board.set_piece_bitboard(Piece::ROOK, piece_bitboard(Piece::ROOK) & dst_mask);
      board.set_piece_bitboard(Piece::QUEEN, piece_bitboard(Piece::QUEEN) & dst_mask);
      board.set_piece_bitboard(Piece::KING, piece_bitboard(Piece::KING) & dst_mask);
      board.and_color_bitboard(_M_side, src_mask);
      board.and_piece_bitboard(move.piece(), src_mask);
      if(move.promotion_piece() == PromotionPiece::NONE) {
        board.or_piece_bitboard(move.piece(), dst_bbd);
        dst_piece_idx = piece_to_index(move.piece());
      } else {
        board.or_piece_bitboard(move.promotion_piece(), dst_bbd);
        dst_piece_idx = promotion_piece_to_index(move.promotion_piece());
      }
      bool is_cap = ((color_bitboard(opp_side) & dst_bbd) != 0);
      bool is_cap_rook = (is_cap ? ((piece_bitboard(Piece::ROOK) & dst_bbd) != 0) : false);
      Square en_passant_squ = (_M_en_passant_column != -1 ? _M_en_passant_column + (_M_side == Side::WHITE ? 050 : 020) : -1);
      Square en_passant_cap_squ = -1;
      if(move.piece() == Piece::PAWN && move.to() == en_passant_squ) {
        is_cap = true;
        Bitboard cap_bbd = (_M_side == Side::WHITE ? dst_bbd >> 8 : dst_bbd << 8);
        Bitboard cap_mask = ~cap_bbd;
        en_passant_cap_squ = (_M_side == Side::WHITE ? move.to() - 8 : move.to() + 8);
        board.and_color_bitboard(opp_side, cap_mask);
        board.and_piece_bitboard(Piece::PAWN, cap_mask);
      }
      board.set_king_square(_M_side, move.piece() == Piece::KING ? move.to() : king_square(_M_side));
      board.set_king_square(opp_side, king_square(opp_side));
      board._M_side = opp_side;
      switch(move.piece()) {
        case Piece::ROOK:
          if(move.from() == (_M_side == Side::WHITE ? H1 : H8))
            board.set_side_castlings(_M_side, side_castlings(_M_side) & ~SideCastlings::SHORT);
          else if(move.from() == (_M_side == Side::WHITE ? A1 : A8))
            board.set_side_castlings(_M_side, side_castlings(_M_side) & ~SideCastlings::LONG);
          else
            board.set_side_castlings(_M_side, side_castlings(_M_side));
          break;
        case Piece::KING:
          board.set_side_castlings(_M_side, SideCastlings::NONE);
          break;
        default:
          board.set_side_castlings(_M_side, side_castlings(_M_side));
          break;
      }
      if(is_cap_rook && move.to() == (_M_side == Side::WHITE ? H8 : H1))
        board.set_side_castlings(opp_side, side_castlings(opp_side) & ~SideCastlings::SHORT);
      else if(is_cap_rook && move.to() == (_M_side == Side::WHITE ? A8 : A1))
        board.set_side_castlings(opp_side, side_castlings(opp_side) & ~SideCastlings::LONG);
      else
        board.set_side_castlings(opp_side, side_castlings(opp_side));
      Row pawn_src_row2 = (_M_side == Side::WHITE ? 1 : 6);
      Row pawn_dst_row2 = (_M_side == Side::WHITE ? 3 : 4);
      if(move.piece() == Piece::PAWN && (move.from() >> 3) == pawn_src_row2 && (move.to() >> 3) == pawn_dst_row2) {
        Square en_passant_squ2 = move.from() + (_M_side == Side::WHITE ? 8 : -8);
        if((color_bitboard(opp_side) & piece_bitboard(Piece::PAWN) & tab_pawn_capture_bitboards[side_to_index(_M_side)][en_passant_squ2]) != 0)
          board._M_en_passant_column = move.from() & 7;
        else
          board._M_en_passant_column = -1;
      } else
        board._M_en_passant_column = -1;
      board._M_halfmove_clock = ((!is_cap && move.piece() != Piece::PAWN) ? _M_halfmove_clock + 1 : 0);
      board._M_fullmove_number = _M_fullmove_number + (_M_side == Side::BLACK ? 1 : 0);
      board._M_hash_key = _M_hash_key;
      board._M_hash_key ^= zobrist[side_to_index(_M_side)][piece_to_index(move.piece())][move.from()];
      board._M_hash_key ^= zobrist[side_to_index(_M_side)][dst_piece_idx][move.to()];
      if((color_bitboard(opp_side) & dst_bbd) != 0) {
        Piece cap_piece;
        if((piece_bitboard(Piece::PAWN) & dst_bbd) != 0)
          cap_piece = Piece::PAWN;
        else if((piece_bitboard(Piece::KNIGHT) & dst_bbd) != 0)
          cap_piece = Piece::KNIGHT;
        else if((piece_bitboard(Piece::BISHOP) & dst_bbd) != 0)
          cap_piece = Piece::BISHOP;
        else if((piece_bitboard(Piece::ROOK) & dst_bbd) != 0)
          cap_piece = Piece::ROOK;
        else if((piece_bitboard(Piece::QUEEN) & dst_bbd) != 0)
          cap_piece = Piece::QUEEN;
        else if((piece_bitboard(Piece::KING) & dst_bbd) != 0)
          cap_piece = Piece::KING;
        else
          cap_piece = Piece::PAWN;
        board._M_hash_key ^= zobrist[side_to_index(opp_side)][piece_to_index(cap_piece)][move.to()];
      }
      if(en_passant_cap_squ != -1)
        board._M_hash_key ^= zobrist[side_to_index(opp_side)][piece_to_index(Piece::PAWN)][en_passant_cap_squ];
      board._M_hash_key ^= zobrist_white_side;
      board._M_hash_key ^= zobrist_castlings[side_to_index(_M_side)][side_castlings_to_index(side_castlings(_M_side))];
      board._M_hash_key ^= zobrist_castlings[side_to_index(_M_side)][side_castlings_to_index(board.side_castlings(_M_side))];
      board._M_hash_key ^= zobrist_castlings[side_to_index(opp_side)][side_castlings_to_index(side_castlings(opp_side))];
      board._M_hash_key ^= zobrist_castlings[side_to_index(opp_side)][side_castlings_to_index(board.side_castlings(opp_side))];
      board._M_hash_key ^= zobrist_en_passant_column[_M_en_passant_column + 1];
      board._M_hash_key ^= zobrist_en_passant_column[board._M_en_passant_column + 1];
    }
    return !board.in_check(_M_side);
  }

  void Board::make_null_move(Board &board) const
  {
    board.set_color_bitboard(Side::WHITE, color_bitboard(Side::WHITE));
    board.set_color_bitboard(Side::BLACK, color_bitboard(Side::BLACK));
    board.set_piece_bitboard(Piece::PAWN, piece_bitboard(Piece::PAWN));
    board.set_piece_bitboard(Piece::KNIGHT, piece_bitboard(Piece::KNIGHT));
    board.set_piece_bitboard(Piece::BISHOP, piece_bitboard(Piece::BISHOP));
    board.set_piece_bitboard(Piece::ROOK, piece_bitboard(Piece::ROOK));
    board.set_piece_bitboard(Piece::QUEEN, piece_bitboard(Piece::QUEEN));
    board.set_piece_bitboard(Piece::KING, piece_bitboard(Piece::KING));
    board.set_king_square(Side::WHITE, king_square(Side::WHITE));
    board.set_king_square(Side::BLACK, king_square(Side::BLACK));
    board._M_side = ~_M_side;
    board.set_side_castlings(Side::WHITE, side_castlings(Side::WHITE));
    board.set_side_castlings(Side::BLACK, side_castlings(Side::BLACK));
    board._M_en_passant_column = -1;
    board._M_halfmove_clock = _M_halfmove_clock;
    board._M_fullmove_number = _M_fullmove_number + (_M_side == Side::BLACK ? 1 : 0);
    board._M_hash_key = _M_hash_key;
    board._M_hash_key ^= zobrist_white_side;
    board._M_hash_key ^= zobrist_en_passant_column[_M_en_passant_column + 1];
    board._M_hash_key ^= zobrist_en_passant_column[board._M_en_passant_column + 1];
  }
  
  bool Board::has_legal_move(Move move) const
  {
    Board tmp_board;
    return make_move(move, tmp_board);
  }
  
  bool Board::has_legal_move_for_tt(Move move) const
  { return has_color_piece(_M_side, move.piece(), move.from()) && (has_color(~_M_side, move.to()) || has_empty(move.to())); }
  
  bool Board::in_checkmate(MovePairList &move_pairs) const
  {
    if(in_check()) {
      generate_pseudolegal_moves(move_pairs);
      for(size_t i = 0; i < move_pairs.length(); i++) {
        if(has_legal_move(move_pairs[i].move)) return false;
      }
      return true;
    } else
      return false;
  }

  bool Board::in_stalemate(MovePairList &move_pairs) const
  {
    if(!in_check()) {
      generate_pseudolegal_moves(move_pairs);
      for(size_t i = 0; i < move_pairs.length(); i++) {
        if(has_legal_move(move_pairs[i].move)) return false;
      }
      return true;
    } else
      return false;
  }
  
  bool Board::unsafely_set(const string &str)
  {
    auto iter = str.begin();
    // Sets colors and pieces.
    int white_piece_count = 0;
    int black_piece_count = 0;
    set_king_square(Side::WHITE, -1);
    set_king_square(Side::BLACK, -1);
    for(Row row = 7; row >= 0; row--) {
      Column col = 0;
      while(col < 8) {
        if(iter == str.end()) return false;
        if(*iter >= '1' && *iter <= '8') {
          int count = *iter - '0';
          if(count > 8 - col) return false;
          for(int i = 0; i < count; i++) {
            set_color(col + (row << 3), Color::EMPTY);
            unset_piece(col + (row << 3));
            col++;
          }
        } else {
          Color tmp_color = (isupper(*iter) ? Color::WHITE : Color::BLACK);
          Side tmp_side = (tmp_color == Color::WHITE ? Side::WHITE : Side::BLACK);
          pair<Piece, bool> tmp_piece_pair = char_to_piece_pair(toupper(*iter));
          if(!tmp_piece_pair.second) return false;
          set_color(col + (row << 3), tmp_color);
          set_piece(col + (row << 3), tmp_piece_pair.first);
          if(tmp_piece_pair.first == Piece::KING) {
            if(king_square(tmp_side) == -1)
              set_king_square(tmp_side, col + (row << 3));
            else
              return false;
          }
          if(tmp_side == Side::WHITE)
            white_piece_count++;
          else
            black_piece_count++;
          col++;
        }
        iter++;
      }
      if(row - 1 >= 0) {
        if(iter == str.end()) return false;
        if(*iter != '/') return false;
        iter++;
      }
    }
    if(king_square(Side::WHITE) == -1) return false;
    if(king_square(Side::BLACK) == -1) return false;
    if(white_piece_count > 16) return false;
    if(black_piece_count > 16) return false;
    if(iter == str.end() || (*iter != ' ' && *iter != '\t')) return false; 
    while(iter != str.end() && (*iter == ' ' || *iter == '\t')) iter++;
    // Sets side.
    if(iter == str.end()) return false;
    pair<Side, bool> side_pair = char_to_side_pair(*iter);
    if(!side_pair.second) return false;
    set_side(side_pair.first);
    iter++;
    if(iter == str.end() || (*iter != ' ' && *iter != '\t')) return false; 
    while(iter != str.end() && (*iter == ' ' || *iter == '\t')) iter++;
    // Sets castlings.
    if(iter == str.end()) return false;
    set_side_castlings(Side::WHITE, SideCastlings::NONE);
    set_side_castlings(Side::BLACK, SideCastlings::NONE);
    if(iter == str.end() || *iter != '-') {
      while(iter != str.end()) {
        bool is_castling = true;
        switch(*iter) {
          case 'K':
            set_side_castlings(Side::WHITE, side_castlings(Side::WHITE) | SideCastlings::SHORT);
            break;
          case 'Q':
            set_side_castlings(Side::WHITE, side_castlings(Side::WHITE) | SideCastlings::LONG);
            break;
          case 'k':
            set_side_castlings(Side::BLACK, side_castlings(Side::BLACK) | SideCastlings::SHORT);
            break;
          case 'q':
            set_side_castlings(Side::BLACK, side_castlings(Side::BLACK) | SideCastlings::LONG);
            break;
          default:
            is_castling = false;
            break;
        }
        if(!is_castling) break;
        iter++;
      }
    } else
      iter++;
    if((side_castlings(Side::WHITE) & SideCastlings::SHORT) != SideCastlings::NONE) {
      if(!has_color_piece(Side::WHITE, Piece::KING, E1)) return false;
      if(!has_color_piece(Side::WHITE, Piece::ROOK, H1)) return false;
    }
    if((side_castlings(Side::WHITE) & SideCastlings::LONG) != SideCastlings::NONE) {
      if(!has_color_piece(Side::WHITE, Piece::KING, E1)) return false;
      if(!has_color_piece(Side::WHITE, Piece::ROOK, A1)) return false;
    }
    if((side_castlings(Side::BLACK) & SideCastlings::SHORT) != SideCastlings::NONE) {
      if(!has_color_piece(Side::BLACK, Piece::KING, E8)) return false;
      if(!has_color_piece(Side::BLACK, Piece::ROOK, H8)) return false;
    }
    if((side_castlings(Side::BLACK) & SideCastlings::LONG) != SideCastlings::NONE) {
      if(!has_color_piece(Side::BLACK, Piece::KING, E8)) return false;
      if(!has_color_piece(Side::BLACK, Piece::ROOK, A8)) return false;
    }
    if(iter == str.end() || (*iter != ' ' && *iter != '\t')) return false; 
    while(iter != str.end() && (*iter == ' ' || *iter == '\t')) iter++;
    // Sets en passant column.
    if(iter == str.end()) return false;
    Square en_passant_squ = -1;
    if(iter == str.end() || *iter != '-') {
      if(iter == str.end()) return false;
      if(iter + 1 == str.end()) return false;
      string en_passant_squ_str(iter, iter + 2);
      en_passant_squ = string_to_square(en_passant_squ_str);
      if(en_passant_squ == -1) return false;
      iter += 2;
    } else
      iter++;
    if(en_passant_squ != -1) {
      if((en_passant_squ >> 3) != (side() == Side::WHITE ? 5 : 2)) return false;
      if(color(en_passant_squ) != Color::EMPTY) return false; 
      Square cap_squ = en_passant_squ + (side() == Side::WHITE ? -8 : 8);
      if(color(cap_squ) != (side() == Side::WHITE ? Color::BLACK : Color::WHITE) || piece(cap_squ) != Piece::PAWN) return false;
      if((color_bitboard(side()) & piece_bitboard(Piece::PAWN) & tab_pawn_capture_bitboards[side_to_index(~side())][en_passant_squ]) == 0)
        en_passant_squ = -1;
    }
    set_en_passant_column(en_passant_squ != -1 ? (en_passant_squ & 7) : -1);
    if(iter == str.end() || (*iter != ' ' && *iter != '\t')) return false; 
    while(iter != str.end() && (*iter == ' ' || *iter == '\t')) iter++;
    // Sets halfmove clock.
    if(iter != str.end()) {
      auto iter2 = iter;
      while(iter2 != str.end() && *iter2 != ' ' && *iter2 != '\t') iter2++; 
      string tmp_str(iter, iter2);
      istringstream iss(tmp_str);
      int x;
      iss >> x;
      if(iss.fail() || !iss.eof()) return false;
      set_halfmove_clock(x);
      iter = iter2;
    } else
      return false;
    if(iter == str.end() || (*iter != ' ' && *iter != '\t')) return false; 
    while(iter != str.end() && (*iter == ' ' || *iter == '\t')) iter++;
    // Sets fullmove number.
    if(iter != str.end()) {
      auto iter2 = iter;
      while(iter2 != str.end() && *iter2 != ' ' && *iter2 != '\t') iter2++; 
      string tmp_str(iter, iter2);
      istringstream iss(tmp_str);
      int x;
      iss >> x;
      if(iss.fail() || !iss.eof()) return false;
      set_fullmove_number(x);
      iter = iter2;
    } else
      return false;
    if(iter != str.end()) return false;
    update_hash_key();
    if(in_check(~_M_side)) return false;
    return true;
  }

  bool Board::set(const std::string &str)
  {
    Board tmp_board;
    if(tmp_board.unsafely_set(str)) {
      *this = tmp_board;
      return true;
    } else
      return false;
  }

  string Board::to_string() const
  {
    string str;
    // Converts colors and pieces.
    for(Row row = 7; row >= 0; row--) {
      Column col = 0;
      while(col < 8) {
        if(color(col + (row << 3)) == Color::EMPTY) {
          int count;
          for(count = 0; count < 8; count++) {
            if(col >= 8) break;
            if(color(col + (row << 3)) != Color::EMPTY) break;
            col++;
          }
          str += static_cast<char>('0' + count);
        } else {
          Color tmp_color = color(col + (row << 3));
          Piece tmp_piece = piece(col + (row << 3));
          char c = piece_to_char(tmp_piece);
          str += static_cast<char>(tmp_color == Color::WHITE ? toupper(c) : tolower(c));
          col++;
        }
      }
      if(row -1 >= 0) str += '/';
    }
    str += ' ';
    // Converts side.
    str += side_to_char(side());
    str += ' ';
    // Converts castlings.
    if(side_castlings(Side::WHITE) != SideCastlings::NONE || side_castlings(Side::BLACK) != SideCastlings::NONE) {
      if((side_castlings(Side::WHITE) & SideCastlings::SHORT) != SideCastlings::NONE) str += 'K';
      if((side_castlings(Side::WHITE) & SideCastlings::LONG) != SideCastlings::NONE) str += 'Q';
      if((side_castlings(Side::BLACK) & SideCastlings::SHORT) != SideCastlings::NONE) str += 'k';
      if((side_castlings(Side::BLACK) & SideCastlings::LONG) != SideCastlings::NONE) str += 'q';
    } else
      str += '-';
    str += ' ';
    // Converts en passant column.
    if(en_passant_column() != -1) {
      Square en_passant_squ = en_passant_column() + (side() == Side::WHITE ? 050 : 020);
      str += square_to_string(en_passant_squ);
    } else
      str += '-';
    str += ' ';
    // Converts halfmove clock.
    ostringstream oss1;
    oss1 << halfmove_clock();
    str += oss1.str();
    str += ' ';
    // Converts fullmove number.
    ostringstream oss2;
    oss2 << fullmove_number();
    str += oss2.str();
    return str;
  }
}
