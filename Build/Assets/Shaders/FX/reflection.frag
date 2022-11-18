#version 430 core

in vec3 reflectionDir;

out vec4 fcolor;

uniform samplerCube cubeMap;

void main()
{
	fcolor = texture(cubeMap, reflectionDir);
}
