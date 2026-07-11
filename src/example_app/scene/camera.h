#pragma once

#include "core/math/matrices.h"

typedef struct {
  Vec3 position;
  float yaw, pitch;

  Mat4 view;
  Mat4 projection;
} Camera;

void camera_create(
  Camera* camera,
  float fov,
  float aspect,
  float near_plane,
  float far_plane
);

void camera_update(Camera* camera);