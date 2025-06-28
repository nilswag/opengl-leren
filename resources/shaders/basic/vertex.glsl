#version 460 core

layout (location = 0) in vec3 pos;

uniform mat4 transform;

void main(void)
{
	gl_Position = transform * vec4(pos, 1.0f);
}