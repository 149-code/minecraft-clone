#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in mat4 model;

uniform mat4 vp;

void main()
{
	mat4 mvp = vp * model;
	gl_Position = mvp * vec4(vertex, 1.0);
}
