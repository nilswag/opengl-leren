#pragma once
#include <stddef.h>
#include <glad/glad.h>

typedef struct
{
    GLsizei size;
    GLenum type;
    GLboolean normalized;
    size_t offset;
} VertexAttribute;

typedef struct
{
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLsizei index_count;
} Mesh;

void gfx_mesh_init(Mesh* mesh, unsigned int* indices, GLsizei index_count, VertexAttribute* attributes, size_t attribute_count, float* vertex_data, size_t vertex_count, GLsizei stride);
void gfx_mesh_render(Mesh* mesh);
void gfx_mesh_free(Mesh* mesh);