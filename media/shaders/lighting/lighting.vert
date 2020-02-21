#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;

uniform mat4 modelMatrix;
uniform mat4 MVPMatrix;

out vec3 iNormal;
out vec4 iPosition;

void main(void){
    iNormal = (modelMatrix * vNormal).xyz;
    iPosition = modelMatrix * vPosition;

    gl_Position = MVPMatrix * vPosition;
}