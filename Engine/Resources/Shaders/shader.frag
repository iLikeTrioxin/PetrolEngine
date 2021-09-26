#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    // None - 0 || dirLight - 1 || pointLight - 2 || spotLight - 3
    vec3 position;     // For spotLight and pointLight 
    vec3 direction;    // For dirLight and spotLight
    int  lightType;    // For everyone

    float cutOff;      // For spotLight
    float outerCutOff; // For spotLight
  
    float constant;    // For spotLight and pointLight
    float linear;      // For spotLight and pointLight
    float quadratic;   // For spotLight and pointLight
  
    vec3 ambient;      // For everyone
    vec3 diffuse;      // For everyone
    vec3 specular;     // For everyone
};

out vec4 FragColor;

in vec3 _FragPos;
in vec3 _Normal;
in vec2 _TexCoords;

uniform Material  material;
uniform Light     light[4];
uniform vec3      viewPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;

vec3 CalcDirLight   (Light light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight (Light light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight  (Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec4 color = texture(texture_diffuse1, _TexCoords);
    
    if(color.w < 0.05)
        discard;
	
    vec3 normal      = normalize(_Normal);
    vec3 viewDir     = normalize(viewPos - _FragPos);
	
    vec3 lightResult = CalcDirLight(light[0], normal, viewDir);

    FragColor = color * vec4(lightResult, 1.0f);
}

vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir   = normalize(-light.direction );
    vec3 reflectDir = reflect  (-lightDir, normal);

    float diff =     max(dot(  normal,  lightDir  ), 0.0);
    float spec = pow(max(dot( viewDir, reflectDir ), 0.0), material.shininess);
    
    vec3 ambient  = light.ambient  *        1;//vec3(texture(material.diffuse , _TexCoords));
    vec3 diffuse  = light.diffuse  * diff * 1;//vec3(texture(material.diffuse , _TexCoords));
    vec3 specular = light.specular * spec * 1;//vec3(texture(material.specular, _TexCoords));
    
    return (ambient + diffuse);
}

vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float _distance   = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * _distance + light.quadratic * (_distance * _distance));    
    
    vec3 ambient  = light.ambient  *        vec3(texture(material.diffuse , _TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse , _TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, _TexCoords));
    
    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float _distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * _distance + light.quadratic * (_distance * _distance));    
    // spotlight intensity
    
    float theta     = dot  (lightDir, normalize(-light.direction)); 
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    vec3 ambient  = light.ambient  *        vec3(texture(material.diffuse , _TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse , _TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, _TexCoords));
    
    return (ambient + diffuse + specular) * attenuation * intensity;
}
