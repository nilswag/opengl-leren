#include <string.h>
#include <math.h>

#include "math/matrix.h"

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

void math_matrix_translate(float* a, float x, float y, float z)
{
    float b[] = {
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    };

    float tmp[16];
    math_matrix_mult(a, b, tmp);
    memcpy(a, tmp, 16 * sizeof(float));
}

void math_matrix_rotate(float* a, float x, float y, float z)
{
    const float RATIO = 3.14159265358979323846 / 180;
    x *= RATIO;
    y *= RATIO;
    z *= RATIO;

    float b[] = {
        cosf(z) * cosf(y), cosf(z) * sinf(y) * sinf(x) - sinf(z) * cosf(x), cosf(z) * sinf(y) * cosf(x) + sinf(z) * sinf(x), 0.0f,
        sinf(z) * cosf(y), sinf(z) * sinf(y) * sinf(x) + cosf(z) * cosf(x), sinf(z) * sinf(y) * cosf(x) - cosf(z) * sinf(x), 0.0f,
       -sinf(y),           cosf(y) * sinf(x),                               cosf(y) * cosf(x),                               0.0f,
        0.0f,              0.0f,                                            0.0f,                                            1.0f
    };

    float tmp[16];
    math_matrix_mult(a, b, tmp);
    memcpy(a, tmp, 16 * sizeof(float));
}