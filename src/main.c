#include <windows.h>

#include "opengl_loader/opengl_enums.h"
#include "window.h"
#include "opengl_loader/opengl_loader.h"

int WINAPI WinMain(
    HINSTANCE instance,
    HINSTANCE prev,
    LPSTR cmd,
    int show)
{
  Window window;

  if (!window_create(
      &window,
      instance,
      "Raw Renderer",
      1280,
      720))
    return 1;

  MSG msg;

  HGLRC context;
  create_context(&context, window.hdc);
  create_capabilities();
  
  gl.glViewport(0, 0, 1280, 720);

  float vertices[12] = {
    -0.5f, 0.5f, 0.0f,    // top left
     0.5f, 0.5f, 0.0f,    // top right
     0.5f, -0.5f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f    // bottom left
  };

  unsigned int indices[6] = {
    0, 1, 2,
    0, 3, 2
  };

  unsigned int VAO;
  gl.glGenVertexArrays(1, &VAO);
  gl.glBindVertexArray(VAO);

  unsigned int VBO;
  gl.glGenBuffers(1, &VBO);
  gl.glBindBuffer(GL_ARRAY_BUFFER, VBO);
  gl.glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int EBO;
  gl.glGenBuffers(1, &EBO);
  gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  gl.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  gl.glEnableVertexAttribArray(0);

  gl.glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  while (1) {
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT)
            return 0;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    gl.glClear(GL_COLOR_BUFFER_BIT);
    gl.glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    SwapBuffers(window.hdc);
  }

  gl.glDeleteVertexArrays(1, &VAO);

  destroy_context(&context);
  window_destroy(&window);

  return 0;
}