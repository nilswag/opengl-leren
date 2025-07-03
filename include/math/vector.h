#pragma once


typedef struct
{
    float x, y, z;
} Vec3f;


Vec3f math_vector_add(Vec3f a, Vec3f b);
Vec3f math_vector_sub(Vec3f a, Vec3f b);
Vec3f math_vector_normalize(Vec3f a);
float math_vector_dot(Vec3f a, Vec3f b);
Vec3f math_vector_cross(Vec3f a, Vec3f b);