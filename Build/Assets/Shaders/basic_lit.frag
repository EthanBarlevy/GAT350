#version 430 core

in vec2 coords;
in vec3 color;

out vec4 fColor;

uniform sampler2D textureSampler;

void main()
{
	fColor = texture(textureSampler, coords) * vec4(color, 1);
}
