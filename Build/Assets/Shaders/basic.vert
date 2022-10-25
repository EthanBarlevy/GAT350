#version 430 core 

in layout(location = 0) vec3 vPosition;
//in layout(location = 1) vec3 vColor;
in layout(location = 1) vec2 vCoords;

out vec2 coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float scale = 1.0f;

void main()
{
	//color = vColor;
	coords = vCoords;
	mat4 mvp = projection * view * model;
	vec4 tposition = mvp * vec4(vPosition * scale, 1.0);
	gl_Position = tposition;
}
