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