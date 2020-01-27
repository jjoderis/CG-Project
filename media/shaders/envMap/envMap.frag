#version 450 core

in vec3 iPosition;
in vec3 iNormal;

layout (location = 0) out vec4 fColor;

uniform samplerCube tex;

void main(void)
{
    vec3 tc = reflect(-iPosition, iNormal);

    tc = vec3(tc.x, -tc.y, tc.z);

    fColor = vec4(0.3, 0.2, 0.1, 1.0) + vec4(0.97, 0.83, 0.79, 0.0) * texture(tex, tc);
}