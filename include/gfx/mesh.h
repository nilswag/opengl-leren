#pragma once
#include <stddef.h>
#include <glad/glad.h>

typedef struct
{
    GLsizei size;
    GLenum type;
    GLboolean normalized;
    size_t offset;
} vertex_attribute_t;

typedef struct
{
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLsizei index_count;
} mesh_t;

void gfx_mesh_init(mesh_t* mesh, unsigned int* indices, GLsizei index_count, vertex_attribute_t* attributes, size_t attribute_count, float* vertex_data, size_t vertex_count, GLsizei stride);
void gfx_mesh_render(mesh_t* mesh);
void gfx_mesh_free(mesh_t* mesh);