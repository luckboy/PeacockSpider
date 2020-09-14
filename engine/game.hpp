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
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include "chess.hpp"

namespace peacockspider
{
  class Game
  {
    std::string _M_event;
    std::string _M_site;
    std::string _M_date;
    std::string _M_round;
    std::string _M_white;
    std::string _M_black;
    Result _M_result;
    std::unique_ptr<Board> _M_board;
    std::vector<Move> _M_moves;
  public:
    Game();

    Game(const std::string &event, const std::string &site, const std::string &date, const std::string &round, const std::string &white, const std::string &black, Result result, Board *board = nullptr); 
 
    Game(const std::string &event, const std::string &site, const std::string &date, const std::string &round, const std::string &white, const std::string &black, Result result, Board *board, const std::vector<Move> &moves);

    Game(const Game &game);

    ~Game();

    Game &operator=(const Game &game);

    const std::string &event() const
    { return _M_event; }

    void set_event(const std::string &event)
    { _M_event = event; }

    const std::string &site() const
    { return _M_site; }

    void set_site(const std::string &site)
    { _M_site = site; }

    const std::string &date() const
    { return _M_date; }

    void set_date(const std::string &date)
    { _M_date = date; }

    const std::string &round() const
    { return _M_round; }

    void set_round(const std::string &round)
    { _M_round = round; }

    const std::string &white() const
    { return _M_white; }

    void set_white(const std::string &white)
    { _M_white = white; }

    const std::string &black() const
    { return _M_black; }

    void set_black(const std::string &black)
    { _M_black = black; }

    Result result() const
    { return _M_result; }

    void set_result(Result result)
    { _M_result = result; }

    const Board *board() const
    { return _M_board.get(); }

    void set_board(Board *board)
    { _M_board = std::unique_ptr<Board>(board); }

    const std::vector<Move> &moves() const
    { return _M_moves; }

    std::vector<Move> &moves()
    { return _M_moves; }
  };

  std::ostream &write_pgn(std::ostream &os, const Game &game);
}
