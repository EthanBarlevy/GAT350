#version 430 core

in vec3 reflectionDir;
in vec3 refractionDir;

out vec4 fcolor;

uniform samplerCube cubeMap;
uniform float interpolation;

void main()
{
	vec3 reflec = texture(cubeMap, reflectionDir).rgb;
	vec3 refrac = texture(cubeMap, refractionDir).rgb;

	vec4 color = vec4(mix(reflec, reflec, interpolation), 0);
	fcolor = color;
}
