#include "opengl_loader.h"
#include "error.h"

GLFunctions gl = {0};

void create_context(HGLRC* context, HDC hdc) {
  PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR), 
    1, 
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, 
    PFD_TYPE_RGBA, 
    32, 
    0, 0, 0, 0, 0, 0, 
    0, 
    0, 
    0, 
    0, 0, 0, 0, 
    24, 
    8, 
    0, 
    PFD_MAIN_PLANE, 
    0, 
    0, 0, 0
  };

  int pixelFormat = ChoosePixelFormat(hdc, &pfd);

  if (pixelFormat == 0 || !SetPixelFormat(hdc, pixelFormat, &pfd)) {
    MessageBox(NULL, "Failed to set pixel format", "Error!", MB_ICONERROR | MB_OK);
  }

  HGLRC old_context = wglCreateContext(hdc);
  if (!old_context || !wglMakeCurrent(hdc, old_context)) {
    LOG("Failed to create temporary opengl context!");
  }

  PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
    (PFNWGLCREATECONTEXTATTRIBSARBPROC)
      wglGetProcAddress("wglCreateContextAttribsARB");

  if (!wglCreateContextAttribsARB) {
    LOG("Extension not supported");
  }

  const int attribs[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB,
        WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0
  };

  *context =
    wglCreateContextAttribsARB(hdc, 0, attribs);

  if (!*context) {
    LOG("Couldn't create OpenGL 4.6");
  }

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(old_context);

  wglMakeCurrent(hdc, *context);
}

void destroy_context(HGLRC* context) {
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(*context);
}

void* get_gl_proc(const char* name) {
  void* proc = (void*)wglGetProcAddress(name);

  if (proc == 0 ||
        proc == (void *)0x1 ||
        proc == (void *)0x2 ||
        proc == (void *)0x3 ||
        proc == (void *)-1)
    {
        proc = (void *)GetProcAddress(
            GetModuleHandleA("opengl32.dll"),
            name
        );
    }

    return proc;
}

void create_capabilities() {
  gl.glViewport = (PFNGLVIEWPORTPROC)
    get_gl_proc("glViewport");

  gl.glClearColor = (PFNGLCLEARCOLORPROC)
    get_gl_proc("glClearColor");

  gl.glClear = (PFNGLCLEARPROC)
    get_gl_proc("glClear");

  gl.glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)
    get_gl_proc("glGenVertexArrays");

  gl.glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)
    get_gl_proc("glBindVertexArray");

  gl.glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)
    get_gl_proc("glDeleteVertexArrays");

  gl.glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)
    get_gl_proc("glVertexAttribPointer");

  gl.glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)
    get_gl_proc("glEnableVertexAttribArray");

  gl.glGenBuffers = (PFNGLGENBUFFERSPROC)
    get_gl_proc("glGenBuffers");

  gl.glBindBuffer = (PFNGLBINDBUFFERPROC)
    get_gl_proc("glBindBuffer");
  
  gl.glBufferData = (PFNGLBUFFERDATAPROC)
    get_gl_proc("glBufferData");

  gl.glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)
    get_gl_proc("glDeleteBuffers");

  gl.glDrawArrays = (PFNGLDRAWARRAYSPROC)
    get_gl_proc("glDrawArrays");

  gl.glDrawElements = (PFNGLDRAWELEMENTSPROC)
    get_gl_proc("glDrawElements");
}

