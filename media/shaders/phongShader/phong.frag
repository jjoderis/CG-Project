#version 450 core

uniform vec4 baseColor;
uniform float shininess;

in vec3 iNormal;
in vec3 iPosition;
in vec3 lightPosition;

layout (location = 0) out vec4 fColor;

void main(){
    vec3 lightVector = iPosition - lightPosition;
    vec3 reflected = normalize(reflect(lightVector, iNormal));
    vec3 cameraVector = normalize(-iPosition);
    float phong = dot(reflected, cameraVector);

    if(phong>0.0){
        phong = pow(phong, shininess);
    }else{
        phong = 0.0;
    }

    float lambert = dot(normalize(-iPosition), iNormal);

    fColor = vec4(phong * vec3(1.0, 1.0, 1.0) + lambert * baseColor.xyz, 1.0);
}