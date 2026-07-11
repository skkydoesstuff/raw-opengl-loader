#pragma once

#include <windows.h>

static void ftoa(float value, char* buffer, int precision) {
  int pos = 0;
  
  // Handle negative
  if (value < 0) {
    buffer[pos++] = '-';
    value = -value;
  }
  
  // Integer part
  int integer = (int)value;
  int divisor = 1;
  int temp = integer;
  while (temp >= 10) {
    divisor *= 10;
    temp /= 10;
  }
  
  if (integer == 0) {
    buffer[pos++] = '0';
  } else {
    while (divisor > 0) {
      buffer[pos++] = '0' + (integer / divisor);
      integer %= divisor;
      divisor /= 10;
    }
  }
  
  // Decimal part
  buffer[pos++] = '.';
  value -= (int)value;
  
  for (int i = 0; i < precision; i++) {
    value *= 10;
    int digit = (int)value;
    buffer[pos++] = '0' + digit;
    value -= digit;
  }
  
  buffer[pos] = '\0';
}

static void _format_print(const char* format, const char* value_str) {
  char buffer[1024];
  char* ptr = buffer;
  const char* fmt = format;
  const char* vptr = value_str;
  
  while (*fmt && ptr - buffer < 1023) {
    if (*fmt == '%' && *(fmt + 1)) {
      fmt++;
      if (*fmt == 'f' || *fmt == 'd' || *fmt == 's') {
        const char* s = vptr;
        while (*s && ptr - buffer < 1023) {
          *ptr++ = *s++;
        }
        fmt++;
      } else {
        *ptr++ = '%';
      }
    } else {
      *ptr++ = *fmt++;
    }
  }
  *ptr = '\0';
  
  DWORD length = (DWORD)(ptr - buffer);
  if (length > 0) {
    DWORD written = 0;
    HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (stdoutHandle != INVALID_HANDLE_VALUE && stdoutHandle != NULL) {
      WriteFile(stdoutHandle, buffer, length, &written, NULL);
    } else {
      OutputDebugStringA(buffer);
    }
  }
}

#define LOG(msg)                                                          \
  do {                                                                    \
    char _log_buffer[1024];                                               \
    wsprintfA(_log_buffer, "%s:%d\n\n%s",                             \
              __FILE__, __LINE__, (msg));                                 \
    MessageBoxA(NULL, _log_buffer, "Log", MB_OK | MB_ICONERROR);          \
  } while (0)

#define my_print(format, value)                                            \
  do {                                                                    \
    char _temp_str[128];                                                  \
    ftoa((float)(value), _temp_str, 6);                                   \
    _format_print((format), _temp_str);                                   \
  } while (0)

