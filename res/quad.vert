#version 460 core

layout (location = 0) in vec3 pos;

layout (location = 1) in vec3 col0;
layout (location = 2) in vec3 col1;
layout (location = 3) in vec3 col2;

void main()
{
    mat3 model = mat3(col0, col1, col2);
    gl_Position = vec4(model * pos, 1.0);
}
