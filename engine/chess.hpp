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
#ifndef _CHESS_HPP
#define _CHESS_HPP

#include <cstddef>
#include <cstdint>
#include <utility>

namespace peacockspider
{
  typedef std::uint64_t Bitboard;
  typedef int Square;
  typedef int Column;
  typedef int Row;

  enum class Side
  {
    WHITE = 0,
    BLACK = 1
  };

  inline Side operator~(Side side)
  { return static_cast<Side>(static_cast<int>(side) ^ 1); }

  inline std::size_t side_to_index(Side side)
  { return static_cast<std::size_t>(side); }
  
  enum class Color
  {
    EMPTY = 0,
    WHITE = 1,
    BLACK = 2
  };

  enum class Piece
  {
    PAWN = 0,
    KNIGHT = 1,
    BISHOP = 2,
    ROOK = 3,
    QUEEN = 4,
    KING = 5
  };
  
  inline std::size_t piece_to_index(Piece piece)
  { return static_cast<std::size_t>(piece); }

  enum class PromotionPiece
  {
    NONE = 0,
    KNIGHT = 1,
    BISHOP = 2,
    ROOK = 3,
    QUEEN = 4
  };

  inline std::size_t promotion_piece_to_index(PromotionPiece promotion_piece)
  { return static_cast<std::size_t>(promotion_piece); }

  enum class SideCastlings
  {
    NONE = 0,
    SHORT = 1,
    LONG = 2
  };

  inline SideCastlings operator~(SideCastlings castlings)
  { return static_cast<SideCastlings>(static_cast<int>(castlings) ^ 3); }

  inline SideCastlings operator&(SideCastlings castlings1, SideCastlings castlings2)
  { return static_cast<SideCastlings>(static_cast<int>(castlings1) & static_cast<int>(castlings2)); }

  inline SideCastlings operator&=(SideCastlings &castlings1, SideCastlings castlings2)
  { castlings1 = castlings1 & castlings2; return castlings1; }

  inline SideCastlings operator|(SideCastlings castlings1, SideCastlings castlings2)
  { return static_cast<SideCastlings>(static_cast<int>(castlings1) | static_cast<int>(castlings2)); }

  inline SideCastlings operator|=(SideCastlings &castlings1, SideCastlings castlings2)
  { castlings1 = castlings1 | castlings2; return castlings1; }

  inline SideCastlings operator^(SideCastlings castlings1, SideCastlings castlings2)
  { return static_cast<SideCastlings>(static_cast<int>(castlings1) ^ static_cast<int>(castlings2)); }

  inline SideCastlings operator^=(SideCastlings &castlings1, SideCastlings castlings2)
  { castlings1 = castlings1 ^ castlings2; return castlings1; }

  class Move
  {
    std::int8_t _M_piece;
    std::int8_t _M_from;
    std::int8_t _M_to;
    std::int8_t _M_promotion_piece;
  public:
    Move() {}
    
    Move(Piece piece, Square from, Square to, PromotionPiece promotion_piece) :
      _M_piece(static_cast<std::int8_t>(piece)), _M_from(from), _M_to(to), _M_promotion_piece(static_cast<std::int8_t>(promotion_piece)) {}

    const Piece piece() const
    { return static_cast<Piece>(_M_piece); }

    const Square from() const
    { return _M_from; }
    
    const Square to() const
    { return _M_to; }

    const PromotionPiece promotion_piece() const
    { return static_cast<PromotionPiece>(_M_promotion_piece); }
  };

  struct MovePair
  {
    Move move;
    int score;
  };

  class MovePairList
  {
    MovePair *_M_move_pairs;
    std::size_t _M_length;
  public:
    MovePairList() {}

    MovePairList(MovePair *move_pairs, std::size_t length) :
      _M_move_pairs(move_pairs), _M_length(length) {}

    std::size_t length() const
    { return  _M_length; }
    
    const MovePair &operator[](std::size_t i) const
    { return _M_move_pairs[i]; }

    void add_move_pair(const MovePair &move_pair)
    {
      _M_move_pairs[_M_length] = move_pair;
      _M_length++;
    }

    MovePairList to_next_list() const
    { return MovePairList(_M_move_pairs + _M_length, 0); } 
  };

  class Board
  {
    Bitboard _M_color_bitboards[2];
    Bitboard _M_piece_bitboards[6];
    int _M_king_squares[2];
    Side _M_side;
    SideCastlings _M_castlings[2];
    Column _M_en_passant_column;
    int _M_halfmove_clock;
    int _M_fullmove_number;
  public:
    Board();

    Bitboard color_bitboard(Side side) const
    { return _M_color_bitboards[side_to_index(side)]; }
    
    void set_color_bitboard(Side side, Bitboard bbd)
    { _M_color_bitboards[side_to_index(side)] = bbd; }

    Bitboard piece_bitboard(Piece piece) const
    { return _M_piece_bitboards[piece_to_index(piece)]; }

    void set_piece_bitboard(Piece piece, Bitboard bbd)
    { _M_piece_bitboards[piece_to_index(piece)] = bbd; }

