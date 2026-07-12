#pragma once

#include <windows.h>

#include "core/window/time.h"

typedef struct {
  HWND hwnd;
  HDC hdc;

  Time time;
} Window;

int window_create(Window* window, const char* title, int width, int height);

void window_handle_messages(Window* window);

void window_swap_buffers(Window* window);

void window_destroy(Window* window);