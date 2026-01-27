#include <glad/glad.h>
#include "renderer.h"
#include "util/defines.h"
#include "shader.h"
#include "math/linmath.h"

void renderer_init(struct renderer* r)
{
    f32 vertices[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    u32 indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    r->quad_shader = create_shader("quad.vert", "quad.frag");

    glGenVertexArrays(1, &r->quad_vao);
    glBindVertexArray(r->quad_vao);
    
    // bind quad data and set attributes
    glGenBuffers(1, &r->quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, r->quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(f32) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    // bind ebo
    u32 ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // bind instance data, set attributes and allocate gpu memory
    glGenBuffers(1, &r->instance_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, r->instance_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mat3f) * MAX_QUADS, NULL, GL_DYNAMIC_DRAW);
    for (i32 i = 0; i < 3; i++)
    {
        glVertexAttribPointer(1 + i, 3, GL_FLOAT, GL_FALSE, sizeof(mat3f), (void*)(i * sizeof(vec3f)));
        glEnableVertexAttribArray(i + 1);   // enable the vertex attribute for each matrix column
        glVertexAttribDivisor(1 + i, 1);    // set attrib divisor to per instance instead of per vertex
    }

    glBindVertexArray(0);
}

void renderer_deinit(struct renderer* r)
{
    glDeleteShader(r->quad_shader);
}

void render_pass_begin(struct renderer* r)
{
    glUseProgram(r->quad_shader);
    glBindVertexArray(r->quad_vao);
}

void render_pass_end(struct renderer* r)
{
    glUseProgram(0);
    glBindVertexArray(0);
}

void renderer_flush(struct renderer* r)
{
    mat3f instances[MAX_QUADS];

    for (u64 i = 0; i < r->quad_count; i++)
    {
        struct quad q = r->render_queue[i];
        mat2f_model(instances[i], q.x, q.y, q.rotation, q.w, q.h);
    }

    glBindBuffer(GL_ARRAY_BUFFER, r->instance_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, r->quad_count * sizeof(mat3f), instances);

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, r->quad_count);

    r->quad_count = 0;
}

void render_quad(struct renderer* r, struct quad quad)
{
    if (r->quad_count >= MAX_QUADS) renderer_flush(r);

    r->render_queue[r->quad_count] = quad;
    r->quad_count++;
}