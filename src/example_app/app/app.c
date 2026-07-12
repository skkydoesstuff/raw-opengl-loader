#include "example_app/app/app.h"

#include "core/opengl_loader/opengl_loader.h"
#include "core/window/window.h"

#include "example_app/resource_manager.h"
#include "example_app/scene/camera.h"
#include "example_app/scene/model.h"

#include <malloc.h>


void app_create(App* app) {
  window_create(&app->window, TITLE, WIDTH, HEIGHT);
  context_create(&app->context, app->window.hdc);
  create_capabilities();
}

ResourceManager* rm;

#define NEW(type, var, ctor, ...) \
  type* var = malloc(sizeof(type)); \
  ctor(var, ##__VA_ARGS__)

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

  rm = malloc(sizeof(ResourceManager));
  rm_create(rm);

  NEW(Shader, shader, shader_create, "base.vert", "base.frag");
  NEW(Mesh, mesh, mesh_create, vertices, 7, sizeof(vertices), indices, 6, sizeof(indices));
  NEW(Camera, camera, camera_create, 45.0f, (float)1920/(float)1080, 0.01f, (float)100.0f);
  NEW(Model, model, model_create, mesh);

  rm_add_item(rm, RESOURCE_SHADER, "base_shader", shader);
  rm_add_item(rm, RESOURCE_MESH,   "base_mesh",   mesh);
  rm_add_item(rm, RESOURCE_CAMERA, "base_camera", camera);
  rm_add_item(rm, RESOURCE_MODEL,  "base_model",  model);

  camera->position = (Vec3){0.0f, 0.0f, 3.0f};

  mesh_bind(mesh);

  mesh_add_vertex_attribute(mesh, 0, 3, (void*)0);
  mesh_add_vertex_attribute(mesh, 1, 4, (void*)(3*sizeof(float)));
}

void update(App* app) { //NOLINT
  Camera* camera = (Camera*)rm_get_item(rm, "base_camera")->data;

  camera_update(camera);
}

void render(App* app) { //NOLINT
  Shader* shader = (Shader*)rm_get_item(rm, "base_shader")->data;
  Camera* camera = (Camera*)rm_get_item(rm, "base_camera")->data;
  Model* model = (Model*)rm_get_item(rm, "base_model")->data;

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
  rm_destroy(rm);

  window_destroy(&app->window);
  context_destroy(&app->context);
}