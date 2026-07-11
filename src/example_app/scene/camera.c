#include "example_app/scene/camera.h"

#include "core/math/matrices.h"
#include "core/math/custom_math.h"
#include "core/math/vectors.h"

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
  mat4_perspective(my_radians(fov), aspect, near_plane, far_plane, &camera->projection);
}

void camera_update(Camera* camera) {
  camera->view = mat4_identity();

  Vec3 forward = VEC3_ZERO;

  float yaw_rad = my_radians(camera->yaw);
  float pitch_rad = my_radians(camera->pitch);

  forward.x = my_cosf(yaw_rad) * my_cosf(pitch_rad);
  forward.y = my_sinf(pitch_rad);
  forward.z = my_sinf(yaw_rad) * my_cosf(pitch_rad);

  forward = vec3_normalize(forward);

  Vec3 target = vec3_add(camera->position, forward);

  mat4_look_at(camera->position, target, (Vec3){0.0f, 1.0f, 0.0f}, &camera->view);
}