#pragma once
#include "util/defines.h"

typedef f32 Mat2x2f[4];
typedef f32 Mat3x3f[9];
typedef f32 Mat4x4f[16];
typedef f32 Matf[];

void _mat_zero_dynamic(Matf mat, u64 rows, u64 cols);
