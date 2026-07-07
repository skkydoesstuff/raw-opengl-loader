#pragma once

#include "core/math/vectors.h"

typedef struct {
  float m[16];
} Mat4;

Mat4 mat4_identity(void);

void mat4_perspective(float fovy, float aspect, float near, float far, Mat4* dest);
void mat4_look_at(Vec3 eye, Vec3 center, Vec3 up, Mat4* dest);

void mat4_translate(Vec3 position, Mat4* dest);
void mat4_rotate(Vec3 rotation, Mat4* dest);
void mat4_scale(Vec3 scale, Mat4* dest);