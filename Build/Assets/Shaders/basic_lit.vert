#version 430 core 

in layout(location = 0) vec3 vPosition;
in layout(location = 1) vec2 vCoords;
in layout(location = 2) vec3 vNormal;

out vec2 coords;
out vec3 color;

struct Light
{
	vec3 color;
	vec4 position;
};

struct Material
{
	vec3 color;
	float shininess;
};

uniform Light light;
uniform Material material;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float scale = 1.0f;

void main()
{
	coords = vCoords;
	
	// Diffuse
	// create mvp matrix
	mat4 model_view = view * model;
	// transform normals & positions to view space
	vec3 normal = mat3(model_view) * vNormal;
	vec4 position = model_view * vec4(vPosition, 1);
	// calculate light direction (unit vector)
	vec3 light_dir = normalize(vec3(light.position - position));

	// calculate light intensitly with dot product (normal * direction)
	float intensity = max(dot(light_dir, normal), 0);
	vec3 diffuse = light.color * intensity;

	// Specular
	vec3 specular = vec3(0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-light_dir, normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection, view_dir), 0);
		intensity = pow(intensity, 32.0);
		specular = light.color * intensity;
	}


	color = vec3(0.3) + diffuse + specular;

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vPosition * scale, 1.0);;
}
