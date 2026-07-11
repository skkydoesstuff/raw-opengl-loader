#include "core/opengl_loader/opengl_loader.h"

#include "example_app/renderer/mesh.h"

void mesh_create(
  Mesh* mesh,
  GLfloat* vertices,
  GLint floats_per_vertex,
  GLsizeiptr size_of_vertices,
  GLuint* indices,
  GLint total_index_count,
  GLsizeiptr size_of_indices
) {
  mesh->stride = floats_per_vertex * sizeof(GLfloat);
  mesh->index_count = total_index_count;

  gl.glGenVertexArrays(1, &mesh->VAO);
  gl.glBindVertexArray(mesh->VAO);
  
  gl.glGenBuffers(1, &mesh->VBO);
  gl.glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
  gl.glBufferData(GL_ARRAY_BUFFER, size_of_vertices, vertices, GL_STATIC_DRAW);

  gl.glGenBuffers(1, &mesh->EBO);
  gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
  gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_indices, indices, GL_STATIC_DRAW);
}

void mesh_bind(Mesh* mesh) {
  gl.glBindVertexArray(mesh->VAO);
}

void mesh_add_vertex_attribute(
  Mesh* mesh,
  GLuint index,
  GLint size,
  const void* ptr
) {

  mesh_bind(mesh);
  gl.glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, mesh->stride, ptr);
  gl.glEnableVertexAttribArray(index);
}

void mesh_draw(Mesh* mesh) {
  mesh_bind(mesh);
  gl.glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, NULL);
}

void mesh_destroy(Mesh* mesh) {
  gl.glDeleteBuffers(1, &mesh->VBO);
  gl.glDeleteBuffers(1, &mesh->EBO);
  gl.glDeleteVertexArrays(1, &mesh->VAO);
}