#include "camera.h"
#include "math/linmath.h"
#include "state.h"

void camera_init(struct camera* c, vec2 window_size)
{
    mat3f_ortho(c->proj, 0, window_size[0], 0, window_size[1]);
    mat3f_identity(c->view);
}

void camera_update(struct camera* c)
{
    mat3f_transform(c->view, c->position, (vec2f) { c->zoom, c->zoom }, 0.0f);
}