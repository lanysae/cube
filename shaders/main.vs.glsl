#version 460 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexCoords;

uniform mat4 projection;
uniform mat4 model;

out vec3 color;
out vec2 texCoords;

void main()
{
    color = inColor;
    texCoords = inTexCoords;

    gl_Position = projection * model * vec4(inPosition, 1.0);
}
