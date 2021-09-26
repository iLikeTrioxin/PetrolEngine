#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec3 _FragPos;
out vec3 _Normal;
out vec2 _TexCoords;

uniform mat4 model;
uniform mat4 pav;

void main()
{
    _FragPos = vec3(model * vec4(aPos, 1.0));
    _Normal  = mat3(model) * aNormal;  
    _TexCoords = aTexCoords;
    gl_Position = pav * vec4(_FragPos, 1.0);
}
