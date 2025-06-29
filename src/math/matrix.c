#include <string.h>
#include <math.h>

#include "math/matrix.h"

typedef enum
{
    AXIS_X,
    AXIS_Y,
    AXIS_Z
} axis_e;

void math_matrix_mult(float* a, float* b, float* c)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            c[i * 4 + j] = 0;
            for (int k = 0; k < 4; k++)
                c[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
        }
    }
}

void math_matrix_translate(float* a, float dx, float dy, float dz)
{
    float b[] = {
        1, 0, 0, dx,
        0, 1, 0, dy,
        0, 0, 1, dz,
        0, 0, 0, 1
    };

    float tmp[16];
    math_matrix_mult(a, b, tmp);
    memcpy(a, tmp, 16 * sizeof(float));
}

static void matrix_rotate_pane(float* a, float deg, axis_e axis)
{
    float t[] = MATH_IDENTITY_MATRIX_4x4;
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
    math_matrix_mult(t, a, tmp);
    memcpy(a, tmp, 16 * sizeof(float));
}

void math_matrix_rotate_x(float* a, float deg)
{
    matrix_rotate_pane(a, deg, AXIS_X);
}

void math_matrix_rotate_y(float* a, float deg)
{
    matrix_rotate_pane(a, deg, AXIS_Y);
}

void math_matrix_rotate_z(float* a, float deg)
{
    matrix_rotate_pane(a, deg, AXIS_Z);
}

void math_matrix_rotate(float* a, float degx, float degy, float degz)
{
    math_matrix_rotate_x(a, degx);
    math_matrix_rotate_y(a, degy);
    math_matrix_rotate_z(a, degz);
}