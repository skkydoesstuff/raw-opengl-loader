#include <windows.h>

#include "core/opengl_loader/opengl_loader.h"
#include "core/window/window.h"

#include "renderer/mesh.h"
#include "renderer/shader.h"

#include <windows.h>

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
  
  HGLRC context;
  create_context(&context, window.hdc);
  create_capabilities();
  
  gl.glViewport(0, 0, 1280, 720);

  Shader shader = {0};
  shader_create(&shader, "base.vert", "base.frag");

  float vertices[28] = {
    -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,  // top left
      0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,  // top right
      0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f   // bottom left
  };

  unsigned int indices[6] = {
    0, 1, 2,
    0, 3, 2
  };

  Mesh mesh = {0};
  mesh_create(&mesh, vertices, 4, sizeof(vertices), indices, 6, sizeof(indices));

  gl.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
  gl.glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
  gl.glEnableVertexAttribArray(0);
  gl.glEnableVertexAttribArray(1);

  gl.glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  while (1) {
    window_handle_messages();

    gl.glClear(GL_COLOR_BUFFER_BIT);
    gl.glUseProgram(shader.program);
    mesh_draw(&mesh);

    window_swap_buffers(&window);
  }

  gl.glDeleteProgram(shader.program);

  shader_destroy(&shader);
  mesh_destroy(&mesh);

  destroy_context(&context);
  window_destroy(&window);

  return 0;
}