#include <glad/glad.h>
#include "renderer.h"
#include "util/defines.h"
#include "shader.h"

void render_init(struct renderer* r)
{
    f32 vertices[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    u32 indices[] = {
        0, 1, 2, 3
    };

    r->quad_shader = create_shader("quad.vert", "quad.frag");
    glGenVertexArrays(1, &r->vao);
    glBindVertexArray(r->vao);

    glGenBuffers(1, &r->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices)
}

void renderer_deinit(struct renderer* r)
{
    glDeleteShader(r->quad_shader);
}

void render_pass_begin(struct renderer* r)
{
    glUseProgram(r->quad_shader);
}

void render_pass_end(struct renderer* r)
{

}

void render_quad(struct renderer* r, struct quad quad, f32 color[3])
{
    if (r->quad_count >= MAX_QUADS) renderer_flush(r);

    r->render_queue[r->quad_count] = quad;
    r->quad_count++;
}