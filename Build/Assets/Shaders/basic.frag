#version 430 core

in vec3 color;

out vec4 fColor;

uniform vec3 tint;

void main()
{
	fColor = vec4(color * tint, 1.0);
}
