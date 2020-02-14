#version 450 core

uniform sampler2D sprite_texture;

layout (location = 0) out vec4 color;

void main(void)
{
    color = texture(sprite_texture, gl_PointCoord);
    
    if(color.x > 0.9 && color.y > 0.9 && color.z > 0.9) {
        discard;
    }
}