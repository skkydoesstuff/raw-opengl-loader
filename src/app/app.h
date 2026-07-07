#pragma once

#include "core/window/window.h"

#define TITLE "app"
#define WIDTH 1920
#define HEIGHT 1080

typedef struct {
  Window window;
  HGLRC context;
} App;

void app_create(App* app);
void app_run(App* app);
void app_destroy(App* app);