#include "example_app/app/app.h"

int main() {
  App app = {0};
  app_create(&app);
  app_run(&app);
  app_destroy(&app);

  return 0;
}