#version 450 core

uniform vec4 baseColor;
uniform float shininess;

in vec3 iNormal;
in vec3 iPosition;
in vec3 lightPosition;
in vec2 iUV;
in vec3 iPos;

layout (location = 0) out vec4 fColor;

#define M_PI 3.1415926535897932384626433832795

layout (binding = 0) uniform sampler2D texture1;

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

    float u = ((M_PI+atan(iPos.z, iPos.x))/(2*M_PI));
	float v = 1-((atan(sqrt(pow(iPos.x,2)+pow(-iPos.z,2)),-iPos.y))/M_PI);
	vec2 uv = vec2(u,v);

    float lambert = dot(normalize(lightPosition-iPosition), iNormal);

    fColor = vec4(phong * vec3(1.0, 1.0, 1.0) + lambert * texture(texture1, iUV).xyz, 1.0);
}