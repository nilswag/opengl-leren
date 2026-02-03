#pragma once
#include "util/core/defines.h"
#include "math/linmath.h"
#include "../camera/camera.h"

#define MAX_QUADS 256
#define INSTANCE_SIZE 13

typedef enum
{
    PASS_WORLD,
    N_PASSES
} PassType;

typedef struct
{
    vec2f pos;
    vec2f size;
    f32 rot;
    vec4f color;
} Quad;

typedef struct
{
    u32 shader;
    u32 vao, instance_vbo;
    u64 count;
    f32 queue[MAX_QUADS][INSTANCE_SIZE];
} RenderPass;

typedef struct
{
    RenderPass passes[N_PASSES];
} Renderer;

void renderer_init(Renderer* r);

void renderer_begin(Renderer* r);
void renderer_submit(Renderer* r, PassType pass, Quad instance);
void renderer_flush_pass(Renderer* r, PassType pass);
void renderer_end(Renderer* r);

void renderer_set_camera(Renderer* r, PassType pass, Camera* camera);