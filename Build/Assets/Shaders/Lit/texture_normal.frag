#version 430 core

#define POINT       0
#define DIRECTIONAL 1
#define SPOTLIGHT   2
#define MAX_LIGHTS  5

in vec2 coords;
in vec3 position;
in mat3 tbn;

out vec4 fColor; // pixel color to draw

uniform struct Light
{
	int type;
	vec3 ambient;
	vec3 color;
	vec4 position;
	vec3 direction;
	float cutoff;
	float exponent;
}  lights[MAX_LIGHTS];

uniform struct Material
{
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
} material;

layout (binding = 0) uniform sampler2D diffuse_map; // diffuse
layout (binding = 1) uniform sampler2D normal_map; // normal

uniform int light_count;
uniform vec3 ambient_color;

void phong(Light light, vec3 position, vec3 normal, out vec3 diffuse, out vec3 specular)
{
	// directional vector to light
	vec3 light_dir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(vec3(light.position) - position);

	// if spotlight, compute the intensity
	float spot_intensity = 1;
	if(light.type == SPOTLIGHT)
	{
		// get cosine of light direction
		float cosine = dot(light.direction, -light_dir);
		// get angle
		float angle = acos(cosine);

		// if angle is less than cutoff then set to 0
		spot_intensity = (angle < light.cutoff) ? pow(cosine, light.exponent) : 0;
	}

	// Diffuse
	// calculate light intensitly with dot product (normal * direction)
	float intensity = max(dot(light_dir, normal), 0) * spot_intensity;
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
	// initialize color with ambient color 
	fColor = vec4(ambient_color, 1) * texture(diffuse_map, coords); 
	// calculate phong (diffuse, specular) for each light and add to color 
	for (int i = 0; i < light_count; i++) 
	{ 
		vec3 diffuse; 
		vec3 specular; 

		vec3 normal = texture(normal_map, coords).rgb;
		normal = (normal * 2) - 1;
		normal = normalize(tbn * normal);

		phong(lights[i], position, normal, diffuse, specular); 
		fColor += (vec4(diffuse, 1) * texture(diffuse_map, coords)) + vec4(specular, 1); 
	}
}
