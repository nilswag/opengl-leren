#include <stdlib.h>
#include <stddef.h>
#include <glad/glad.h>

#include "gfx/mesh.h"

void gfx_mesh_init(Mesh* mesh, unsigned int* indices, GLsizei index_count, VertexAttribute* attributes, size_t attribute_count, float* vertex_data, size_t vertex_count, GLsizei stride)
{
    glGenVertexArrays(1, &mesh->vao);
    glGenBuffers(1, &mesh->vbo);
    glGenBuffers(1, &mesh->ebo);

    glBindVertexArray(mesh->vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index_count, indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * stride, vertex_data, GL_STATIC_DRAW);

    for (int i = 0; i < attribute_count; i++)
    {
        VertexAttribute a = attributes[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, a.size, a.type, a.normalized, stride, (const void*)a.offset);
    }

    glBindVertexArray(0);

    mesh->index_count = index_count;
}

void gfx_mesh_render(Mesh* mesh)
{
    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, (const void*)0);
    glBindVertexArray(0);
}

void gfx_mesh_free(Mesh* mesh)
{
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteBuffers(1, &mesh->ebo);
    glDeleteVertexArrays(1, &mesh->vao);
}