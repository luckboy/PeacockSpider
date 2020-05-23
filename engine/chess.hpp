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
#include <string>
#include <utility>
#include "consts.hpp"
#include "exception.hpp"
#include "types.hpp"

namespace peacockspider
{
  class Board;
  class MovePairList;

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

  inline bool equal_for_promotion(PromotionPiece promotion_piece1, PromotionPiece promotion_piece2)
  {
    if(promotion_piece1 == PromotionPiece::QUEEN)
      return promotion_piece2 == PromotionPiece::QUEEN ||
        promotion_piece2 == PromotionPiece::ROOK ||
        promotion_piece2 == PromotionPiece::BISHOP;
    else
      return promotion_piece1 == promotion_piece2;
  }

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

  class CANMove
  {
    Square _M_from;
    Square _M_to;
    PromotionPiece _M_promotion_piece;
  public:
    CANMove() {}

    CANMove(Square from, Square to, PromotionPiece promotion_piece) :
      _M_from(from), _M_to(to), _M_promotion_piece(promotion_piece) {}

    explicit CANMove(const std::string &str);
      
    bool operator==(const CANMove &move) const
    {
      return _M_from == move._M_from &&
        _M_to == move._M_to &&
        _M_promotion_piece == move._M_promotion_piece;
    }

    bool operator!=(const CANMove &move) const
    { return !(*this == move); }
    
    Square from() const
    { return _M_from; }

    void set_from(Square from)
    { _M_from = from; }

    Square to() const
    { return _M_to; }

    void set_to(Square to)
    { _M_to = to; }

    PromotionPiece promotion_piece() const
    { return _M_promotion_piece; }
    
    void set_promotion_piece(PromotionPiece promotion_piece)
    { _M_promotion_piece = promotion_piece; }
  private:
    bool unsafely_set(const std::string &str);
  public:
    bool set(const std::string &str);

    std::string to_string() const;
  };

  enum class SANMoveFlags
  {
    NONE = 0,
    CAPTURE = 1,
    SHORT_CASTLING = 2,
    LONG_CASTLING = 4,
    CHECK = 8,
    CHECKMATE = 16
  };

  inline SANMoveFlags operator~(SANMoveFlags flags)
  { return static_cast<SANMoveFlags>(static_cast<int>(flags) ^ 31); }

  inline SANMoveFlags operator&(SANMoveFlags flags1, SANMoveFlags flags2)
  { return static_cast<SANMoveFlags>(static_cast<int>(flags1) & static_cast<int>(flags2)); }

  inline SANMoveFlags operator&=(SANMoveFlags &flags1, SANMoveFlags flags2)
  { flags1 = flags1 & flags2; return flags1; }

  inline SANMoveFlags operator|(SANMoveFlags flags1, SANMoveFlags flags2)
  { return static_cast<SANMoveFlags>(static_cast<int>(flags1) | static_cast<int>(flags2)); }

  inline SANMoveFlags operator|=(SANMoveFlags &flags1, SANMoveFlags flags2)
  { flags1 = flags1 | flags2; return flags1; }
  
  inline SANMoveFlags operator^(SANMoveFlags flags1, SANMoveFlags flags2)
  { return static_cast<SANMoveFlags>(static_cast<int>(flags1) ^ static_cast<int>(flags2)); }

  inline SANMoveFlags operator^=(SANMoveFlags &flags1, SANMoveFlags flags2)
  { flags1 = flags1 ^ flags2; return flags1; }

  class SANMove
  {
    Piece _M_piece;
    Column _M_from_column;
    Row _M_from_row;
    Square _M_to;
    PromotionPiece _M_promotion_piece;
    SANMoveFlags _M_flags;
  public:
    SANMove() {}
    
    SANMove(Piece piece, Column from_col, Row from_row, Square to, PromotionPiece promotion_piece, SANMoveFlags flags) :
      _M_piece(piece), _M_from_column(from_col), _M_from_row(from_row), _M_to(to), _M_promotion_piece(promotion_piece), _M_flags(flags) {}
      
    SANMove(bool is_short_castling) :
      _M_piece(Piece::KING), _M_from_column(-1), _M_from_row(-1), _M_to(-1), _M_promotion_piece(PromotionPiece::NONE),
      _M_flags(is_short_castling ? SANMoveFlags::SHORT_CASTLING : SANMoveFlags::LONG_CASTLING) {}

    explicit SANMove(const std::string &str);

    bool operator==(const SANMove &move) const
    {
      return _M_piece == move._M_piece &&
        _M_from_column == move._M_from_column &&
        _M_from_row == move._M_from_row &&
        _M_to == move._M_to &&
        _M_promotion_piece == move._M_promotion_piece &&
        _M_flags == move._M_flags;
    }

    bool operator!=(const SANMove &move) const
    { return !(*this == move); }

