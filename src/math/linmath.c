#include <math.h>
#include "linmath.h"
#include "util/defines.h"

// column major
void mat3f_model(mat3f a, f32 tx, f32 ty, f32 rot, f32 sx, f32 sy)
{
    f32 s = sin(rot);
    f32 c = cos(rot);

    a[0] = sx * c; a[3] = sy * -s; a[6] = tx;
    a[1] = sx * s; a[4] = sy * c;  a[7] = ty;
    a[2] = 0.0f;   a[5] = 0.0f;    a[8] = 1.0f;
}

// column major
void mat3f_ortho(mat3f a, f32 l, f32 r, f32 b, f32 t)
{
    a[0] = 2 / (r - l); a[3] = 0;           a[6] = -((r + l) / (r - l));
    a[1] = 0;           a[4] = 2 / (t - b); a[7] = -((t + b) / (t - b));
    a[2] = 0;           a[5] = 0;           a[8] = 1;
}