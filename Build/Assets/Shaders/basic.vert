#version 430 core 

in layout(location = 0) vec3 vPosition;
in layout(location = 1) vec3 vColor;
in layout(location = 2) vec2 vCoords;

out vec3 color;
out vec2 coords;

uniform float scale;
uniform mat4 mvp;

void main()
{
	color = vColor;
	coords = vCoords;

	vec4 tposition = mvp * vec4(vPosition * scale, 1.0);
	gl_Position = tposition;
}
