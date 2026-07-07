#include "core/math/vectors.h"
#include "core/math/custom_math.h"

Vec3 vec3_add(Vec3 a, Vec3 b) {
  return (Vec3){
    a.x + b.x,
    a.y + b.y,
    a.z + b.z
  };
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
  return (Vec3){
    a.x - b.x,
    a.y - b.y,
    a.z - b.z
  };
}

Vec3 vec3_mul_vec3(Vec3 a, Vec3 b) {
  return (Vec3){
    a.x * b.x,
    a.y * b.y,
    a.z * b.z
  };
}

Vec3 vec3_scale(Vec3 v, float s) {
  return (Vec3){
    v.x * s,
    v.y * s,
    v.y * s
  };
}

float vec3_dot(Vec3 a, Vec3 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec3 vec3_cross(Vec3 a, Vec3 b) {
  return (Vec3){
    (a.y * b.z) - (a.z * b.y),
    (a.z * b.x) - (a.x * b.z),
    (a.x * b.y) - (a.y * b.x)
  };
}

float vec3_length(Vec3 v) {
  return my_sqrtf(vec3_dot(v, v));
}

Vec3 vec3_normalize(Vec3 v) {
  float len = vec3_length(v);

  if (len == 0.0f) {
    return (Vec3){0.0f, 0.0f, 0.0f};
  }

  float inv_len = 1.0f / len;

  return (Vec3){
    v.x * inv_len,
    v.y * inv_len,
    v.z * inv_len
  };
}