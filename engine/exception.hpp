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
#ifndef _EXCEPTION_HPP
#define _EXCEPTION_HPP

#include <exception>
#include <string>

namespace peacockspider
{
  class Exception : std::exception
  {
    std::string _M_message;
  public:
    explicit Exception(const std::string &msg) throw() : _M_message(msg) {}

    virtual ~Exception() throw();

    virtual const char *what() const throw();
  };
}

#endif
