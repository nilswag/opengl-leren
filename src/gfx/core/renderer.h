#pragma once
#include "util/core/defines.h"
#include "math/linmath.h"

#define MAX_QUADS 256
#define INSTANCE_SIZE 13

enum pass_type
{
    PASS_WORLD,
    N_PASSES
};

struct quad
{
    vec2f pos;
    vec2f size;
    f32 rot;
    vec4f color;
};

struct render_pass
{
    u32 shader;
    u32 vao, instance_vbo;
    u64 count;
    f32 queue[MAX_QUADS][INSTANCE_SIZE];
};

struct renderer
{
    struct render_pass passes[N_PASSES];
};

void renderer_init(struct renderer* r);
void renderer_deinit(struct renderer* r);

void renderer_begin(struct renderer* r);
void renderer_submit(struct renderer* r, enum pass_type pass, struct quad instance);
void renderer_flush_pass(struct renderer* r, enum pass_type pass);
void renderer_end(struct renderer* r);

struct camera;

void renderer_set_camera(struct renderer* r, enum pass_type pass, struct camera* camera);