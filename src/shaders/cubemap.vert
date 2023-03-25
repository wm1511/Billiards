#version 440
layout (location = 0) in vec3 vertex_position;

out vec3 WorldPos;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    WorldPos = vertex_position;  
    gl_Position =  projection * view * vec4(WorldPos, 1.0);
}