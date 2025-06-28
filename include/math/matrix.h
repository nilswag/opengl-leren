#pragma once

#define MATH_IDENTITY_MATRIX_4x4 { \
    1.0f, 0.0f, 0.0f, 0.0f, \
    0.0f, 1.0f, 0.0f, 0.0f, \
    0.0f, 0.0f, 1.0f, 0.0f, \
    0.0f, 0.0f, 0.0f, 1.0f  \
}


void math_matrix_mult(float* a, float* b, float* c);
void math_matrix_translate(float* mat, float x, float y, float z);