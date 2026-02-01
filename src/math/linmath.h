#pragma once
#include "util/defines.h"

typedef f32 mat3f[9];
typedef f32 matf[];

typedef f32 vec2f[2];
typedef f32 vec3f[3];
typedef f32 vecf[];

void mat3f_model(mat3f a, f32 tx, f32 ty, f32 rot, f32 sx, f32 sy);
void mat3f_ortho();