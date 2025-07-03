#pragma once
#include "math/vector.h"

#define MATH_MATRIX_IDENTITY_4x4f { \
    1.0f, 0.0f, 0.0f, 0.0f, \
    0.0f, 1.0f, 0.0f, 0.0f, \
    0.0f, 0.0f, 1.0f, 0.0f, \
    0.0f, 0.0f, 0.0f, 1.0f  \
}


typedef struct
{
    float* data;
    size_t rows;
    size_t cols;
} matf_t;


typedef struct
{
    float data[4 * 4];
} mat4x4f_t;


void math_matrix_mult(matf_t* a, matf_t* b, matf_t* c);
void math_matrix_mult4x4(mat4x4f_t* a, mat4x4f_t* b, mat4x4f_t* c);

void math_matrix_translate4x4_x(mat4x4f_t* a, float dx);
void math_matrix_translate4x4_y(mat4x4f_t* a, float dy);
void math_matrix_translate4x4_z(mat4x4f_t* a, float dz);
void math_matrix_translate4x4(mat4x4f_t* a, float dx, float dy, float dz);

void math_matrix_rotate4x4_x(mat4x4f_t* a, float deg);
void math_matrix_rotate4x4_y(mat4x4f_t* a, float deg);
void math_matrix_rotate4x4_z(mat4x4f_t* a, float deg);
void math_matrix_rotate4x4(mat4x4f_t* a, float degx, float degy, float degz);

void math_matrix_scale4x4_x(mat4x4f_t* a, float x);
void math_matrix_scale4x4_y(mat4x4f_t* a, float y);
void math_matrix_scale4x4_z(mat4x4f_t* a, float z);
void math_matrix_scale4x4(mat4x4f_t* a, float w);