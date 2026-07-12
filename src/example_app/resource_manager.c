#include "example_app/resource_manager.h"

#include "core/utils/string_compare.h"

#include "example_app/renderer/shader.h"
#include "example_app/renderer/mesh.h"

#include <malloc.h>

void rm_create(ResourceManager* rm) {
  rm->items = NULL;
  rm->capacity = 0;
  rm->count = 0;
}

void rm_add_item(ResourceManager* rm, ResourceType type, const char* tag, void* data) {
  if (rm->count >= rm->capacity) {
    size_t new_capacity = rm->capacity == 0
      ? 8
      : rm->capacity * 2;

    Resource* new_items = realloc(
      rm->items,
      sizeof(Resource) * new_capacity
    );

    if (!new_items)
      return;

    rm->items = new_items;
    rm->capacity = new_capacity;
  }

  Resource r = {
    tag,
    type,
    data
  };

  rm->items[rm->count++] = r;
}

Resource* rm_get_item(ResourceManager* rm, const char* tag) {
  for (size_t i = 0; i < rm->count; i++) {
    if (string_compare(tag, rm->items[i].tag)) {
      return &rm->items[i];
    }
  }

  return NULL;
}

void rm_destroy(ResourceManager* rm) {
  for (size_t i = 0; i < rm->count; i++) {
    switch(rm->items[i].type) {
      case RESOURCE_SHADER: 
        shader_destroy(rm->items[i].data);
        free(rm->items[i].data);
        break;

      case RESOURCE_MESH:
        mesh_destroy(rm->items[i].data);
        free(rm->items[i].data);
        break;

      case RESOURCE_MODEL:
        free(rm->items[i].data);
        break;

      case RESOURCE_CAMERA:
        free(rm->items[i].data);
        break;
    }
  }

  free(rm->items);
  rm->items = NULL;
  rm->count = 0;
  rm->capacity = 0;
}