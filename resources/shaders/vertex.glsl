#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoords;

out vec3 _color;
out vec2 _texCoords;

void main()
{
	gl_Position = vec4(pos, 1.0f);
	_color = color;
	_texCoords = texCoords;
}