    Piece piece() const
    { return _M_piece; }

    void set_piece(Piece piece)
    { _M_piece = piece; }

    Column from_column() const
    { return _M_from_column; }

    void set_from_column(Column from_col)
    { _M_from_column = from_col; }

    Row from_row() const
    { return _M_from_row; }

    void set_from_row(Row from_row)
    { _M_from_row = from_row; }

    Square to() const
    { return _M_to; }

    void set_to(Square to)
    { _M_to = to; }

    PromotionPiece promotion_piece() const
    { return _M_promotion_piece; }

    void set_promotion_piece(PromotionPiece promotion_piece)
    { _M_promotion_piece = promotion_piece; }

    SANMoveFlags flags() const
    { return _M_flags; }

    void set_flags(SANMoveFlags flags)
    { _M_flags = flags; }
  private:
    bool unsafely_set(const std::string &str);
  public:
    bool set(const std::string &str);

    std::string to_string() const;
  };
  
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

    Move(const CANMove &move, const Board &board, MovePairList &move_pairs);

    Move(const SANMove &move, const Board &board, MovePairList &move_pairs);

    Move(const std::string &str, const Board &board, MovePairList &move_pairs, bool is_can = true);

    bool operator==(const Move &move) const
    {
      return _M_piece == move._M_piece &&
        _M_from == move._M_from &&
        _M_to == move._M_to &&
        _M_promotion_piece == move._M_promotion_piece;
    }

    bool operator!=(const Move &move) const
    { return !(*this == move); }
    
    bool equal_for_promotion(const Move &move) const
    {
      return _M_piece == move._M_piece &&
        _M_from == move._M_from &&
        _M_to == move._M_to &&
        ::peacockspider::equal_for_promotion(static_cast<PromotionPiece>(_M_promotion_piece), static_cast<PromotionPiece>(move._M_promotion_piece));
    }

    const Piece piece() const
    { return static_cast<Piece>(_M_piece); }
    
    void set_piece(Piece piece)
    { _M_piece = static_cast<std::int8_t>(piece); }

    const Square from() const
    { return _M_from; }
    
    void set_from(Square from)
    { _M_from = from; }
    
    const Square to() const
    { return _M_to; }

    void set_to(Square to)
    { _M_to = to; }

    const PromotionPiece promotion_piece() const
    { return static_cast<PromotionPiece>(_M_promotion_piece); }

    void set_promotion_piece(PromotionPiece promotion_piece)
    { _M_promotion_piece = static_cast<std::int8_t>(promotion_piece); }
    
    bool is_capture(const Board &board) const;

    bool is_check(const Board &board) const;

    bool is_checkmate(const Board &board, MovePairList &move_pairs) const;

    bool set_can(const CANMove &move, const Board &board, MovePairList &move_pairs);

    bool set_can(const std::string &str, const Board &board, MovePairList &move_pairs)
    {
      CANMove tmp_move;
      if(!tmp_move.set(str)) return false;
      return set_can(tmp_move, board, move_pairs);
    }

    bool set_san(const SANMove &move, const Board &board, MovePairList &move_pairs);
  
    bool set_san(const std::string &str, const Board &board, MovePairList &move_pairs)
    {
      SANMove tmp_move;
      if(!tmp_move.set(str)) return false;
      return set_san(tmp_move, board, move_pairs);
    }

    CANMove to_can_move() const;

    SANMove to_san_move(const Board &board, MovePairList &move_pairs) const;
    
    std::string to_string() const
    { return to_can_move().to_string(); }
    
