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
} Matf;


typedef struct
{
    float data[4 * 4];
} Matf4x4;


void math_matrix_mult(Matf* a, Matf* b, Matf* c);
void math_matrix_mult4x4(Matf4x4* a, Matf4x4* b, Matf4x4* c);

void math_matrix_translate4x4_x(Matf4x4* a, float dx);
void math_matrix_translate4x4_y(Matf4x4* a, float dy);
void math_matrix_translate4x4_z(Matf4x4* a, float dz);
void math_matrix_translate4x4(Matf4x4* a, float dx, float dy, float dz);

void math_matrix_rotate4x4_x(Matf4x4* a, float deg);
void math_matrix_rotate4x4_y(Matf4x4* a, float deg);
void math_matrix_rotate4x4_z(Matf4x4* a, float deg);
void math_matrix_rotate4x4(Matf4x4* a, float degx, float degy, float degz);

void math_matrix_scale4x4_x(Matf4x4* a, float x);
void math_matrix_scale4x4_y(Matf4x4* a, float y);
void math_matrix_scale4x4_z(Matf4x4* a, float z);
void math_matrix_scale4x4(Matf4x4* a, float w);

Matf4x4 math_matrix_lookat(Vec3f from, Vec3f to);
Matf4x4 math_matrix_proj_pers(float fov, float aspect_ratio, float z_near, float z_far);