#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec3 _color;

uniform mat4 model;
uniform mat4 view;

void main(void)
{
	gl_Position = view * model * vec4(pos, 1.0f);
    _color = color;
}