#pragma once
#include "util/defines.h"

typedef f32 Mat2f[4];
typedef f32 Mat3f[9];
typedef f32 Mat4f[16];
typedef f32 Matf[];

void matf_identity_dynamic(Matf mat, u64 rows, u64 cols);
void matf_mult_dynamic(const Matf a, const Matf b, const Matf c, u64 a_rows, u64 a_cols, u64 b_rows, u64 b_cols);

#define MAT2F_IDENTITY(mat) STMT(matf_identity_dynamic(mat, 2, 2);)
#define MAT3F_IDENTITY(mat) STMT(matf_identity_dynamic(mat, 3, 3);)
#define MAT4F_IDENTITY(mat) STMT(matf_identity_dynamic(mat, 4, 4);)

#define MAT2F_MULT(a, b, c) STMT(matf_mult_dynamic(a, b, c, 2, 2, 2, 2);)
#define MAT3F_MULT(a, b, c) STMT(matf_mult_dynamic(a, b, c, 3, 3, 3, 3);)
#define MAT4F_MULT(a, b, c) STMT(matf_mult_dynamic(a, b, c, 4, 4, 4, 4);)