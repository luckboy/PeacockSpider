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
#include "tournament.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    TournamentResult::TournamentResult(size_t player_count)
      : _M_player_count(player_count)
    {
      _M_scores.resize(_M_player_count);
      _M_sorted_player_indices.resize(_M_player_count);
      _M_crosstable.resize(_M_player_count);
      for(size_t i = 0; i < _M_player_count; i++) {
        _M_crosstable[i].resize(_M_player_count);
      }
      clear();
    }

    TournamentResult::~TournamentResult() {}
    
    void TournamentResult::clear()
    {
      for(size_t i = 0; i < _M_player_count; i++) {
        _M_scores[i] = 0;
      }
      for(size_t i = 0; i < _M_player_count; i++) {
        _M_sorted_player_indices[i] = i;
      }
      for(size_t i = 0; i < _M_player_count; i++) {
        for(size_t j = 0; j < _M_player_count; j++) {
          _M_crosstable[i][j].scores[0] = 0;
          _M_crosstable[i][j].scores[1] = 0;
        }
      }
    }
    
    void TournamentResult::set_game_result(size_t player1, size_t player2, size_t match_game_index, Result result)
    {
      int score, opp_score;
      if(match_game_index == 0) {
        switch(result) {
          case Result::WHITE_WIN:
            score = 2;
            opp_score = 0;
            break;
          case Result::BLACK_WIN:
            score = 0;
            opp_score = 2;
            break;
          default:
            score = 1;
            opp_score = 1;
            break;
        }
      } else {
        switch(result) {
          case Result::WHITE_WIN:
            score = 0;
            opp_score = 2;
            break;
          case Result::BLACK_WIN:
            score = 2;
            opp_score = 0;
            break;
          default:
            score = 1;
            opp_score = 1;
            break;
        }
      }
      _M_scores[player1] += score;
      _M_scores[player2] += opp_score;
      _M_crosstable[player1][player2].scores[match_game_index] = score;
      _M_crosstable[player2][player1].scores[match_game_index] = opp_score;
    }
    
    void TournamentResult::sort_player_indices()
    {
      sort(_M_sorted_player_indices.begin(), _M_sorted_player_indices.end(), [this](size_t index1, size_t index2) {
        return _M_scores[index1] > _M_scores[index2];
      });
    }
  }
}
