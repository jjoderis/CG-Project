#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;
uniform mat4 viewMatrix;

out vec3 iNormal;
out vec3 iPosition;
out vec3 lightPosition;

void main(){
    iNormal = normalize((normalMatrix * vNormal).xyz);
    iPosition = (modelViewMatrix * vPosition).xyz;
    lightPosition = (viewMatrix * vec4(3.0, 0.0, 0.0, 1.0)).xyz;
    gl_Position = projectionMatrix * vec4(iPosition, 1.0);
}