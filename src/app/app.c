#include "app/app.h"

#include "core/opengl_loader/opengl_loader.h"
#include "core/window/window.h"

#include "renderer/shader.h"
#include "renderer/mesh.h"

#include "core/math/vectors.h"
#include "core/math/matrices.h"

void app_create(App* app) {
  window_create(&app->window, TITLE, WIDTH, HEIGHT);
  context_create(&app->context, app->window.hdc);
  create_capabilities();
}

Shader shader;
Mesh mesh;

Vec3 m_rot = (Vec3){0.0f, 0.0f, 0.0f}; 
Mat4 model, view, projection;

GLint model_loc; 
GLint view_loc;
GLint projection_loc;

void setup() {
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

  shader_create(&shader, "base.vert", "base.frag");
  mesh_create(&mesh, vertices, 7, sizeof(vertices), indices, 6, sizeof(indices));

  mesh_bind(&mesh);

  mesh_add_vertex_attribute(&mesh, 0, 3, (void*)0);
  mesh_add_vertex_attribute(&mesh, 1, 4, (void*)(3*sizeof(float)));

  mat4_perspective(45.0f, (float)1920/(float)1080, 0.01f, 100.0f, &projection);

  model_loc = gl.glGetUniformLocation(shader.program, "model");
  view_loc = gl.glGetUniformLocation(shader.program, "view");
  projection_loc = gl.glGetUniformLocation(shader.program, "projection");
}

void update() {
  m_rot.x += 0.01f;

  model = mat4_identity();
  mat4_translate((Vec3){0.0f, 0.0f, 0.0f}, &model);
  mat4_rotate(m_rot, &model);
  mat4_scale((Vec3){1.0f, 1.0f, 1.0f}, &model);

  view = mat4_identity();
  mat4_look_at((Vec3){0.0f, 0.0f, 3.0f}, (Vec3){0.0f, 0.0f, 0.0f}, (Vec3){0.0f, 1.0f, 0.0f}, &view);
}

void render() {
  gl.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gl.glUseProgram(shader.program);
  gl.glUniformMatrix4fv(model_loc, 1, GL_FALSE, model.m);
  gl.glUniformMatrix4fv(view_loc, 1, GL_FALSE, view.m);
  gl.glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection.m);
  mesh_draw(&mesh);
}

void app_run(App* app) {
  setup();

  while (1) {
    window_handle_messages();

    update();
    render();
    
    window_swap_buffers(&app->window);
  }
}

void app_destroy(App* app) {
  shader_destroy(&shader);
  mesh_destroy(&mesh);

  window_destroy(&app->window);
  context_destroy(&app->context);
}