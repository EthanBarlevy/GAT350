#version 430 core

in vec2 coords;

out vec4 fColor;

uniform sampler2D textureSampler;

void main()
{
	fColor = texture(textureSampler, coords);
}
