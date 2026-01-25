#pragma once
#include "util/defines.h"

typedef f32 Mat2f[4];
typedef f32 Mat3f[9];
typedef f32 Matf[];

void matf_identity_dynamic(Matf mat, u64 rows, u64 cols);
void matf_mult_dynamic(const Matf a, const Matf b, Matf c, u64 a_rows, u64 a_cols, u64 b_rows, u64 b_cols);

void mat2f_transform(Mat3f a, f32 tx, f32 ty, f32 rot, f32 sx, f32 sy);