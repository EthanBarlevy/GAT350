#version 430 core 

in layout(location = 0) vec3 vposition;
in layout(location = 2) vec3 vnormal;

out vec3 reflectionDir;
out vec3 refractionDir;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float refraction_index;

void main()
{
	vec3 position = vec3(model * vec4(vposition, 1));
	vec3 normal = normalize(mat3(model) * vnormal);

	vec3 cameraPos = vec3(inverse(view)[3]);
	vec3 viewDir = normalize(position - cameraPos);
	reflectionDir = reflect(viewDir, normal);
	refractionDir = refract(viewDir, normal, 1.0 / refraction_index);

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}
