#pragma once
#include <iostream>

namespace gfx
{
	class Shader
	{
	public:
		unsigned int id;

		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		void use();
	};
}
