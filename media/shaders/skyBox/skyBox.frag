#version 450 core

in vec3 texCoord;

layout (location = 0) out vec4 color;

uniform samplerCube tex;

void main(void)
{
    color = texture(tex, texCoord);
}