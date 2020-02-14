#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

out vec3 iNormal;
out vec3 iPosition;
out vec3 cameraPos;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

void main(void)
{
    gl_Position = projectionMatrix * modelViewMatrix * vPosition; 

    iNormal = (normalMatrix * vNormal).xyz;
    iPosition = (modelViewMatrix * vPosition).xyz;
}