#include <windows.h>

#include "core/opengl_loader/opengl_enums.h"
#include "core/opengl_loader/opengl_loader.h"
#include "core/window/window.h"

#include "renderer/mesh.h"
#include "renderer/shader.h"

#include "core/math/matrices.h"

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
  
  gl.glEnable(GL_DEPTH_TEST);
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

  Mat4 model, view, projection;

  model = mat4_identity();
  mat4_translate((Vec3){0.0f, 0.0f, 0.0f}, &model);
  mat4_rotate((Vec3){0.0f, 0.0f, 0.0f}, &model);
  mat4_scale((Vec3){1.0f, 1.0f, 1.0f}, &model);

  mat4_look_at((Vec3){0.0f, 0.0f, 3.0f}, (Vec3){0.0f, 0.0f, 0.0f}, (Vec3){0.0f, 1.0f, 0.0f}, &view);

  mat4_perspective(45.0f, (float)1920/(float)1080, 0.01f, 100.0f, &projection);

  GLint model_loc = gl.glGetUniformLocation(shader.program, "model");
  GLint view_loc = gl.glGetUniformLocation(shader.program, "view");
  GLint projection_loc = gl.glGetUniformLocation(shader.program, "projection");

  while (1) {
    window_handle_messages();

    gl.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl.glUseProgram(shader.program);
    gl.glUniformMatrix4fv(model_loc, 1, GL_FALSE, model.m);
    gl.glUniformMatrix4fv(view_loc, 1, GL_FALSE, view.m);
    gl.glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection.m);
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