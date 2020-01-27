#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

out vec3 iNormal;
out vec3 iPosition;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

void main(void)
{
    gl_Position = projectionMatrix * modelViewMatrix * vPosition;

    iNormal = normalize((normalMatrix * vNormal).xyz);
    iPosition = (modelViewMatrix * vPosition).xyz; 
}