    Square king_square(Side side) const
    { return _M_king_squares[side_to_index(side)]; }
    
    void set_king_square(Side side, Square squ)
    { _M_king_squares[side_to_index(side)] = squ; }

    Side side() const
    { return _M_side; }
    
    void set_side(Side side)
    { _M_side = side; }

    SideCastlings side_castlings(Side side) const
    { return _M_castlings[side_to_index(side)]; }

    void set_side_castling(Side side, SideCastlings side_castlings)
    { _M_castlings[side_to_index(side)] = side_castlings; }
    
    Column en_passant_column() const
    { return _M_en_passant_column; }
    
    void set_en_passant_column(Column col)
    { _M_en_passant_column = col; }

    int halfmove_clock() const
    { return _M_halfmove_clock; }

    void set_halfmove_clock(int halfmove_clock)
    { _M_halfmove_clock = halfmove_clock; }

    int fullmove_number() const
    { return _M_fullmove_number; }

    void set_fullmove_number(int fullmove_number)
    { _M_fullmove_number = fullmove_number; }

    bool has_color(Side side, Square squ) const
    { return (_M_color_bitboards[side_to_index(side)] & (static_cast<Bitboard>(1) << squ)) != 0; }

    Color color(Square squ) const
    {
      if((_M_color_bitboards[side_to_index(Side::WHITE)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return Color::WHITE;
      else if((_M_color_bitboards[side_to_index(Side::BLACK)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return Color::BLACK;
      else
        return Color::EMPTY;
    }

    void set_color(Square squ, Color color)
    {
      switch(color) {
        case Color::WHITE:
          _M_color_bitboards[side_to_index(Side::WHITE)] |= static_cast<Bitboard>(1) << squ;
          _M_color_bitboards[side_to_index(Side::BLACK)] &= ~(static_cast<Bitboard>(1) << squ);
          break;
        case Color::BLACK:
          _M_color_bitboards[side_to_index(Side::WHITE)] &= ~(static_cast<Bitboard>(1) << squ);
          _M_color_bitboards[side_to_index(Side::BLACK)] |= static_cast<Bitboard>(1) << squ;
          break;
        case Color::EMPTY:
          _M_color_bitboards[side_to_index(Side::WHITE)] &= ~(static_cast<Bitboard>(1) << squ);
          _M_color_bitboards[side_to_index(Side::BLACK)] &= ~(static_cast<Bitboard>(1) << squ);
          break;
      }
    }

    bool has_piece(Piece piece, Square squ) const
    { return (_M_piece_bitboards[piece_to_index(piece)] & (static_cast<Bitboard>(1) << squ)) != 0; }
    
    std::pair<Piece, bool> piece_pair(Square squ) const
    {
      if((_M_piece_bitboards[piece_to_index(Piece::PAWN)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return std::make_pair(Piece::PAWN, true);
      else if((_M_piece_bitboards[piece_to_index(Piece::KNIGHT)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return std::make_pair(Piece::KNIGHT, true);
      else if((_M_piece_bitboards[piece_to_index(Piece::BISHOP)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return std::make_pair(Piece::BISHOP, true);
      else if((_M_piece_bitboards[piece_to_index(Piece::ROOK)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return std::make_pair(Piece::ROOK, true);
      else if((_M_piece_bitboards[piece_to_index(Piece::QUEEN)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return std::make_pair(Piece::QUEEN, true);
      else if((_M_piece_bitboards[piece_to_index(Piece::KING)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return std::make_pair(Piece::KING, true);
      else
        return std::make_pair(Piece::PAWN, false);
    }

    void set_piece_pair(Square squ, std::pair<Piece, bool> piece_pair)
    {
      _M_piece_bitboards[piece_to_index(Piece::PAWN)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::KNIGHT)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::BISHOP)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::ROOK)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::QUEEN)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::KING)] &= ~(static_cast<Bitboard>(1) << squ);
      if(piece_pair.second) _M_piece_bitboards[piece_to_index(piece_pair.first)] |= static_cast<Bitboard>(1) << squ;
    }
    
    void set_piece(Square squ, Piece piece)
    {
      _M_piece_bitboards[piece_to_index(Piece::PAWN)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::KNIGHT)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::BISHOP)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::ROOK)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::QUEEN)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::KING)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(piece)] |= static_cast<Bitboard>(1) << squ;
    }

    void unset_piece(Square squ)
    {
      _M_piece_bitboards[piece_to_index(Piece::PAWN)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::KNIGHT)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::BISHOP)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::ROOK)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::QUEEN)] &= ~(static_cast<Bitboard>(1) << squ);
      _M_piece_bitboards[piece_to_index(Piece::KING)] &= ~(static_cast<Bitboard>(1) << squ);
    }

    bool has_attack(Side side, Square squ) const;
    
    bool in_check() const
    { return has_attack(_M_side, _M_king_squares[side_to_index(_M_side)]); } 

    void generate_pseudo_legal_moves(MovePairList &move_pairs) const;

    void generate_pseudo_legel_good_moves(MovePairList &move_pairs) const;

    bool make_move(Move move, Board &board) const;
  };
}

#endif
