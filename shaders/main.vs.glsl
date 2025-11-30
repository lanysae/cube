#version 460 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;

uniform mat4 model;

out vec3 color;

void main()
{
    color = inColor;

    gl_Position = model * vec4(inPosition, 1.0);
}
