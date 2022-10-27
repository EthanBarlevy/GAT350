#version 430 core

in vec2 coords;
in vec3 position;
in vec3 normal;

out vec4 fColor; // pixel color to draw

struct Light
{
	vec3 ambient;
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
uniform sampler2D textureSampler;

void main()
{
	// Ambient
	vec3 ambient = light.ambient * material.color;

	// Diffuse
	// calculate light direction (unit vector)
	vec3 light_dir = normalize(vec3(light.position) - position);

	// calculate light intensitly with dot product (normal * direction)
	float intensity = max(dot(light_dir, normal), 0);
	vec3 diffuse = light.color * material.color * intensity;

	// Specular
	vec3 specular = vec3(0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-light_dir, normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection, view_dir), 0);
		intensity = pow(intensity, material.shininess);
		specular = light.color * material.color * intensity;
	}

	//color = ambient + diffuse + specular;
	
	fColor = vec4(ambient + diffuse, 1) * texture(textureSampler, coords) + vec4(specular, 1);
}
