#pragma once
#include "util/core/defines.h"
#include "math/linmath.h"
#include "../camera/camera.h"

#define MAX_QUADS 256
#define INSTANCE_SIZE 13

typedef enum pass_type
{
    PASS_WORLD,
    N_PASSES
} pass_type;

typedef struct quad
{
    vec2f pos;
    vec2f size;
    f32 rot;
    vec4f color;
} quad;

typedef struct render_pass
{
    u32 shader;
    u32 vao, instance_vbo;
    u64 count;
    f32 queue[MAX_QUADS][INSTANCE_SIZE];
} render_pass;

typedef struct renderer
{
    render_pass passes[N_PASSES];
} renderer;

void renderer_init(renderer* r);

void renderer_begin(renderer* r);
void renderer_submit(renderer* r, pass_type pass, quad instance);
void renderer_flush_pass(renderer* r, pass_type pass);
void renderer_end(renderer* r);

void renderer_set_camera(renderer* r, pass_type pass, camera* camera);