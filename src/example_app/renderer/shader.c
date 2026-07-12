#include "core/opengl_loader/opengl_loader.h"

#include "core/file_utils/file_utils.h"
#include "core/utils/string_compare.h"

#include "example_app/renderer/shader.h"

#include "logging.h"

GLuint compile_shader(const GLchar** src, GLenum type) {
  GLuint shader = gl.glCreateShader(type);
  gl.glShaderSource(shader, 1, src, NULL);
  gl.glCompileShader(shader);

  return shader;
}

GLuint link_program(GLuint v, GLuint f) {
  GLuint p = gl.glCreateProgram();
  gl.glAttachShader(p, v);
  gl.glAttachShader(p, f);
  gl.glLinkProgram(p);
  gl.glDetachShader(p, v);
  gl.glDetachShader(p, f);
  gl.glDeleteShader(v);
  gl.glDeleteShader(f);

  return p;
}

void shader_create(Shader* shader, const char* vertex_file_name, const char* fragment_file_name) {
  shader->program = 0;
  shader->uniform_count = 0;
  shader->uniforms = (void*)0;

  char *exe_dir = get_executable_path();
  const char *suffix = "/assets/shaders/";

  size_t shader_dir_len = strlen(exe_dir) + strlen(suffix) + 1;
  char *shader_dir = malloc(shader_dir_len);
  if (shader_dir == NULL) {
      print("Failed to allocate memory for the shader directory!");
      free(exe_dir);
      return;
  }

  strcpy(shader_dir, exe_dir);
  strcat(shader_dir, suffix);

  size_t vertex_len = strlen(shader_dir) + strlen(vertex_file_name) + 1;
  char *vertex_path = malloc(vertex_len);
  if (vertex_path == NULL) {
      print("Failed to allocate memory for vertex shader path!");
      free(shader_dir);
      free(exe_dir);
      return;
  }
  strcpy(vertex_path, shader_dir);
  strcat(vertex_path, vertex_file_name);

  size_t fragment_len = strlen(shader_dir) + strlen(fragment_file_name) + 1;
  char *fragment_path = malloc(fragment_len);
  if (fragment_path == NULL) {
      print("Failed to allocate memory for fragment shader path!");
      free(vertex_path);
      free(shader_dir);
      free(exe_dir);
      return;
  }
  strcpy(fragment_path, shader_dir);
  strcat(fragment_path, fragment_file_name);

  char* vert_src = read_file(vertex_path);
  char* frag_src = read_file(fragment_path);

  if (!vert_src) {
    print("vertex shader failed to load\n");
    return;
  }

  if (!frag_src) {
    print("fragment shader failed to load\n");
    free(vert_src);
    return;
  }

  GLuint v = compile_shader((const char**)&vert_src, GL_VERTEX_SHADER);
  GLuint f = compile_shader((const char**)&frag_src, GL_FRAGMENT_SHADER);
  
  shader->program = link_program(v, f);

  free(fragment_path);
  free(vertex_path);
  free(shader_dir);
  free(exe_dir);
}

void shader_bind(Shader* shader) {
  gl.glUseProgram(shader->program);
}

void shader_destroy(Shader* shader) {
  gl.glDeleteProgram(shader->program);
}

GLint shader_get_uniform(Shader* shader, const char* name) {
  for (int i = 0; i < shader->uniform_count; i++) {
    if (string_compare(shader->uniforms[i].name, name)) {
      return shader->uniforms[i].uniform;
    }
  }

  shader->uniforms = realloc(
    shader->uniforms,
    (shader->uniform_count + 1) * sizeof(Uniform)
  );

  if (shader->uniforms == NULL) {
    return 0;
  }

  Uniform uni = {
    name,
    gl.glGetUniformLocation(shader->program, name)
  };

  shader->uniforms[shader->uniform_count] = uni;
  shader->uniform_count++;

  return uni.uniform;
}

void shader_uniform_mat4(Shader* shader, const char* name, Mat4 mat) {
  GLint uni = shader_get_uniform(shader, name);
  gl.glUniformMatrix4fv(uni, 1, GL_FALSE, mat.m);
}