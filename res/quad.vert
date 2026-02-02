#version 460 core

layout(location = 0) in vec2 i_pos;

layout(location = 1) in vec3 i_col0;
layout(location = 2) in vec3 i_col1;
layout(location = 3) in vec3 i_col2;

layout(location = 4) in vec4 i_color;

out vec4 o_color;

uniform mat3 proj;
uniform mat3 view;

void main()
{
    mat3 model = mat3(i_col0, i_col1, i_col2);
    gl_Position = vec4(proj * view * model * vec3(i_pos, 1.0), 1.0);
    o_color = i_color;
}
