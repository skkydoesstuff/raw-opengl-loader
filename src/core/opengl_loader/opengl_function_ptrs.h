#pragma once

#include <stdint.h>
#include <windows.h>

#include "core/opengl_loader/opengl_types.h"

// general opengl functions
typedef void (APIENTRY*glViewportProc)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRY*glClearColorProc)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRY*glClearProc)(GLbitfield mask);
typedef void (APIENTRY*glEnableProc)(GLenum cap);
typedef void (APIENTRY*glDisableProc)(GLenum cap);
typedef const GLubyte* (APIENTRY*glGetStringProc)(GLenum name);

// vertex array functions
typedef void (APIENTRY*glGenVertexArraysProc)(GLsizei n, GLuint* arrays);
typedef void (APIENTRY*glBindVertexArrayProc)(GLuint array);
typedef void (APIENTRY*glDeleteVertexArraysProc)(GLsizei n, GLuint* arrays);
typedef void (APIENTRY*glVertexAttribPointerProc)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void (APIENTRY*glEnableVertexAttribArrayProc)(GLuint index);

// buffer functions
typedef void (__stdcall*glGenBuffersProc)(GLsizei n, GLuint* buffers);
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

// uniform functions
typedef GLint (APIENTRY*glGetUniformLocationProc)(GLuint program, const GLchar* name);

typedef void (APIENTRY*glUniformMatrix4fvProc)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* val);