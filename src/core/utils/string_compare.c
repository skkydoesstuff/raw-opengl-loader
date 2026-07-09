#include "core/utils/string_compare.h"

int string_compare(const char* a, const char* b) {
  while (*a && *b) {
    if (*a != *b) {
      return 0;
    }

    a++;
    b++;
  }

  return *a == *b;
}