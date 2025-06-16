#pragma once
#include <iostream>
#include <glad/glad.h>

namespace gfx
{
	class Shader
	{
	public:
		unsigned int id;

		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

		inline void use() const
		{
			glUseProgram(id);
		}

		inline void setBool(const std::string& name, bool value) const
		{
			unsigned int location = glGetUniformLocation(id, name.c_str());
			glUniform1i(location, value);
		}

		inline void setInt(const std::string& name, int value) const
		{
			unsigned int location = glGetUniformLocation(id, name.c_str());
			glUniform1i(location, value);
		}

		inline void setFloat(const std::string& name, float value) const
		{
			unsigned int location = glGetUniformLocation(id, name.c_str());
			glUniform1f(location, value);
		}

	};
}
