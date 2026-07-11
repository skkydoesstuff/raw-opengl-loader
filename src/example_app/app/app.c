#include "example_app/app/app.h"

#include "core/opengl_loader/opengl_loader.h"
#include "core/window/window.h"

#include "core/math/vectors.h"
#include "core/math/matrices.h"

#include "example_app/renderer/shader.h"
#include "example_app/renderer/mesh.h"
#include "example_app/scene/camera.h"

#include "logging.h"

void app_create(App* app) {
  window_create(&app->window, TITLE, WIDTH, HEIGHT);
  context_create(&app->context, app->window.hdc);
  create_capabilities();
}

Shader* shader;
Mesh* mesh;

Camera* camera;

Vec3 m_rot = (Vec3){0.0f, 0.0f, 0.0f};
Vec3 m_pos = (Vec3){0.0f, 0.0f, 0.0f};
Mat4 model;

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

  shader = malloc(sizeof(Shader));
  mesh = malloc(sizeof(Mesh));
  camera = malloc(sizeof(Camera));

  shader_create(shader, "base.vert", "base.frag");
  mesh_create(mesh, vertices, 7, sizeof(vertices), indices, 6, sizeof(indices));
  camera_create(camera, 45.0f, (float)1920/(float)1080, 0.01f, (float)100.0f);

  camera->position = (Vec3){0.0f, 0.0f, 3.0f};

  mesh_bind(mesh);

  my_print("%f\n", camera->position.z);

  mesh_add_vertex_attribute(mesh, 0, 3, (void*)0);
  mesh_add_vertex_attribute(mesh, 1, 4, (void*)(3*sizeof(float)));
}

void update() {
  m_rot.x += 0.01f;

  model = mat4_identity();
  mat4_translate(m_pos, &model);
  mat4_rotate(m_rot, &model);
  mat4_scale((Vec3){1.0f, 1.0f, 1.0f}, &model);

  camera_update(camera);
}

void render() {
  gl.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader_bind(shader);

  shader_uniform_mat4(shader, "model", model);
  shader_uniform_mat4(shader, "view", camera->view);
  shader_uniform_mat4(shader, "projection", camera->projection);
  mesh_draw(mesh);
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
  shader_destroy(shader);
  mesh_destroy(mesh);

  free(shader);
  free(mesh);

  window_destroy(&app->window);
  context_destroy(&app->context);
}