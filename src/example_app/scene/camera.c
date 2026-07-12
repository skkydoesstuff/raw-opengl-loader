#include "example_app/scene/camera.h"

#include "core/math/matrices.h"
#include "core/math/radians.h"
#include "core/math/vectors.h"

#include <math.h>

void camera_create(
  Camera* camera,
  float fov,
  float aspect,
  float near_plane,
  float far_plane
) {
  camera->position = VEC3_ZERO;
  camera->yaw = -90.0f;
  camera->pitch = 0.0f;

  camera->projection = mat4_identity();
  mat4_perspective(TO_RADIANS(fov), aspect, near_plane, far_plane, &camera->projection);
}

void camera_update(Camera* camera) {
  camera->view = mat4_identity();

  Vec3 forward = VEC3_ZERO;

  float yaw_rad = TO_RADIANS(camera->yaw);
  float pitch_rad = TO_RADIANS(camera->pitch);

  forward.x = cosf(yaw_rad) * cosf(pitch_rad);
  forward.y = sinf(pitch_rad);
  forward.z = sinf(yaw_rad) * cosf(pitch_rad);

  forward = vec3_normalize(forward);

  Vec3 target = vec3_add(camera->position, forward);

  mat4_look_at(camera->position, target, (Vec3){0.0f, 1.0f, 0.0f}, &camera->view);
}