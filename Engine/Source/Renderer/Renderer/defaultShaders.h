#pragma once

#include <Aliases.h>

// that define is so the IDE doesn't make weird indentations caused by the raw strings
#define namespace_PetrolEngine     namespace PetrolEngine {
#define namespace_PetrolEngine_end }

namespace_PetrolEngine

static const String defaultVertexShader = R""""(
#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

layout (location = 0) out vec3 _FragPos;
layout (location = 1) out vec3 _Normal;
layout (location = 2) out vec2 _TexCoords;

layout (binding = 0) uniform View{
    mat4 model;
    mat4 projection;
    mat4 view;
} v;

void main() {
    _FragPos = vec3(v.model * vec4(aPos, 1.0));
    _Normal  = mat3(v.model) * aNormal;
    _TexCoords = aTexCoords;
    gl_Position = v.projection * v.view * vec4(_FragPos, 1.0);
}
)"""";

static const String defaultFragmentShader = R""""(
#version 450 core

struct Material {
    sampler2D diffuseMap ;
    sampler2D specularMap;
    float     shininess  ;
};

struct Light {
// None - 0 || dirLight - 1 || pointLight - 2 || spotLight - 3
    vec3  position;  // For spotLight and pointLight
    vec3  direction; // For dirLight and spotLight
    float lightType; // For everyone (treat as int - uniform buffer cannot contain int)

    float cutOff;      // For spotLight
    float outerCutOff; // For spotLight

    float constant;    // For spotLight and pointLight
    float linear;      // For spotLight and pointLight
    float quadratic;   // For spotLight and pointLight

    vec3 ambient;      // For everyone
    vec3 diffuse;      // For everyone
    vec3 specular;     // For everyone
};

layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec3 _FragPos;
layout (location = 1) in vec3 _Normal;
layout (location = 2) in vec2 _TexCoords;

layout (binding = 0) uniform           u_shininess { float shininess; };
layout (binding = 1) uniform sampler2D diffuseMap ;
layout (binding = 2) uniform sampler2D specularMap;

layout (binding = 3) uniform sampler2D texture_diffuse1 ;
layout (binding = 4) uniform sampler2D texture_diffuse2 ;
layout (binding = 5) uniform sampler2D texture_specular1;
layout (binding = 6) uniform sampler2D texture_normal1  ;
layout (binding = 7) uniform sampler2D texture_height1  ;

layout (binding = 8) uniform u_viewPos           { vec3     viewPos;  };
layout (binding = 9) uniform u_light             { Light    light[4]; };

vec3 CalcDirLight   (Light light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight (Light light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight  (Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec4 color = texture(texture_diffuse1, _TexCoords);

    if(color.w < 0.05)
    discard;

    vec3 normal      = normalize(_Normal);
    vec3 viewDir     = normalize(viewPos - _FragPos);

    vec3 lightResult = CalcDirLight(light[0], normal, viewDir);

    FragColor = color;//vec4(1.0f);//color * vec4(lightResult, 1.0f);
}

vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir   = normalize(-light.direction );
    vec3 reflectDir = reflect  (-lightDir, normal);

    float diff =     max(dot(  normal,  lightDir  ), 0.0);
    float spec = pow(max(dot( viewDir, reflectDir ), 0.0), shininess);

    vec3 ambient  = light.ambient  *        1;//vec3(texture(diffuseMap, _TexCoords));
    vec3 diffuse  = light.diffuse  * diff * 1;//vec3(texture(diffuseMap, _TexCoords));
    vec3 specular = light.specular * spec * 1;

    return (ambient + diffuse);
}

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float _distance   = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * _distance + light.quadratic * (_distance * _distance));

    vec3 ambient  = light.ambient  *        vec3(texture(diffuseMap, _TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(diffuseMap, _TexCoords));
    vec3 specular = light.specular * spec;

    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float _distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * _distance + light.quadratic * (_distance * _distance));
    // spotlight intensity

    float theta     = dot  (lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient  = light.ambient  *        vec3(texture(diffuseMap, _TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(diffuseMap, _TexCoords));
    vec3 specular = light.specular * spec;

    return (ambient + diffuse + specular) * attenuation * intensity;
}
)"""";

static const String defaultQuadVertexShaderBatched = R""""(
#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in int  aTexIndex;
layout (location = 2) in vec2 aTexCoords;

layout (location = 0) out vec2 _TexCoords;

)"""";


static const String defaultTextVertexShader = R""""(
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCords;
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(position, 1.0f);
    TexCoords = texCords;
}
)"""";
static const String defaultTextFragmentShader = R""""(
#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;

const float width = 0.4;
const float edge = 0.1;

void main() {
    float distance = 1.0 - texture(text, TexCoords).r;
    float alpha = 1 - smoothstep(width, width + edge, distance);

    //vec4 result = vec4(1,1,1,1);
    //float mask = texture(text, TexCoords).r;
    //mask = smoothstep(0, 1, mask);
    //if( mask >= 0.7 ) { result.a = 1; }
    //else { result.a = 0; }
    color = vec4(1,1,1,1);
    //float mask = texture(text, TexCoords).a;
    //color = vec4(mask,0,0,1);
    //color = vec4(texture(text, TexCoords).r);
}
)"""";
namespace_PetrolEngine_end