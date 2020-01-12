#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

out vec3 iNormal;
out vec3 iPosition;

void main(){
    iNormal = normalize((normalMatrix * vNormal).xyz);
    iPosition = (modelViewMatrix * vPosition).xyz;
    gl_Position = projectionMatrix * vec4(iPosition, 1.0);
}