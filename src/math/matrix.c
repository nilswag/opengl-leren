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


void math_matrix_mult(float* a, size_t a_rows, size_t a_cols, float* b, size_t b_rows, size_t b_cols, float* c)
{
    if (a_cols != b_rows)
    {
        fputs("Incompatible matrix sizes.", stderr);
        return;
    }

    for (size_t i = 0; i < a_rows; i++)
    {
        for (size_t j = 0; j < b_cols; j++)
        {
            c[i * b_cols + j] = 0;
            for (size_t k = 0; k < a_cols; k++)
            {
                c[i * b_cols + j] += a[i * a_cols + k] * b[k * b_cols + j];
            }
        }
    }
}



void math_matrix_mult_4x4(float* a, float* b, float* c)
{
    math_matrix_mult(a, 4, 4, b, 4, 4, c);
}


static void _matrix_translate(float* a, float d, _axis_e axis)
{
    float t[] = MATH_MATRIX_IDENTITY;
    switch (axis)
    {
    case AXIS_X:
        t[0 * 4 + 3] = d;
        break;

    case AXIS_Y:
        t[1 * 4 + 3] = d;
        break;

    case AXIS_Z:
        t[2 * 4 + 3] = d;
        break;

    default:
        break;
    }

    float tmp[16];
    math_matrix_mult_4x4(t, a, tmp);
    memcpy(a, tmp, 16 * sizeof(float));
}


void math_matrix_translate_x(float* a, float dx)
{
    _matrix_translate(a, dx, AXIS_X);
}


void math_matrix_translate_y(float* a, float dy)
{
    _matrix_translate(a, dy, AXIS_Y);
}


void math_matrix_translate_z(float* a, float dz)
{
    _matrix_translate(a, dz, AXIS_Z);
}


void math_matrix_translate(float* a, float dx, float dy, float dz)
{
    math_matrix_translate_x(a, dx);
    math_matrix_translate_y(a, dy);
    math_matrix_translate_z(a, dz);
}


static void _matrix_rotate_plane(float* a, float deg, _axis_e axis)
{
    float t[] = MATH_MATRIX_IDENTITY;
    float rad = MATH_DEGREE_TO_RADIAN(deg);
    float c = cosf(rad);
    float s = sinf(rad);

    switch (axis)
    {
    case AXIS_X:
        t[1 * 4 + 1] = c;
        t[1 * 4 + 2] = -s;
        t[2 * 4 + 1] = s;
        t[2 * 4 + 2] = c;
        break;

    case AXIS_Y:
        t[0 * 4 + 0] = c;
        t[0 * 4 + 2] = s;
        t[2 * 4 + 0] = -s;
        t[2 * 4 + 2] = c;
        break;

    case AXIS_Z:
        t[0 * 4 + 0] = c;
        t[0 * 4 + 1] = -s;
        t[1 * 4 + 0] = s;
        t[1 * 4 + 1] = c;
        break;

    default:
        break;
    }

    float tmp[16];
    math_matrix_mult_4x4(t, a, tmp);
    memcpy(a, tmp, 16 * sizeof(float));
}


void math_matrix_rotate_x(float* a, float deg)
{
    _matrix_rotate_plane(a, deg, AXIS_X);
}


void math_matrix_rotate_y(float* a, float deg)
{
    _matrix_rotate_plane(a, deg, AXIS_Y);
}

 
void math_matrix_rotate_z(float* a, float deg)
{
    _matrix_rotate_plane(a, deg, AXIS_Z);
}


void math_matrix_rotate(float* a, float degx, float degy, float degz)
{
    math_matrix_rotate_x(a, degx);
    math_matrix_rotate_y(a, degy);
    math_matrix_rotate_z(a, degz);
}


static void _matrix_scale(float* a, float w, _axis_e axis)
{
    float t[] = MATH_MATRIX_IDENTITY;

    switch (axis)
    {
    case AXIS_X:
        t[0 * 4 + 0] = w;
        break;

    case AXIS_Y:
        t[1 * 4 + 1] = w;
        break;

    case AXIS_Z:
        t[2 * 4 + 2] = w;
        break;

    default:
        break;
    }

    float tmp[16];
    math_matrix_mult_4x4(t, a, tmp);
    memcpy(a, tmp, 16 * sizeof(float));
}


void math_matrix_scale_x(float* a, float x)
{
    _matrix_scale(a, x, AXIS_X);
}


void math_matrix_scale_y(float* a, float y)
{
    _matrix_scale(a, y, AXIS_Y);
}


void math_matrix_scale_z(float* a, float z)
{
    _matrix_scale(a, z, AXIS_Z);
}


void math_matrix_scale(float* a, float w)
{
    float t[] = {
        w, 0, 0, 0,
        0, w, 0, 0,
        0, 0, w, 0,
        0, 0, 0, 1
    };

    float tmp[16];
    math_matrix_mult_4x4(t, a, tmp);
    memcpy(a, tmp, 16 * sizeof(float));
}