#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;
layout (location = 2) in vec2 vUV;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;
uniform mat4 viewMatrix;

out vec3 iNormal;
out vec3 iPosition;
out vec2 iUV;
out vec3 lightPosition;
out vec3 iPos;

void main(){
    iNormal = normalize((normalMatrix * vNormal).xyz);
    iPosition = (modelViewMatrix * vPosition).xyz;
    iPos = vPosition.xyz;
    iUV = vUV;
    lightPosition = (viewMatrix * vec4(3.0, 0.0, 0.0, 1.0)).xyz;
    gl_Position = projectionMatrix * vec4(iPosition, 1.0);
}