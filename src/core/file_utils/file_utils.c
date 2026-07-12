#include "core/file_utils/file_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "logging.h"

char* get_executable_path()
{
  char* exe_path = malloc(MAX_PATH);

  if (!exe_path) {
    print("Memory allocation failed");
    return NULL;
  }

  DWORD result = GetModuleFileNameA(NULL, exe_path, MAX_PATH);

  if (result == 0 || result == MAX_PATH) {
    print("Failed to get executable path");
    free(exe_path);
    return NULL;
  }

  char* last_backslash = strrchr(exe_path, '\\');

  if (last_backslash) {
    *last_backslash = '\0';
  }

  return exe_path;
}


char* read_file(const char* path)
{
  FILE* file = fopen(path, "rb");

  if (!file) {
    return NULL;
  }

  fseek(file, 0, SEEK_END);

  long size = ftell(file);

  if (size <= 0) {
    fclose(file);
    return NULL;
  }

  rewind(file);

  char* buffer = malloc((size_t)size + 1);

  if (!buffer) {
    fclose(file);
    return NULL;
  }

  size_t bytes_read = fread(buffer, 1, (size_t)size, file);

  if (bytes_read != (size_t)size) {
    free(buffer);
    fclose(file);
    return NULL;
  }

  buffer[size] = '\0';

  fclose(file);

  return buffer;
}