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

    vec4 lightDirection;
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
    vec3 scatteredLight = vec3(0.0);
    vec3 reflectedLight = vec3(0.0);

    for (int i = 0; i < numLights; ++i){
        if (!Light[i].isEnabled) {
            continue;
        }

        vec3 lightPosition = (viewMatrix * Light[i].lightPosition).xyz;
        vec3 lightDirection = lightPosition - iPosition.xyz;
        float attenuation = 1.0;

        if (Light[i].isLocal) {
            float lightDistance = length(lightDirection);
            lightDirection = lightDirection / lightDistance;

            attenuation = 1.0 /
                (Light[i].constantAttenuation
                 + Light[i].linearAttenuation * lightDistance
                 + Light[i].quadraticAttenuation * lightDistance * lightDistance);

            if (Light[i].isSpot) {
                float spotCos = dot(lightDirection, Light[i].coneDirection.xyz);
                if (spotCos < Light[i].spotCosCutoff) {
                    attenuation = 0.0;
                } else {
                    attenuation *= pow(spotCos, Light[i].spotExponent);
                }
            }
        }

        vec3 reflected = normalize(reflect(-lightDirection, iNormal));

        float diffuse = max(0.0, dot(iNormal, lightDirection));
        float specular = max(0.0, dot(iNormal, reflected));

        if (diffuse == 0.0) {
            specular = 0.0;
        } else {
            specular = pow(specular, shininess);
        }

        scatteredLight += Light[i].ambient.rgb * attenuation + Light[i].lightColor.rgb * diffuse * attenuation;
        reflectedLight += Light[i].lightColor.rgb * specular * attenuation;
    }
    
    vec3 rgb = min(baseColor.rgb * scatteredLight + reflectedLight, vec3(1.0));
    fColor = vec4(rgb, baseColor.a);
}