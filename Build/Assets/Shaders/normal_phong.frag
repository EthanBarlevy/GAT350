#version 430 core

in vec2 coords;
in vec3 position;
//in vec3 normal;
in mat3 tbn;

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
	vec2 uv_tiling;
	vec2 uv_offset;
};

uniform Light light;
uniform Material material;

layout (binding = 0) uniform sampler2D diffuse_map; // diffuse
layout (binding = 1) uniform sampler2D normal_map; // normal

void phong(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	// Ambient
	ambient = light.ambient * material.color;

	// Diffuse
	// calculate light direction (unit vector)
	vec3 light_dir = normalize(vec3(light.position) - position);

	// calculate light intensitly with dot product (normal * direction)
	float intensity = max(dot(light_dir, normal), 0);
	diffuse = light.color * material.color * intensity;

	// Specular
	specular = vec3(0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-light_dir, normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection, view_dir), 0);
		intensity = pow(intensity, material.shininess);
		specular = light.color * material.color * intensity;
	}
}

void main()
{
	vec3 ambient, diffuse, specular;

	vec2 tcoords = (coords * material.uv_tiling) + material.uv_offset;
	
	vec3 normal = texture(normal_map, tcoords).rgb;
	// 0-1 to -1-1
	normal = (normal * 2) - 1;
	normal = normalize(tbn * normal);

	phong(position, normal, ambient, diffuse, specular);

	//color = ambient + diffuse + specular;
	

	//vec4 tcolor = mix(texture(diffuse_map, tcoords), texture(normal_map, tcoords), 0.8);
	vec4 tcolor = texture(diffuse_map, tcoords);

	fColor = vec4(ambient + diffuse, 1) * tcolor + vec4(specular, 1);
}
