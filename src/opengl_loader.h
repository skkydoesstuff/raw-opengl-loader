#pragma once

#include <windows.h>
#include <gl/gl.h>

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB  0x9126

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW  0x88E4
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_ELEMENT_ARRAY_BUFFER 0x8893

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

typedef void (APIENTRY*PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRY*PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRY*PFNGLCLEARPROC)(GLbitfield mask);

typedef void (APIENTRY*PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
typedef void (APIENTRY*PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void (APIENTRY*PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
typedef void (APIENTRY*PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void (APIENTRY*PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);

typedef void (APIENTRY*PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
typedef void (APIENTRY*PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void (APIENTRY*PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (APIENTRY*PFNGLDELETEBUFFERSPROC)(GLsizei n, GLuint* buffers);

typedef void (APIENTRY*PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
typedef void (APIENTRY*PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void* indices);


typedef struct {
  PFNGLVIEWPORTPROC glViewport;
  PFNGLCLEARCOLORPROC glClearColor;
  PFNGLCLEARPROC glClear;

  PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
  PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
  PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
  PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
  PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

  PFNGLGENBUFFERSPROC glGenBuffers;
  PFNGLBINDBUFFERPROC glBindBuffer;
  PFNGLBUFFERDATAPROC glBufferData;
  PFNGLDELETEBUFFERSPROC glDeleteBuffers;

  PFNGLDRAWARRAYSPROC glDrawArrays;
  PFNGLDRAWELEMENTSPROC glDrawElements;
} GLFunctions;

extern GLFunctions gl;