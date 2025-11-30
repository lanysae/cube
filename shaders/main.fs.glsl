#version 460 core

in vec3 color;
in vec2 texCoords;

out vec4 fragColor;

void main()
{
    const float multiplier = texCoords.x > 0.05 && texCoords.x < 0.95 && texCoords.y > 0.05 && texCoords.y < 0.95 ? 1.0 : 0.2;

    fragColor = vec4(multiplier * color, 1.0);
}
