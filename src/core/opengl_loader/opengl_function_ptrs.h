#pragma once

#include "core/opengl_loader/opengl_types.h"

// general opengl functions
typedef void (__stdcall*glViewportProc)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (__stdcall*glClearColorProc)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (__stdcall*glClearProc)(GLbitfield mask);
typedef void (__stdcall*glEnableProc)(GLenum cap);
typedef void (__stdcall*glDisableProc)(GLenum cap);
typedef const GLubyte* (__stdcall*glGetStringProc)(GLenum name);

// vertex array functions
typedef void (__stdcall*glGenVertexArraysProc)(GLsizei n, GLuint* arrays);
typedef void (__stdcall*glBindVertexArrayProc)(GLuint array);
typedef void (__stdcall*glDeleteVertexArraysProc)(GLsizei n, GLuint* arrays);
typedef void (__stdcall*glVertexAttribPointerProc)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void (__stdcall*glEnableVertexAttribArrayProc)(GLuint index);

// buffer functions
typedef void (__stdcall*glGenBuffersProc)(GLsizei n, GLuint* buffers);
typedef void (__stdcall*glBindBufferProc)(GLenum target, GLuint buffer);
typedef void (__stdcall*glBufferDataProc)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (__stdcall*glDeleteBuffersProc)(GLsizei n, GLuint* buffers);

// drawing functions
typedef void (__stdcall*glDrawArraysProc)(GLenum mode, GLint first, GLsizei count);
typedef void (__stdcall*glDrawElementsProc)(GLenum mode, GLsizei count, GLenum type, const void* indices);

// shader functions
typedef GLuint (__stdcall*glCreateShaderProc)(GLenum shaderType);
typedef GLuint (__stdcall*glDeleteShaderProc)(GLuint shader);
typedef void (__stdcall*glShaderSourceProc)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
typedef void (__stdcall*glCompileShaderProc)(GLuint shader);
typedef GLuint (__stdcall*glCreateProgramProc)();
typedef GLuint (__stdcall*glDeleteProgramProc)(GLuint program);
typedef void (__stdcall*glAttachShaderProc)(GLuint program, GLuint shader);
typedef void (__stdcall*glDetachShaderProc)(GLuint program, GLuint shader);
typedef void (__stdcall*glLinkProgramProc)(GLuint program);
typedef void (__stdcall*glUseProgramProc)(GLuint program);

// uniform functions
typedef GLint (__stdcall*glGetUniformLocationProc)(GLuint program, const GLchar* name);

typedef void (__stdcall*glUniformMatrix4fvProc)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* val);