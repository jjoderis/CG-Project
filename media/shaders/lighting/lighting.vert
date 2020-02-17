#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 0) in vec4 vNormal;

uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;
uniform mat4 projectionMatrix;

out vec3 iNormal;
out vec4 iPosition;

void main(void){
    iNormal = (normalMatrix * vNormal).xyz;
    iPosition = modelViewMatrix * vPosition;

    gl_Position = projectionMatrix * iPosition;
}