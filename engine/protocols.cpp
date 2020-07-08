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
#include "protocols.hpp"

using namespace std;

namespace peacockspider
{
  mutex output_mutex;

  void split_command_line(const string &cmd_line, string &cmd_name, string &arg_str)
  {
    auto iter = cmd_line.begin();
    while(iter != cmd_line.end() && (*iter == ' ' || *iter == '\t')) iter++;
    auto cmd_name_iter = iter;
    while(iter != cmd_line.end() && *iter != ' ' && *iter != '\t') iter++;
    cmd_name = string(cmd_name_iter, iter);
    while(iter != cmd_line.end() && (*iter == ' ' || *iter == '\t')) iter++;
    auto arg_str_iter = iter;
    arg_str = string(arg_str_iter, cmd_line.end());
  }

  void split_argument_string(const string &arg_str, vector<string> &args)
  {
    args.clear();
    auto iter = arg_str.begin();
    while(iter != arg_str.end()) {
      auto arg_iter = iter;
      while(iter != arg_str.end() && *iter != ' ' && *iter != '\t') iter++;
      args.push_back(string(arg_iter, iter));
      while(iter != arg_str.end() && (*iter == ' ' || *iter == '\t')) iter++;
    }
  }
}
