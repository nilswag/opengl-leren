#include "math/matrix.h"

void _mat_zero_dynamic(Matf mat, u64 rows, u64 cols)
{
    for (u64 i = 0; i < rows; i++)
        for (u64 j = 0; j < cols; j++)
            mat[i * rows + j] = 0.0f;
}
