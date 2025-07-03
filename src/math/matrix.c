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


void math_matrix_mult(Matf* a, Matf* b, Matf* c)
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


void math_matrix_mult4x4(Matf4x4* a, Matf4x4* b, Matf4x4* c)
{
    Matf _a = { a->data, 4, 4 };
    Matf _b = { b->data, 4, 4 };
    Matf _c = { c->data, 4, 4 };

    math_matrix_mult(&_a, &_b, &_c);
}


static void _matrix_translate4x4(Matf4x4* a, float d, _axis_e axis)
{
    Matf4x4 t = MATH_MATRIX_IDENTITY_4x4f;
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

    Matf4x4 tmp = { 0 };
    math_matrix_mult4x4(&t, a, &tmp);
    memcpy(a->data, tmp.data, 16 * sizeof(float));
}


void math_matrix_translate4x4_x(Matf4x4* a, float dx)
{
    _matrix_translate4x4(a, dx, AXIS_X);
}


void math_matrix_translate4x4_y(Matf4x4* a, float dy)
{
    _matrix_translate4x4(a, dy, AXIS_Y);
}


void math_matrix_translate4x4_z(Matf4x4* a, float dz)
{
    _matrix_translate4x4(a, dz, AXIS_Z);
}


void math_matrix_translate4x4(Matf4x4* a, float dx, float dy, float dz)
{
    math_matrix_translate4x4_x(a, dx);
    math_matrix_translate4x4_y(a, dy);
    math_matrix_translate4x4_z(a, dz);
}


static void _matrix_rotate_plane4x4(Matf4x4* a, float deg, _axis_e axis)
{
    Matf4x4 t = MATH_MATRIX_IDENTITY_4x4f;
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

    Matf4x4 tmp = { 0 };
    math_matrix_mult4x4(&t, a, &tmp);
    memcpy(a->data, tmp.data, 16 * sizeof(float));
}


void math_matrix_rotate4x4_x(Matf4x4* a, float deg)
{
    _matrix_rotate_plane4x4(a, deg, AXIS_X);
}


void math_matrix_rotate4x4_y(Matf4x4* a, float deg)
{
    _matrix_rotate_plane4x4(a, deg, AXIS_Y);
}

 
void math_matrix_rotate4x4_z(Matf4x4* a, float deg)
{
    _matrix_rotate_plane4x4(a, deg, AXIS_Z);
}


void math_matrix_rotate4x4(Matf4x4* a, float degx, float degy, float degz)
{
    math_matrix_rotate4x4_x(a, degx);
    math_matrix_rotate4x4_y(a, degy);
    math_matrix_rotate4x4_z(a, degz);
}


static void _matrix_scale4x4(Matf4x4* a, float w, _axis_e axis)
{
    Matf4x4 t = MATH_MATRIX_IDENTITY_4x4f;

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

    Matf4x4 tmp = { 0 };
    math_matrix_mult4x4(&t, a, &tmp);
    memcpy(a->data, tmp.data, 16 * sizeof(float));
}


void math_matrix_scale4x4_x(Matf4x4* a, float x)
{
    _matrix_scale4x4(a, x, AXIS_X);
}


void math_matrix_scale4x4_y(Matf4x4* a, float y)
{
    _matrix_scale4x4(a, y, AXIS_Y);
}


void math_matrix_scale4x4_z(Matf4x4* a, float z)
{
    _matrix_scale4x4(a, z, AXIS_Z);
}


void math_matrix_scale4x4(Matf4x4* a, float w)
{
    Matf4x4 t = {
        w, 0, 0, 0,
        0, w, 0, 0,
        0, 0, w, 0,
        0, 0, 0, 1
    };

    Matf4x4 tmp = { 0 };
    math_matrix_mult4x4(&t, a, &tmp);
    memcpy(a->data, tmp.data, 16 * sizeof(float));
}


Matf4x4 math_matrix_lookat(Vec3f from, Vec3f to)
{
    Vec3f global_up = { 0.0f, 1.0f, 0.0f };
    Vec3f f = math_vector_normalize(math_vector_sub(to, from));
    Vec3f r = math_vector_normalize(math_vector_cross(global_up, f));
    Vec3f u = math_vector_normalize(math_vector_cross(r, f));

    return (Matf4x4) {
        r.x, u.x, f.x, -math_vector_dot(r, from),
        r.y, u.y, f.y, -math_vector_dot(u, from),
        r.z, u.z, f.z, -math_vector_dot(f, from),
        0,   0,   0,   1
    };
}