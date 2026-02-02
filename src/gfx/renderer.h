#pragma once
#include "util/defines.h"
#include "camera.h"
#include "quad.h"

#define MAX_QUADS 2048

enum shader_types
{
    SHADER_QUAD,
    N_SHADERS
};

struct renderer
{
    u32 shaders[N_SHADERS];
    enum shader_types active_shader;
    u32 quad_vao, quad_vbo, instance_vbo;

    struct quad render_queue[MAX_QUADS];
    u64 quad_count;
};

void renderer_init(struct renderer* r);
void renderer_deinit(struct renderer* r);

void render_pass_begin(struct renderer* r);
void render_pass_end(struct renderer* r);

void renderer_flush(struct renderer* r);

void render_quad(struct renderer* r, struct quad q);

void renderer_set_camera(struct renderer* r, struct camera* c);