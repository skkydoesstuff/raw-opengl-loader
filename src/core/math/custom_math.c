#include "custom_math.h"
#include <stdint.h>

float my_sqrtf(float x) {
  if (x < 0.0f) {
    return 0.0f / 0.0f;
  }

  if (x == 0.0f || x == 1.0f) {
    return x;
  }

  union {
    float f;
    unsigned int i;
  } u = { x };

  // Approximate sqrt by halving the exponent
  u.i = (u.i >> 1) + 0x1FC00000;

  float guess = u.f;

  // Newton-Raphson refinement
  for (int i = 0; i < 4; i++) {
    guess = 0.5f * (guess + x / guess);
  }

  return guess;
}

float my_fabsf(float x) {
  union {
    float f;
    unsigned int i;
  } u = {x};

  u.i &= 0x7FFFFFFF;

  return u.f;
}

float my_fminf(float a, float b) {
  if (a < b) {
    return a;
  }

  return b;
}

float my_fmaxf(float a, float b) {
  if (a > b) {
    return a;
  }

  return b;
}

float my_copysignf(float x, float y) {
  union {  
    float f;
    unsigned int i;
  } ux = { x }, uy = { y };

  ux.i &= 0x7FFFFFFF;
  ux.i |= uy.i & 0x80000000;

  return ux.f;
}

static float wrap_pi(float x) {
    int k = (int)(x * INV_TWO_PI);

    x -= (float)k * TWO_PI;

    if (x > PI)
        x -= TWO_PI;

    if (x < -PI)
        x += TWO_PI;

    return x;
}

float my_sinf(float x) {
  x = wrap_pi(x);

  int sign = 1;

  if (x > HALF_PI) {
    x = PI - x;
  }
  else if (x < -HALF_PI) {
    x = -PI - x;
    sign = -1;
  }

  float x2 = x * x;

  float result =
    x *
    (1.0f
    - x2 * (1.0f / 6.0f)
    + x2 * x2 * (1.0f / 120.0f)
    - x2 * x2 * x2 * (1.0f / 5040.0f)
    + x2 * x2 * x2 * x2 * (1.0f / 362880.0f));

  return sign * result;
}

float my_cosf(float x) {
  return my_sinf(x + HALF_PI);
}

float my_tanf(float x) {
  float c = my_cosf(x);

  if (c == 0.0f)
    return 0.0f / 0.0f;

  return my_sinf(x) / c;
}