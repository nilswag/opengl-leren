#pragma once

#define MATH_MATRIX_IDENTITY { \
    1.0f, 0.0f, 0.0f, 0.0f, \
    0.0f, 1.0f, 0.0f, 0.0f, \
    0.0f, 0.0f, 1.0f, 0.0f, \
    0.0f, 0.0f, 0.0f, 1.0f  \
}

void math_matrix_mult(float* a, float* b, float* c);

void math_matrix_translate_x(float* a, float dx);
void math_matrix_translate_y(float* a, float dy);
void math_matrix_translate_z(float* a, float dz);
void math_matrix_translate(float* a, float dx, float dy, float dz);

void math_matrix_rotate_x(float* a, float deg);
void math_matrix_rotate_y(float* a, float deg);
void math_matrix_rotate_z(float* a, float deg);
void math_matrix_rotate(float* a, float degx, float degy, float degz);

void math_matrix_scale_x(float* a, float x);
void math_matrix_scale_y(float* a, float y);
void math_matrix_scale_z(float* a, float z);
void math_matrix_scale(float* a, float w);