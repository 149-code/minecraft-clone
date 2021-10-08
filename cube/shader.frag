#version 330 core

uniform vec3 blockColor;
out vec3 pixelColor;

void main()
{
	pixelColor = blockColor;
}
