#pragma once

#include "core/opengl_loader/opengl_types.h"

typedef struct {
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;

  GLsizei stride;
  GLint index_count;
} Mesh;

void mesh_create(
  Mesh* mesh,
  GLfloat* vertices,
  GLint floats_per_vertex,
  GLsizeiptr size_of_vertices,
  GLuint* indices,
  GLint total_index_count,
  GLsizeiptr size_of_indices
);

void mesh_bind(Mesh* mesh);

void mesh_add_vertex_attribute(
  Mesh* mesh,
  GLuint index,
  GLint size,
  const void* ptr
);

void mesh_draw(Mesh* mesh);

void mesh_destroy(Mesh* mesh);