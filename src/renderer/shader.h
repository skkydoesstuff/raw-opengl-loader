#include "core/opengl_loader/opengl_types.h"

#include "core/math/matrices.h"

typedef struct {
  const char* name;
  GLuint uniform;
} Uniform;

typedef struct {
  GLuint program;
  int uniform_count;
  Uniform* uniforms;
} Shader;

void shader_create(Shader* shader, const char* vertex_file_name, const char* fragment_file_name);
void shader_bind(Shader* shader);
void shader_destroy(Shader* shader);

void shader_uniform_mat4(Shader* shader, const char* name, Mat4 mat);