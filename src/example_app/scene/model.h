#pragma once

#include "core/math/vectors.h"
#include "core/math/matrices.h"

#include "example_app/renderer/mesh.h"
#include "example_app/renderer/shader.h"

typedef struct {
  Mesh* mesh;
  Vec3 position;
  Vec3 rotation;
  Vec3 scale;

  Mat4 model_matrix;
} Model;

void model_create(Model* model, Mesh* mesh);

void model_draw(Model* model, Shader* base_shader);