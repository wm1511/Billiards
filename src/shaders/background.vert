#version 440
layout (location = 0) in vec3 vertex_position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 Position;

void main()
{
    Position = vertex_position;

	mat4 rotView = mat4(mat3(viewMatrix));
	vec4 clipPos = projectionMatrix * rotView * vec4(Position, 1.0);

	gl_Position = clipPos.xyww;
}