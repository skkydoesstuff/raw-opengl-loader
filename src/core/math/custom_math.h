#pragma once

#define PI 3.14159265358979323846f
#define HALF_PI 1.57079632679489661923f
#define TWO_PI 6.28318530717958647692f
#define INV_TWO_PI 0.15915494309189533577f

#define NAN_F 0x7FC00000

float my_sqrtf(float x);
float my_fabsf(float x);
float my_fminf(float a, float b);
float my_fmaxf(float a, float b);
float my_copysignf(float x, float y);

float my_sinf(float rad);
float my_cosf(float rad);
float my_tanf(float rad);