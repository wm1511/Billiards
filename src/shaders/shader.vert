#version 440

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texcoord;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	Position = vec4(modelMatrix * vec4(vertex_position, 1.f)).xyz;
	TexCoords = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);
	Normal = mat3(modelMatrix) * vertex_normal;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_position, 1.f);
}