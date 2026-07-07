#include "core/math/matrices.h"

#include <math.h>

#define MAT4(col, row) ((col) * 4 + (row))

static const Mat4 MAT4_IDENTITY = {
  .m = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  }
};

Mat4 mat4_identity(void) {
  return MAT4_IDENTITY;
}

Mat4 mat4_mul(Mat4 a, Mat4 b) {
  Mat4 res = {0};

  for (int col = 0; col < 4; col++){
    for (int row = 0; row < 4; row++) {
      res.m[MAT4(col, row)] =
        a.m[MAT4(0, row)] * b.m[MAT4(0, col)] +
        a.m[MAT4(1, row)] * b.m[MAT4(1, col)] +
        a.m[MAT4(2, row)] * b.m[MAT4(2, col)] +
        a.m[MAT4(3, row)] * b.m[MAT4(3, col)];
    }
  }

  return res;
}

Mat4 mat4_translate_create(Vec3 position) {
  Mat4 res = MAT4_IDENTITY;

  res.m[MAT4(3, 0)] = position.x;
  res.m[MAT4(3, 1)] = position.y;
  res.m[MAT4(3, 2)] = position.z;

  return res;
}

Mat4 mat4_scale_create(Vec3 scale) {
  Mat4 res = MAT4_IDENTITY;

  res.m[MAT4(0, 0)] = scale.x;
  res.m[MAT4(1, 1)] = scale.y;
  res.m[MAT4(2, 2)] = scale.z;

  return res;
}

Mat4 mat4_rotate_x_create(float radians) {
  Mat4 res = MAT4_IDENTITY;

  float c = cosf(radians);
  float s = sinf(radians);

  res.m[MAT4(1, 1)] =  c;
  res.m[MAT4(1, 2)] =  s;
  res.m[MAT4(2, 1)] = -s;
  res.m[MAT4(2, 2)] =  c;

  return res;
}

Mat4 mat4_rotate_y_create(float radians) {
  Mat4 res = MAT4_IDENTITY;

  float c = cosf(radians);
  float s = sinf(radians);

  res.m[MAT4(0, 0)] =  c;
  res.m[MAT4(0, 2)] = -s;
  res.m[MAT4(2, 0)] =  s;
  res.m[MAT4(2, 2)] =  c;

  return res;
}

Mat4 mat4_rotate_z_create(float radians) {
  Mat4 res = MAT4_IDENTITY;

  float c = cosf(radians);
  float s = sinf(radians);

  res.m[MAT4(0, 0)] =  c;
  res.m[MAT4(0, 1)] =  s;
  res.m[MAT4(1, 0)] = -s;
  res.m[MAT4(1, 1)] =  c;

  return res;
}

void mat4_perspective(float fovy, float aspect, float near, float far, Mat4* dest) {
  *dest = MAT4_IDENTITY;

  float f = 1.0f / tanf(fovy * 0.5f);
  float nf = 1.0f / (near - far);

  dest->m[MAT4(0, 0)] = f / aspect;
  dest->m[MAT4(1, 1)] = f;
  dest->m[MAT4(2, 2)] = (near + far) * nf;
  dest->m[MAT4(2, 3)] = -1.0f;
  dest->m[MAT4(3, 2)] = 2.0f * near * far * nf;
}

void mat4_look_at(Vec3 eye, Vec3 center, Vec3 up, Mat4* dest) {
  Vec3 forward = vec3_normalize(vec3_sub(center, eye));
  Vec3 right   = vec3_normalize(vec3_cross(forward, up));
  Vec3 camera_up = vec3_cross(right, forward);

  *dest = MAT4_IDENTITY;

  dest->m[MAT4(0, 0)] = right.x;
  dest->m[MAT4(0, 1)] = right.y;
  dest->m[MAT4(0, 2)] = right.z;

  dest->m[MAT4(1, 0)] = camera_up.x;
  dest->m[MAT4(1, 1)] = camera_up.y;
  dest->m[MAT4(1, 2)] = camera_up.z;

  dest->m[MAT4(2, 0)] = -forward.x;
  dest->m[MAT4(2, 1)] = -forward.y;
  dest->m[MAT4(2, 2)] = -forward.z;

  dest->m[MAT4(3, 0)] = -vec3_dot(right, eye);
  dest->m[MAT4(3, 1)] = -vec3_dot(camera_up, eye);
  dest->m[MAT4(3, 2)] =  vec3_dot(forward, eye);
}

void mat4_translate(Vec3 position, Mat4 *dest) {
  Mat4 translated = mat4_translate_create(position);

  *dest = mat4_mul(*dest, translated);
}

void mat4_rotate(Vec3 rotation, Mat4 *dest) {
  Mat4 rotatedX = mat4_rotate_x_create(rotation.x);
  Mat4 rotatedY = mat4_rotate_y_create(rotation.y);
  Mat4 rotatedZ = mat4_rotate_z_create(rotation.z);

  Mat4 rotated = mat4_mul(rotatedX, rotatedY);
  rotated = mat4_mul(rotated, rotatedZ);

  *dest = mat4_mul(*dest, rotated);
}

void mat4_scale(Vec3 scale, Mat4* dest) {
  Mat4 scaled = mat4_scale_create(scale);
  *dest = mat4_mul(*dest, scaled);
}