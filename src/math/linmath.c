#include <math.h>
#include "linmath.h"
#include "util/core/defines.h"

// column major
void mat3f_transform(mat3f a, vec2f pos, vec2f scale, f32 rot)
{
    f32 s = sin(rot);
    f32 c = cos(rot);

    a[0] = scale[0] * c; a[3] = scale[1] * -s; a[6] = pos[0];
    a[1] = scale[0] * s; a[4] = scale[1] * c;  a[7] = pos[1];
    a[2] = 0.0f;         a[5] = 0.0f;          a[8] = 1.0f;
}

// column major
void mat3f_ortho(mat3f a, f32 l, f32 r, f32 b, f32 t)
{
    a[0] = 2.0f / (r - l); a[3] = 0.0f;           a[6] = -((r + l) / (r - l));
    a[1] = 0.0f;           a[4] = 2.0f / (t - b); a[7] = -((t + b) / (t - b));
    a[2] = 0.0f;           a[5] = 0.0f;           a[8] = 1.0f;
}

// column major
void mat3f_identity(mat3f a)
{
    a[0] = 1.0f; a[3] = 0.0f; a[6] = 0.0f;
    a[1] = 0.0f; a[4] = 1.0f; a[7] = 0.0f;
    a[2] = 0.0f; a[5] = 0.0f; a[8] = 1.0f;
}