#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

#include "gfx/shader.h"

static GLuint compile_shader(const char* shader_src, GLenum type)
{
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &shader_src, NULL);
	glCompileShader(id);

	GLuint success = 1;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLsizei length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* log = malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, NULL, log);
		fprintf(stderr, "Failed to compile shader: \n%s", log);
		free(log);
		glDeleteShader(id);
		return 0;
	}

	return id;
}

shader_t gfx_shader_init(const char* vertex_src, const char* fragment_src)
{
	shader_t s = { 0 };
	s.id = glCreateProgram();
	s.vertex_id = compile_shader(vertex_src, GL_VERTEX_SHADER);
	s.fragment_id = compile_shader(fragment_src, GL_FRAGMENT_SHADER);

	if (!s.vertex_id || !s.fragment_id)
	{
		fputs("Aborting shader creation due to shader compilation failure.\n", stderr);
		return s;
	}

	glAttachShader(s.id, s.vertex_id);
	glAttachShader(s.id, s.fragment_id);
	glLinkProgram(s.id);

	GLuint success = 1;
	glGetProgramiv(s.id, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLsizei length = 0;
		glGetProgramiv(s.id, GL_INFO_LOG_LENGTH, &length);
		char* log = malloc(length * sizeof(char));
		glGetProgramInfoLog(s.id, length, NULL, log);
		fprintf(stderr, "Failed to link shader program: \n%s", log);
		free(log);
	}

	return s;
}

void gfx_shader_use(shader_t* shader)
{
	glUseProgram(shader->id);
}

void gfx_shader_free(shader_t* shader)
{
	glDeleteShader(shader->vertex_id);
	glDeleteShader(shader->fragment_id);
	glDeleteProgram(shader->id);
}

void gfx_shader_set_int(shader_t* shader, const char* name, int value)
{
	GLint location = glGetUniformLocation(shader->id, name);
	glUniform1i(location, value);
}

void gfx_shader_set_float(shader_t* shader, const char* name, float value)
{
	GLint location = glGetUniformLocation(shader->id, name);
	glUniform1f(location, value);
}

void gfx_shader_set_bool(shader_t* shader, const char* name, int value)
{
	gfx_shader_set_int(shader, name, value);
}