#pragma once

#include <windows.h>

#define LOG(msg)                                                          \
  do {                                                                  \
    char _log_buffer[1024];                                           \
    wsprintfA(_log_buffer, "%s:%d\n\n%s",                             \
              __FILE__, __LINE__, (msg));                             \
    MessageBoxA(NULL, _log_buffer, "Log", MB_OK | MB_ICONERROR);      \
  } while (0)

