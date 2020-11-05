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
#include <atomic>
#include <cerrno>
#include <cstring>
#ifdef __unix__
#include <signal.h>
#endif
#ifdef __unix__
#include <stdio.h>
#include <unistd.h>
#else
#include <io.h>
#endif
#include "gen_alg_sig.hpp"

using namespace std;

namespace peacockspider
{
  namespace genalg
  {
    volatile sig_atomic_t is_genetic_algorithm_stop;

    namespace
    {
      void signal_handler(int sig_number)
      {
        const char *str = "Stopping ...\n";
#ifdef __unix__
        size_t len = strlen(str);
        ssize_t i = 0;
        while(i < static_cast<ssize_t>(len)) {
          ssize_t result = write(STDERR_FILENO, str + i, len - i);
          if(result == -1 && errno == EINTR) continue;
          i += result;
        }
#else
        unsigned len = strlen(str);
        int i = 0;
        while(i < static_cast<int>(len)) {
          int result = _write(2, str + i, len - i);
          if(result == -1 && errno == EINTR) continue;
          i += result;
        }
#endif
        is_genetic_algorithm_stop = 1;
        atomic_thread_fence(memory_order_seq_cst);
      }
    }
    
    void initialize_genetic_algorithm_signal()
    {
      is_genetic_algorithm_stop = 0;
      atomic_thread_fence(memory_order_seq_cst);
#ifdef __unix__
      struct sigaction action;
      action.sa_handler = signal_handler;
      sigemptyset(&(action.sa_mask));
      action.sa_flags = 0;
      sigaction(SIGINT, &action, nullptr);
#else
      signal(signal_handler);
#endif
    }
  }
}
