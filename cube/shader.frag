#version 330 core

in vec3 pixelUv;
out vec4 pixelColor;

uniform sampler3D tex;

void main()
{
	pixelColor = texture(tex, pixelUv);
}
