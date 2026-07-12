#pragma once

#ifdef DEBUG

#include <stdio.h>
#include <stdarg.h>

static inline void debug_print(const char* format, ...) {
  va_list args;
  va_start(args, format);

  vprintf(format, args);

  va_end(args);
}

#define print(...) debug_print(__VA_ARGS__)

#else

#define print(...)

#endif