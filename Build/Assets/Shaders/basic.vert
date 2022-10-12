#version 430 core 

in layout(location = 0) vec3 vPosition;
in layout(location = 1) vec3 vColor;

out vec3 color;

void main()
{
	color = vColor;

	gl_Position = vec4(vPosition, 1.0);
}
