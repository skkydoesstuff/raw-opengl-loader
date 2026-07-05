#pragma once

#include <windows.h>

#include "opengl_loader/opengl_types.h"
#include "opengl_loader/opengl_enums.h"

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB  0x9126

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

typedef ptrdiff_t GLsizeiptr;

typedef HGLRC (WINAPI *PFNWGLCREATECONTEXTATTRIBSARBPROC)(
    HDC,
    HGLRC,
    const int *
);

typedef struct {
  HGLRC hglrc;
} Context;

void create_context(HGLRC* context, HDC hdc);
void destroy_context(HGLRC* context);
void create_capabilities();

// general opengl functions
typedef void (APIENTRY*glViewportProc)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRY*glClearColorProc)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRY*glClearProc)(GLbitfield mask);

// vertex array functions
typedef void (APIENTRY*glGenVertexArraysProc)(GLsizei n, GLuint* arrays);
typedef void (APIENTRY*glBindVertexArrayProc)(GLuint array);
typedef void (APIENTRY*glDeleteVertexArraysProc)(GLsizei n, GLuint* arrays);
typedef void (APIENTRY*glVertexAttribPointerProc)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void (APIENTRY*glEnableVertexAttribArrayProc)(GLuint index);

// buffer functions
typedef void (APIENTRY*glGenBuffersProc)(GLsizei n, GLuint* buffers);
typedef void (APIENTRY*glBindBufferProc)(GLenum target, GLuint buffer);
typedef void (APIENTRY*glBufferDataProc)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (APIENTRY*glDeleteBuffersProc)(GLsizei n, GLuint* buffers);

// drawing functions
typedef void (APIENTRY*glDrawArraysProc)(GLenum mode, GLint first, GLsizei count);
typedef void (APIENTRY*glDrawElementsProc)(GLenum mode, GLsizei count, GLenum type, const void* indices);

// shader functions
typedef GLuint (APIENTRY*glCreateShaderProc)(GLenum shaderType);
typedef GLuint (APIENTRY*glDeleteShaderProc)(GLuint shader);
typedef void (APIENTRY*glShaderSourceProc)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
typedef void (APIENTRY*glCompileShaderProc)(GLuint shader);
typedef GLuint (APIENTRY*glCreateProgramProc)();
typedef GLuint (APIENTRY*glDeleteProgramProc)(GLuint program);
typedef void (APIENTRY*glAttachShaderProc)(GLuint program, GLuint shader);
typedef void (APIENTRY*glDetachShaderProc)(GLuint program, GLuint shader);
typedef void (APIENTRY*glLinkProgramProc)(GLuint program);
typedef void (APIENTRY*glUseProgramProc)(GLuint program);

typedef struct {
  glViewportProc glViewport;
  glClearColorProc glClearColor;
  glClearProc glClear;

  glGenVertexArraysProc glGenVertexArrays;
  glBindVertexArrayProc glBindVertexArray;
  glDeleteVertexArraysProc glDeleteVertexArrays;
  glVertexAttribPointerProc glVertexAttribPointer;
  glEnableVertexAttribArrayProc glEnableVertexAttribArray;

  glGenBuffersProc glGenBuffers;
  glBindBufferProc glBindBuffer;
  glBufferDataProc glBufferData;
  glDeleteBuffersProc glDeleteBuffers;

  glDrawArraysProc glDrawArrays;
  glDrawElementsProc glDrawElements;

  glCreateShaderProc glCreateShader;
  glDeleteShaderProc glDeleteShader;
  glShaderSourceProc glShaderSource;
  glCompileShaderProc glCompileShader;
  glCreateProgramProc glCreateProgram;
  glDeleteProgramProc glDeleteProgram;
  glAttachShaderProc glAttachShader;
  glDetachShaderProc glDetachShader;
  glLinkProgramProc glLinkProgram;
  glUseProgramProc glUseProgram;
} GLFunctions;

extern GLFunctions gl;