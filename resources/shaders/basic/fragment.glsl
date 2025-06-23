#version 460 core

in vec3 color;

out vec4 _color;

void main(void)
{
	_color = vec4(color, 1.0f);
}