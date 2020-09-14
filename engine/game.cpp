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
#include "game.hpp"

using namespace std;

namespace peacockspider
{
  Game::Game() :
    _M_result(Result::UNFINISHED)
  {}

  Game::Game(const string &event, const string &site, const string &date, const string &round, const string &white, const string &black, Result result, Board *board) :
    _M_event(event), _M_site(site), _M_date(date), _M_round(round), _M_white(white), _M_black(black), _M_result(result), _M_board(board) {}
 
  Game::Game(const string &event, const string &site, const string &date, const string &round, const string &white, const string &black, Result result, Board *board, const vector<Move> &moves) :
    _M_event(event), _M_site(site), _M_date(date), _M_round(round), _M_white(white), _M_black(black), _M_result(result), _M_board(board), _M_moves(moves) {}

  Game::~Game() {}
}
