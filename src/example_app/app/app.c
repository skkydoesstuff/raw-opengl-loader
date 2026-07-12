#include "example_app/app/app.h"

#include "core/opengl_loader/opengl_loader.h"
#include "core/window/window.h"
#include "core/math/radians.h"

#include "example_app/scene/camera.h"
#include "example_app/scene/model.h"

void app_create(App* app) {
  window_create(&app->window, TITLE, WIDTH, HEIGHT);
  context_create(&app->context, app->window.hdc);
  create_capabilities();
}

Shader* shader;
Mesh* mesh;

Camera* camera;

Model* model;

void setup(App* app) { //NOLINT
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
  model = malloc(sizeof(Model));

  shader_create(shader, "base.vert", "base.frag");
  mesh_create(mesh, vertices, 7, sizeof(vertices), indices, 6, sizeof(indices));
  camera_create(camera, 45.0f, (float)1920/(float)1080, 0.01f, (float)100.0f);
  model_create(mesh, model);

  camera->position = (Vec3){0.0f, 0.0f, 3.0f};

  mesh_bind(mesh);

  mesh_add_vertex_attribute(mesh, 0, 3, (void*)0);
  mesh_add_vertex_attribute(mesh, 1, 4, (void*)(3*sizeof(float)));
}

void update(App* app) {
  model->rotation.x += TO_RADIANS(90.0f) * app->window.time.delta_time;

  camera_update(camera);
}

void render(App* app) { //NOLINT
  gl.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader_bind(shader);

  shader_uniform_mat4(shader, "view", camera->view);
  shader_uniform_mat4(shader, "projection", camera->projection);
  model_draw(model, shader);
}

void app_run(App* app) {
  setup(app);

  while (1) {
    window_handle_messages(&app->window);

    update(app);
    render(app);
    
    window_swap_buffers(&app->window);
  }
}

void app_destroy(App* app) {
  shader_destroy(shader);
  mesh_destroy(mesh);

  free(shader);
  free(mesh);
  free(camera);
  free(model);

  window_destroy(&app->window);
  context_destroy(&app->context);
}