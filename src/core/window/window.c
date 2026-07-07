#include "window.h"
#include <minwindef.h>

static const char CLASS_NAME[] = "raw_renderer";

static LRESULT CALLBACK wnd_proc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int window_create(
    Window *window,
    const char *title,
    int width,
    int height)
{
  HINSTANCE instance = GetModuleHandle(NULL);

  WNDCLASSEX wc = {
        .cbSize = sizeof(wc),
        .lpfnWndProc = wnd_proc,
        .hInstance = instance,
        .lpszClassName = CLASS_NAME,
        .hCursor = LoadCursor(NULL, IDC_ARROW),
    };

    RegisterClassEx(&wc);

    window->hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        title,
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        NULL,
        NULL,
        instance,
        NULL);

    if (!window->hwnd)
        return 0;

    window->hdc = GetDC(window->hwnd);

    ShowWindow(window->hwnd, SW_SHOW);

    return 1;
}

void window_handle_messages() {
  MSG msg;

  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    if (msg.message == WM_QUIT)
      exit(0);

    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

void window_swap_buffers(Window *window) {
  SwapBuffers(window->hdc);
}

void window_destroy(Window *window)
{
    ReleaseDC(window->hwnd, window->hdc);
    DestroyWindow(window->hwnd);
}