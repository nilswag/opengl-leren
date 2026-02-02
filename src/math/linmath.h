#pragma once
#include "util/defines.h"

typedef f32 mat3f[9];
typedef f32 matf[];

typedef f32 vec2f[2];
typedef f32 vec3f[3];
typedef f32 vecf[];

typedef i32 vec2[2];
typedef i32 vec3[3];
typedef i32 vec[];

void mat3f_transform(mat3f a, f32 tx, f32 ty, f32 rot, f32 sx, f32 sy);

static inline void mat3f_model(mat3f a, f32 tx, f32 ty, f32 rot, f32 sx, f32 sy)
{
    mat3f_transform(a, tx, ty, rot, sx, sy);
}

void mat3f_ortho(mat3f a, f32 l, f32 r, f32 b, f32 t);

void mat3f_identity(mat3f a);
