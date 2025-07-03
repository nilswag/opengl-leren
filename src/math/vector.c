#include "math/vector.h"


float math_vector_dot(vec3f_t* a, vec3f_t* b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}


vec3f_t math_vector_cross(vec3f_t* a, vec3f_t* b)
{

}