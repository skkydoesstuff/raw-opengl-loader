#pragma once

#include <stddef.h>

typedef enum {
  RESOURCE_SHADER,
  RESOURCE_MESH,
  RESOURCE_CAMERA,
  RESOURCE_MODEL
} ResourceType;

typedef struct {
  const char* tag;
  ResourceType type;
  void* data;
} Resource;

typedef struct {
  Resource* items;
  size_t count;
  size_t capacity;
} ResourceManager;

void rm_create(ResourceManager* rm);
void rm_add_item(ResourceManager* rm, ResourceType type, const char* tag, void* data);
Resource* rm_get_item(ResourceManager* rm, const char* tag);
void rm_destroy(ResourceManager* rm);