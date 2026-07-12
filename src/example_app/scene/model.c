#include "example_app/scene/model.h"
#include "core/math/matrices.h"

void model_create(Model* model, Mesh* mesh) {
  model->mesh = mesh;
  model->position = VEC3_ZERO;
  model->rotation = VEC3_ZERO;
  model->scale = VEC3_ONE;
}

void model_update(Model* model) {
  model->model_matrix = mat4_identity();
  mat4_translate(model->position, &model->model_matrix);
  mat4_rotate(model->rotation, &model->model_matrix);
  mat4_scale(model->scale, &model->model_matrix);
}

void model_draw(Model* model, Shader* base_shader) {
  model_update(model);
  shader_uniform_mat4(base_shader, "model", model->model_matrix);
  mesh_draw(model->mesh);
}