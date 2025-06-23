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

void gfx_shader_set_int(Shader* shader, const char* name, int value);
void gfx_shader_set_float(Shader* shader, const char* name, float value);
void gfx_shader_set_bool(Shader* shader, const char* name, int value);
