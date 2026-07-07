#pragma once

#include <windows.h>

#include "core/opengl_loader/opengl_types.h"
#include "core/opengl_loader/opengl_enums.h"
#include "core/opengl_loader/opengl_function_ptrs.h"

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB  0x9126

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

typedef HGLRC (WINAPI *PFNWGLCREATECONTEXTATTRIBSARBPROC)(
  HDC,
  HGLRC,
  const int *
);

typedef struct {
  HGLRC hglrc;
} Context;

void context_create(HGLRC* context, HDC hdc);
void context_destroy(HGLRC* context);
void create_capabilities();

typedef struct GLFunctions {
  #define GL_FUNCTION(name) name##Proc name;
  #include "core/opengl_loader/opengl_functions.inc"
  #undef GL_FUNCTION
} GLFunctions;


extern GLFunctions gl;