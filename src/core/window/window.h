#pragma once

#include <windows.h>

typedef struct {
  HWND hwnd;
  HDC hdc;
} Window;

int window_create(Window* window, HINSTANCE hInstance, const char* title, int width, int height);

void window_handle_messages();

void window_swap_buffers(Window* window);

void window_destroy(Window* window);