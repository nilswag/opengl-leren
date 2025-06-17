#version 460 core

out vec4 color;

in vec3 _color;
in vec2 _texCoords;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	color = mix(texture(texture0, _texCoords), texture(texture1, _texCoords), 0.2f);
}