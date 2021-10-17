#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 uv;
layout (location = 2) in float textureId;
layout (location = 3) in mat4 model;

uniform mat4 vp;
out vec3 pixelUv;

void main()
{
	mat4 mvp = vp * model;
	gl_Position = mvp * vec4(vertex, 1.0);

	pixelUv = vec3(uv, textureId);
}
