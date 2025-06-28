#pragma once
#include <stddef.h>
#include <glad/glad.h>

typedef struct
{
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    size_t index_count;
} mesh_t;

// TODO: Add support for dynamic vertex attributes.
void gfx_mesh_init(mesh_t* mesh, float* vertices, size_t vertex_count, unsigned int* indices, size_t index_count);
void gfx_mesh_render(mesh_t* mesh);
void gfx_mesh_free(mesh_t* mesh);