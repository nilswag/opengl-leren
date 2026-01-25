#include "matrix.h"
#include "util/defines.h"
#include "util/log.h"

void matf_identity_dynamic(Matf mat, u64 rows, u64 cols)
{
    for (u64 i = 0; i < rows; i++)
        for (u64 j = 0; j < cols; j++)
            mat[i * cols + j] = (i == j) ? 1.0f : 0.0f;
}

void matf_mult_dynamic(const Matf a, const Matf b, Matf c, u64 a_rows, u64 a_cols, u64 b_rows, u64 b_cols)
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