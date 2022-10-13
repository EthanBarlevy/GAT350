#version 430 core

in vec3 color;
in vec2 coords;

out vec4 fColor;

uniform vec3 tint;
uniform sampler2D textureSampler;

void main()
{
	//fColor = vec4(color * tint, 1.0);
	fColor = texture(textureSampler, coords);
}
