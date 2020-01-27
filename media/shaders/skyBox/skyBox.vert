#version 450 core

layout (location = 0) in vec3 vPosition;

out vec3 texCoord;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

void main(void){
    
    texCoord = vPosition;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(vPosition, 1.0);
}