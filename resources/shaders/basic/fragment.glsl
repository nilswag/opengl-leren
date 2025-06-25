#version 460 core

in vec3 color;

out vec4 _color;

uniform float multiplier;

void main(void)
{
	_color = vec4(multiplier * color, 1.0f);
}