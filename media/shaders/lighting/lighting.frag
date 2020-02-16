#version 450 core

layout (location = 0) out vec4 fColor;

uniform vec4 baseColor;
uniform float shininess;

uniform mat4 viewMatrix;

struct LightProperties {
    bool isEnabled;
    bool isLocal;

    bool isSpot;
    vec4 ambient;
    vec4 lightColor;
    vec4 lightPosition;

    vec4 halfVector;
    vec4 coneDirection;
    float spotCosCutoff;
    float spotExponent;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

const int maxLights = 20;
layout (std140) uniform Lights{
    int numLights;
    LightProperties Light[maxLights]; 
};

in vec3 iNormal;
in vec4 iPosition;

void main(void){
    vec4 lightCameraPosition = viewMatrix * Light[0].lightPosition;
    vec3 objectToLight = normalize((lightCameraPosition - iPosition).xyz);

    float diffuse = max(0.0, dot(iNormal, objectToLight));

    vec3 reflected = normalize(reflect(objectToLight, iNormal));
    float specular = max(0.0, dot(normalize(iPosition.xyz), reflected));
    specular = pow(specular, shininess);

    vec3 scatteredLight = vec3(Light[0].ambient) + (Light[0].lightColor * diffuse).xyz;
    vec3 reflectedLight = vec3(Light[0].lightColor) * specular * Light[0].constantAttenuation;

    vec3 rgb = min(baseColor.rgb * scatteredLight + reflectedLight, vec3(1.0));

    fColor = vec4(rgb, baseColor.a);
}