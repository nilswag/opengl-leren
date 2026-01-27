#include <math.h>
#include "linmath.h"
#include "util/defines.h"
#include "util/log.h"

void matf_identity_dynamic(matf mat, u64 rows, u64 cols)
{
    for (u64 i = 0; i < rows; i++)
        for (u64 j = 0; j < cols; j++)
            mat[i * cols + j] = (i == j) ? 1.0f : 0.0f;
}

void matf_mult_dynamic(const matf a, const matf b, matf c, u64 a_rows, u64 a_cols, u64 b_rows, u64 b_cols)
{
    ASSERT(a_cols == b_rows, "matrices can not be multiplied\n");

    for (u64 i = 0; i < a_rows; i++)
    {
        for (u64 j = 0; j < b_cols; j++)
        {
            f32 sum = 0.0f;
            for (u64 k = 0; k < a_rows; k++)
                sum += a[i * a_cols + k] * b[k * b_cols + j];
            c[i * b_cols + j] = sum;
        }
    }
}

void mat2f_transform(mat3f a, f32 tx, f32 ty, f32 rot, f32 sx, f32 sy)
{
    f32 s = sin(rot);
    f32 c = cos(rot);

    a[0] = sx * s; a[1] = sy * -s; a[2] = tx;
    a[3] = sx * s; a[4] = sy * c;  a[5] = ty;
    a[6] = 0.0f;   a[7] = 0.0f;    a[8] = 1.0f;
}