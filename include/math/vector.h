#pragma once


typedef struct
{
    float x, y, z;
} vec3f_t;


float math_vector_dot(vec3f_t* a, vec3f_t* b);
vec3f_t math_vector_cross(vec3f_t* a, vec3f_t* b);