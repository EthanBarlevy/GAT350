#version 430 core 

in layout(location = 0) vec3 vPosition;
in layout(location = 1) vec3 vColor;

out vec3 color;

uniform float scale;
uniform mat4 transform;

void main()
{
	color = vColor;

	vec4 tposition = vec4(vPosition, 1.0) * transform;
	gl_Position = tposition;
}
