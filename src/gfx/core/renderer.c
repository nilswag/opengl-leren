#include <glad/glad.h>
#include <stdlib.h>
#include <string.h>
#include "renderer.h"
#include "../camera/camera.h"
#include "math/linmath.h"
#include "../shader/shader.h"

static f32 vertices[] = {
    0.0f, 0.0f,     // top left
    1.0f, 0.0f,     // top right
    1.0f, 1.0f,     // bottom right
    0.0f, 1.0f      // bottom left
};

static u32 indices[] = {
    0, 1, 2,
    0, 2, 3
};

static u32 quad_vao, quad_vbo, quad_ebo;

static u32 _create_instance_vbo()
{
    u32 vbo;    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * INSTANCE_SIZE * MAX_QUADS, NULL, GL_DYNAMIC_DRAW);
    // model matrix
    for (u64 i = 0; i < 3; i++)
    {
        glVertexAttribPointer(1 + i, 3, GL_FLOAT, GL_FALSE, sizeof(f32) * INSTANCE_SIZE, (void*)(sizeof(vec3f) * i));
        glVertexAttribDivisor(1 + i, 1);
        glEnableVertexAttribArray(i + 1);
    }

    // color
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(f32) * INSTANCE_SIZE, (void*)(sizeof(mat3f)));
    glVertexAttribDivisor(4, 1);
    glEnableVertexAttribArray(4);

    return vbo;
}

void renderer_init(struct renderer* r)
{
    glGenVertexArrays(1, &quad_vao);
    glBindVertexArray(quad_vao);

    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2f), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &quad_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    r->passes[PASS_WORLD] = (struct render_pass) {
        .shader = create_shader("quad.vert", "quad.frag"),
        .vao = quad_vao,
        .instance_vbo = _create_instance_vbo(),
        .count = 0,
    };

    glBindVertexArray(0);
}

void renderer_begin(struct renderer* r)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_submit(struct renderer* r, enum pass_type pass, struct quad instance)
{
    struct render_pass* p = &r->passes[pass];
    if (p->count >= MAX_QUADS) renderer_flush_pass(r, pass);

    f32* dst = p->queue[p->count++];

    mat3f model;
    mat3f_model(model, instance.pos, instance.size, instance.rot);

    memcpy(dst, model, sizeof(mat3f));
    memcpy(dst + 9, instance.color, sizeof(vec4f));
}

void renderer_flush_pass(struct renderer* r, enum pass_type pass)
{
    struct render_pass* p = &r->passes[pass];
    if (p->count == 0) return; // queue is empty

    glBindBuffer(GL_ARRAY_BUFFER, p->instance_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, p->count * INSTANCE_SIZE * sizeof(f32), p->queue);

    glBindVertexArray(p->vao);
    glUseProgram(p->shader);

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, p->count);

    glUseProgram(0);
    glBindVertexArray(0);

    p->count = 0;   
}

void renderer_flush(struct renderer* r)
{
    for (u64 i = 0; i < N_PASSES; i++)
        renderer_flush_pass(r, i);
}

void renderer_set_camera(struct renderer* r, enum pass_type pass, struct camera* camera)
{
    struct render_pass* p = &r->passes[pass];
    glUseProgram(p->shader);
    glUniformMatrix3fv(glGetUniformLocation(p->shader, "view"), 1, GL_FALSE, camera->view);
    glUniformMatrix3fv(glGetUniformLocation(p->shader, "proj"), 1, GL_FALSE, camera->proj);
}