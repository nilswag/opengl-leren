#include <stdio.h>
#include <string.h>
#include <math.h>

#include "math/math.h"
#include "math/matrix.h"


typedef enum
{
    AXIS_X,
    AXIS_Y,
    AXIS_Z
} _axis_e;


void math_matrix_mult(matf_t* a, matf_t* b, matf_t* c)
{
    if (a->cols != b->rows)
    {
        fputs("Incompatible matrix sizes.", stderr);
        return;
    }

    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < b->cols; j++)
        {
            c->data[i * b->cols + j] = 0;
            for (size_t k = 0; k < a->cols; k++)
            {
                c->data[i * b->cols + j] += a->data[i * a->cols + k] * b->data[k * b->cols + j];
            }
        }
    }
}


void math_matrix_mult4x4(mat4x4f_t* a, mat4x4f_t* b, mat4x4f_t* c)
{
    matf_t _a = {
        .data = a->data, .rows = 4, .cols = 4
    };

    matf_t _b = {
        .data = b->data, .rows = 4, .cols = 4
    };

    matf_t _c = {
        .data = c->data, .rows = 4, .cols = 4
    };

    math_matrix_mult(&_a, &_b, &_c);
}


static void _matrix_translate4x4(mat4x4f_t* a, float d, _axis_e axis)
{
    mat4x4f_t t = MATH_MATRIX_IDENTITY_4x4f;
    switch (axis)
    {
    case AXIS_X:
        t.data[0 * 4 + 3] = d;
        break;

    case AXIS_Y:
        t.data[1 * 4 + 3] = d;
        break;

    case AXIS_Z:
        t.data[2 * 4 + 3] = d;
        break;

    default:
        break;
    }

    mat4x4f_t tmp = { 0 };
    math_matrix_mult4x4(&t, a, &tmp);
    memcpy(a->data, tmp.data, 16 * sizeof(float));
}


void math_matrix_translate4x4_x(mat4x4f_t* a, float dx)
{
    _matrix_translate4x4(a, dx, AXIS_X);
}


void math_matrix_translate4x4_y(mat4x4f_t* a, float dy)
{
    _matrix_translate4x4(a, dy, AXIS_Y);
}


void math_matrix_translate4x4_z(mat4x4f_t* a, float dz)
{
    _matrix_translate4x4(a, dz, AXIS_Z);
}


void math_matrix_translate4x4(mat4x4f_t* a, float dx, float dy, float dz)
{
    math_matrix_translate4x4_x(a, dx);
    math_matrix_translate4x4_y(a, dy);
    math_matrix_translate4x4_z(a, dz);
}


static void _matrix_rotate_plane4x4(mat4x4f_t* a, float deg, _axis_e axis)
{
    mat4x4f_t t = MATH_MATRIX_IDENTITY_4x4f;
    float rad = MATH_DEGREE_TO_RADIAN(deg);
    float c = cosf(rad);
    float s = sinf(rad);

    switch (axis)
    {
    case AXIS_X:
        t.data[1 * 4 + 1] = c;
        t.data[1 * 4 + 2] = -s;
        t.data[2 * 4 + 1] = s;
        t.data[2 * 4 + 2] = c;
        break;

    case AXIS_Y:
        t.data[0 * 4 + 0] = c;
        t.data[0 * 4 + 2] = s;
        t.data[2 * 4 + 0] = -s;
        t.data[2 * 4 + 2] = c;
        break;

    case AXIS_Z:
        t.data[0 * 4 + 0] = c;
        t.data[0 * 4 + 1] = -s;
        t.data[1 * 4 + 0] = s;
        t.data[1 * 4 + 1] = c;
        break;

    default:
        break;
    }

    mat4x4f_t tmp = { 0 };
    math_matrix_mult4x4(&t, a, &tmp);
    memcpy(a->data, tmp.data, 16 * sizeof(float));
}


void math_matrix_rotate4x4_x(mat4x4f_t* a, float deg)
{
    _matrix_rotate_plane4x4(a, deg, AXIS_X);
}


void math_matrix_rotate4x4_y(mat4x4f_t* a, float deg)
{
    _matrix_rotate_plane4x4(a, deg, AXIS_Y);
}

 
void math_matrix_rotate4x4_z(mat4x4f_t* a, float deg)
{
    _matrix_rotate_plane4x4(a, deg, AXIS_Z);
}


void math_matrix_rotate4x4(mat4x4f_t* a, float degx, float degy, float degz)
{
    math_matrix_rotate4x4_x(a, degx);
    math_matrix_rotate4x4_y(a, degy);
    math_matrix_rotate4x4_z(a, degz);
}


static void _matrix_scale4x4(mat4x4f_t* a, float w, _axis_e axis)
{
    mat4x4f_t t = MATH_MATRIX_IDENTITY_4x4f;

    switch (axis)
    {
    case AXIS_X:
        t.data[0 * 4 + 0] = w;
        break;

    case AXIS_Y:
        t.data[1 * 4 + 1] = w;
        break;

    case AXIS_Z:
        t.data[2 * 4 + 2] = w;
        break;

    default:
        break;
    }

    mat4x4f_t tmp = { 0 };
    math_matrix_mult4x4(&t, a, &tmp);
    memcpy(a->data, tmp.data, 16 * sizeof(float));
}


void math_matrix_scale4x4_x(mat4x4f_t* a, float x)
{
    _matrix_scale4x4(a, x, AXIS_X);
}


void math_matrix_scale4x4_y(mat4x4f_t* a, float y)
{
    _matrix_scale4x4(a, y, AXIS_Y);
}


void math_matrix_scale4x4_z(mat4x4f_t* a, float z)
{
    _matrix_scale4x4(a, z, AXIS_Z);
}


void math_matrix_scale4x4(mat4x4f_t* a, float w)
{
    mat4x4f_t t = {
        w, 0, 0, 0,
        0, w, 0, 0,
        0, 0, w, 0,
        0, 0, 0, 1
    };

    mat4x4f_t tmp = { 0 };
    math_matrix_mult4x4(&t, a, &tmp);
    memcpy(a->data, tmp.data, 16 * sizeof(float));
}