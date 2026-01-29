#pragma once
#include "util/defines.h"

#define MAX_QUADS 1024

struct quad
{
    f32 x, y;
    f32 w, h;
    f32 rotation;
};

struct renderer
{
    u32 quad_shader;
    u32 quad_vao, quad_vbo, instance_vbo;

    struct quad render_queue[MAX_QUADS];
    u64 quad_count;
};

void renderer_init(struct renderer* r);
void renderer_deinit(struct renderer* r);
void render_pass_begin(struct renderer* r);
void render_pass_end(struct renderer* r);
void renderer_flush(struct renderer* r);
void render_quad(struct renderer* r, struct quad quad);