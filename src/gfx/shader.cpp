#include <vector>
#include <glad/glad.h>

#include "shader.h"
#include "util/util.h"

static unsigned int compileShader(GLenum type, const std::string& _src)
{
	unsigned int shader = glCreateShader(type);
	const char* src = _src.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetShaderInfoLog(shader, length, nullptr, log.data());
		std::cerr << "Failed to compile shader: " << log.data() << std::endl;
	}

	return shader;
}

gfx::Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	id = glCreateProgram();

	unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexSrc);
	unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	int success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		int length = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetProgramInfoLog(id, length, nullptr, log.data());
		std::cerr << "Failed to link shader program: " << log.data() << std::endl;
	}
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void gfx::Shader::use()
{
	glUseProgram(id);
}

