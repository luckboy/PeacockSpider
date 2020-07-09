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
#ifndef _PROTOCOLS_HPP
#define _PROTOCOLS_HPP

#include <iostream>
#include "engine.hpp"

namespace peacockspider
{
  extern const char *input_prefix;
  extern const char *output_prefix;
  extern const char *board_prefix;

  extern std::mutex output_mutex;

  void split_command_line(const std::string &cmd_line, std::string &cmd_name, std::string &arg_str);

  void split_argument_string(const std::string &arg_str, std::vector<std::string> &args);
  
  void unsafely_print_line(std::ostream *ols, const std::string &str);

  void print_line(std::ostream *ols, const std::string &str);

  bool xboard_loop(Engine *engine, std::ostream *ols, std::function<std::pair<bool, bool> (Engine *, const std::string &, std::ostream *)> fun);

  std::pair<bool, bool> uci_loop(Engine *engine, const std::string &first_cmd_line, std::ostream *ols);
}

#endif
