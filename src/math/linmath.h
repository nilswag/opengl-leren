#pragma once
#include "util/defines.h"

typedef f32 mat2f[4];
typedef f32 mat3f[9];
typedef f32 matf[];

typedef f32 vec2f[2];
typedef f32 vec3f[3];
typedef f32 vecf[];

void matf_identity(matf mat, u64 rows, u64 cols);
void matf_mult(const matf a, const matf b, matf c, u64 a_rows, u64 a_cols, u64 b_rows, u64 b_cols);

void mat2f_model(mat3f a, f32 tx, f32 ty, f32 rot, f32 sx, f32 sy);