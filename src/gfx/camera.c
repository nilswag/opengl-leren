#include "camera.h"
#include "math/linmath.h"

void camera_init(struct camera* c, vec2 screen_size)
{
    c->zoom = 1.0f;
    mat3f_ortho(c->proj, 0, screen_size[0], 0, screen_size[1]);
    mat3f_identity(c->view);
}

void camera_update(struct camera* c)
{
    mat3f_transform(c->view, c->position, (vec2f) { c->zoom, c->zoom }, 0.0f);
}