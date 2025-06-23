#pragma once
#include <glad/glad.h>

typedef struct
{
	GLuint id;
	GLuint vertex_id;
	GLuint fragment_id;
} Shader;

Shader gfx_shader_init(const char* vertex_src, const char* fragment_src);
void gfx_shader_use(Shader* shader);
void gfx_shader_destroy(Shader* shader);