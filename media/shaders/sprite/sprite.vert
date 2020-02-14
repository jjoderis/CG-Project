#version 450 core

layout (location = 0) in vec4 position;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

void main(void){

    vec4 pos = projectionMatrix * modelViewMatrix * position;
    gl_PointSize = (1.0 - pos.z / pos.w) * 30.0;
    gl_Position = pos;
}