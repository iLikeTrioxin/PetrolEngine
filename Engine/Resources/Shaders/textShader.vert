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
