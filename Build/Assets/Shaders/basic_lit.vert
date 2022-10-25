#version 430 core 

in layout(location = 0) vec3 vPosition;
in layout(location = 1) vec2 vCoords;
in layout(location = 2) vec3 vNormal;

out vec2 coords;
out vec3 color;

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec4 position;
};

uniform Light light;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float scale = 1.0f;

void main()
{
	coords = vCoords;
	
	// diffuse
	mat4 model_view = view * model;
	vec3 normal = mat3(model_view) * vNormal;
	vec4 position = model_view * vec4(vPosition, 1);
	vec3 light_dir = normalize(vec3(light.position - position));

	float intensity = max(dot(light_dir, normal), 0);
	vec3 diffuse = light.diffuse * intensity;

	color = diffuse + light.ambient;

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vPosition * scale, 1.0);;
}
