#pragma once

#define MATH_DEGREE_TO_RADIAN(deg) ((deg) * (3.14159265358979323846f / 180.0f))

#define MATH_IDENTITY_MATRIX_4x4 { \
    1.0f, 0.0f, 0.0f, 0.0f, \
    0.0f, 1.0f, 0.0f, 0.0f, \
    0.0f, 0.0f, 1.0f, 0.0f, \
    0.0f, 0.0f, 0.0f, 1.0f  \
}

void math_matrix_mult(float* a, float* b, float* c);
void math_matrix_translate(float* a, float dx, float dy, float dz);

void math_matrix_rotate_x(float* a, float deg);
void math_matrix_rotate_y(float* a, float deg);
void math_matrix_rotate_z(float* a, float deg);
void math_matrix_rotate(float* a, float degx, float degy, float degz);