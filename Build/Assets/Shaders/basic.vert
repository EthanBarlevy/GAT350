#version 430 core 

in vec3 vPosition; // 0
in vec3 vColor; // 1

out vec3 color;

void main()
{
	color = vColor;

	gl_Position = vec4(vPosition, 1.0);
}
