#include <string.h>

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