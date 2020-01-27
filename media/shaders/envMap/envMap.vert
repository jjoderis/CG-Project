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

    iNormal = vNormal.xyz;
    iPosition = vPosition.xyz;
    //the normalMatrix is the transpose inverse of the model view matrix
    //we use it to convert the camera into model space
    //we use this to calculate the correct tex coordinate in the fragment shader
    cameraPos = (transpose(normalMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
}