    std::string to_string(const Board &board, MovePairList &move_pairs) const
    { return to_san_move(board, move_pairs).to_string(); }
  };

  struct MovePair
  {
    Move move;
    int score;
    
    MovePair() {}

    explicit MovePair(Move move) :
      move(move) {}

    MovePair(Move move, int score) :
      move(move), score(score) {}
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
    
    MovePair &operator[](std::size_t i)
    { return _M_move_pairs[i]; }
    
    void clear()
    { _M_length = 0; }

    void add_move_pair(const MovePair &move_pair)
    {
      _M_move_pairs[_M_length] = move_pair;
      _M_length++;
    }

    bool contain_move(Move move) const;

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

    explicit Board(const std::string &str);
    
    bool operator==(const Board &board) const
    {
      return equal_for_repetitions(board) &&
        _M_halfmove_clock == board._M_halfmove_clock &&
        _M_fullmove_number == board._M_fullmove_number;
    }

    bool operator!=(const Board &board) const
    { return !(*this == board); }

    bool equal_for_repetitions(const Board &board) const;
    
    Bitboard color_bitboard(Side side) const
    { return _M_color_bitboards[side_to_index(side)]; }
    
    void set_color_bitboard(Side side, Bitboard bbd)
    { _M_color_bitboards[side_to_index(side)] = bbd; }
    
    void and_color_bitboard(Side side, Bitboard bbd)
    { _M_color_bitboards[side_to_index(side)] &= bbd; }

    void or_color_bitboard(Side side, Bitboard bbd)
    { _M_color_bitboards[side_to_index(side)] |= bbd; }

    void xor_color_bitboard(Side side, Bitboard bbd)
    { _M_color_bitboards[side_to_index(side)] ^= bbd; }

    Bitboard piece_bitboard(Piece piece) const
    { return _M_piece_bitboards[piece_to_index(piece)]; }

    void set_piece_bitboard(Piece piece, Bitboard bbd)
    { _M_piece_bitboards[piece_to_index(piece)] = bbd; }

    void and_piece_bitboard(Piece piece, Bitboard bbd)
    { _M_piece_bitboards[piece_to_index(piece)] &= bbd; }

    void or_piece_bitboard(Piece piece, Bitboard bbd)
    { _M_piece_bitboards[piece_to_index(piece)] |= bbd; }

    void xor_piece_bitboard(Piece piece, Bitboard bbd)
    { _M_piece_bitboards[piece_to_index(piece)] ^= bbd; }

    void or_piece_bitboard(PromotionPiece promotion_piece, Bitboard bbd)
    { _M_piece_bitboards[promotion_piece_to_index(promotion_piece)] |= bbd; }

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

    void set_side_castlings(Side side, SideCastlings side_castlings)
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
    
    bool has_empty(Square squ) const
    { return ((_M_color_bitboards[side_to_index(Side::WHITE)] | _M_color_bitboards[side_to_index(Side::BLACK)]) & (static_cast<Bitboard>(1) << squ)) == 0; }

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
    
    bool has_piece(Piece piece1, Piece piece2, Square squ) const
    { return ((_M_piece_bitboards[piece_to_index(piece1)] | _M_piece_bitboards[piece_to_index(piece2)]) & (static_cast<Bitboard>(1) << squ)) != 0; }
    
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

    Piece piece(Square squ) const
    {
      if((_M_piece_bitboards[piece_to_index(Piece::PAWN)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return Piece::PAWN;
      else if((_M_piece_bitboards[piece_to_index(Piece::KNIGHT)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return Piece::KNIGHT;
      else if((_M_piece_bitboards[piece_to_index(Piece::BISHOP)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return Piece::BISHOP;
      else if((_M_piece_bitboards[piece_to_index(Piece::ROOK)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return Piece::ROOK;
      else if((_M_piece_bitboards[piece_to_index(Piece::QUEEN)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return Piece::QUEEN;
      else if((_M_piece_bitboards[piece_to_index(Piece::KING)] & (static_cast<Bitboard>(1) << squ)) != 0)
        return Piece::KING;
      else
        return Piece::PAWN;
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

    bool has_color_piece(Side side, Piece piece, Square squ) const
    { return (_M_color_bitboards[side_to_index(side)] & _M_piece_bitboards[piece_to_index(piece)] & (static_cast<Bitboard>(1) << squ)) != 0; }

    bool has_color_piece(Side side, Piece piece1, Piece piece2, Square squ) const
    { return (_M_color_bitboards[side_to_index(side)] & (_M_piece_bitboards[piece_to_index(piece1)] | _M_piece_bitboards[piece_to_index(piece2)]) & (static_cast<Bitboard>(1) << squ)) != 0; }

    bool has_attack(Side side, Square squ) const;
    
    bool in_check() const
    { return has_attack(_M_side, _M_king_squares[side_to_index(_M_side)]); } 

    bool in_check(Side side) const
    { return has_attack(side, _M_king_squares[side_to_index(side)]); }
    
    void generate_pseudolegal_moves(MovePairList &move_pairs) const;

    void generate_pseudolegal_good_moves(MovePairList &move_pairs) const;

    bool make_move(Move move, Board &board) const;

    bool has_legal_move(Move move) const;

    bool in_checkmate(MovePairList &move_pairs) const;
    
    bool in_stalemate(MovePairList &move_pairs) const;
  private:
    bool unsafely_set(const std::string &str);
  public:
    bool set(const std::string &str);

    std::string to_string() const;
  };
  
  Square string_to_square(const std::string &str);

  std::string square_to_string(Square squ);

  Column char_to_column(char c);

  char column_to_char(Column col);

  Row char_to_row(char c);

  char row_to_char(Row row);

  std::pair<Side, bool> char_to_side_pair(char c);

  char side_to_char(Side side);

  std::pair<Piece, bool> char_to_piece_pair(char c);

  char piece_to_char(Piece piece);

  PromotionPiece char_to_promotion_piece(char c);

  char promotion_piece_to_char(PromotionPiece promotion_piece);

  bool is_column_char(char c);

  bool is_row_char(char c);
}

#endif
