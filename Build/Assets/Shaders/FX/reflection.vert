#version 430 core 

in layout(location = 0) vec3 vposition;
in layout(location = 2) vec3 vnormal;

out vec3 reflectionDir;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec3 position = vec3(model * vec4(vposition, 1));
	vec3 normal = normalize(mat3(model) * vnormal);

	vec3 cameraPos = vec3(inverse(view)[3]);
	vec3 viewDir = normalize(position - cameraPos);
	reflectionDir = reflect(viewDir, normal);

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}
