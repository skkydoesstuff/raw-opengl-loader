#include "core/opengl_loader/opengl_types.h"

typedef struct {
  const char* name;
  GLuint uniform;
} Uniform;

typedef struct {
  GLuint program;
} Shader;

void shader_create(Shader* shader, const char* vertex_file_name, const char* fragment_file_name);
void shader_bind(Shader* shader);
void shader_destroy(Shader* shader);