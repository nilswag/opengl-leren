#pragma once
#include "util/defines.h"

typedef f32 Mat2f[4];
typedef f32 Mat3f[9];
typedef f32 Matf[];

typedef f32 Vec2f[2];
typedef f32 Vec3f[3];
typedef f32 Vecf[];

void matf_identity(Matf mat, u64 rows, u64 cols);
void matf_mult(const Matf a, const Matf b, Matf c, u64 a_rows, u64 a_cols, u64 b_rows, u64 b_cols);

void mat2f_transform(Mat3f a, f32 tx, f32 ty, f32 rot, f32 sx, f32 sy);