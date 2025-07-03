#include <math.h>

#include "math/vector.h"


Vec3f math_vector_add(Vec3f a, Vec3f b)
{
    return (Vec3f) {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}


Vec3f math_vector_sub(Vec3f a, Vec3f b)
{
    return (Vec3f) {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}


Vec3f math_vector_normalize(Vec3f a)
{
    float magnitude = sqrtf(math_vector_dot(a, a));
    return (Vec3f) { a.x / magnitude, a.y / magnitude, a.z / magnitude };
}


float math_vector_dot(Vec3f a, Vec3f b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}


Vec3f math_vector_cross(Vec3f a, Vec3f b)
{
    return (Vec3f) {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}