#version 460 core

out vec4 color;
in vec3 _color;

void main(void)
{
	color = vec4(_color, 1.0f);
}