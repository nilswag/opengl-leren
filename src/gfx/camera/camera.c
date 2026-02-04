#include "camera.h"

void camera_init(camera* c, vec2 screen_size)
{
    c->zoom = 1.0f;
    mat3f_ortho(c->proj, 0, screen_size[0], 0, screen_size[1]);
    mat3f_identity(c->view);
}

void camera_update(camera* c)
{
    mat3f_transform(c->view, (vec2f) { -c->position[0], -c->position[1] }, (vec2f) { c->zoom, c->zoom }, 0.0f);
}