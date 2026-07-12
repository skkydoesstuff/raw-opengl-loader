#include "core/file_utils/file_utils.h"

#include <windows.h>

#include "logging.h"

char* get_executable_path() {
  char* exePath = malloc(MAX_PATH);
  if (!exePath) {
    print("Memory allocation failed");
  }

  DWORD result = GetModuleFileName(NULL, exePath, MAX_PATH);
  if (result == 0 || result == MAX_PATH) {
    print("Failed to get executable path");
    free(exePath);
  }

  char* last_backslash = strrchr(exePath, '\\');
  if (last_backslash) {
    *last_backslash = '\0';
  }

  return exePath;
}

char* read_file(const char* path) {
  HANDLE file = CreateFileA(
    path,
    GENERIC_READ,
    FILE_SHARE_READ,
    NULL,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    NULL
  );

  if (file == INVALID_HANDLE_VALUE) {
    return NULL;
  }

  LARGE_INTEGER size;
  if (!GetFileSizeEx(file, &size) || size.QuadPart <= 0) {
    CloseHandle(file);
    return NULL;
  }

  char* buffer = malloc((size_t)size.QuadPart + 1);
  if (!buffer) {
    CloseHandle(file);
    return NULL;
  }

  DWORD bytes_read;
  if (!ReadFile(file, buffer, (DWORD)size.QuadPart, &bytes_read, NULL) ||
    bytes_read != (DWORD)size.QuadPart) {
    free(buffer);
    CloseHandle(file);
    return NULL;
  }

  buffer[size.QuadPart] = '\0';

  CloseHandle(file);
  return buffer;
}