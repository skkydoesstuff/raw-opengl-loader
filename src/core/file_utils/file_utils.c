#include "core/file_utils/file_utils.h"

#include <windows.h>
#include <stdio.h>

#include "error.h"

char* get_executable_path() {
  char* exePath = malloc(MAX_PATH);
  if (!exePath) {
    LOG("Memory allocation failed");
  }

  DWORD result = GetModuleFileName(NULL, exePath, MAX_PATH);
  if (result == 0 || result == MAX_PATH) {
    LOG("Failed to get executable path");
    free(exePath);
  }

  char* last_backslash = strrchr(exePath, '\\');
  if (last_backslash) {
    *last_backslash = '\0';
  }

  return exePath;
}

char* read_file(const char* path) {
  FILE* file = fopen(path, "rb");
  if (!file) {
    LOG("Failed to open file");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);

  if (file_size <= 0) {
    LOG("Invalid file size");
    fclose(file);
    return NULL;
  }

  char* buffer = (char*)malloc(file_size + 1);
  if (!buffer) {
    LOG("Failed to allocate memory for buffer!");
    fclose(file);
    return NULL;
  }

  size_t bytes_read = fread(buffer, 1, file_size, file);
  if (bytes_read != file_size) {
    LOG("Error reading file");
    free(buffer);
    fclose(file);
    return NULL;
  }

  buffer[file_size] = '\0';
  fclose(file);

  return buffer;
}