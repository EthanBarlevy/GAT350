#version 430 core

#define POINT       0
#define DIRECTIONAL 1
#define SPOTLIGHT   2


in vec2 coords;
in vec3 position;
in vec3 normal;

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
} light;

uniform struct Material
{
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
} material;

layout (binding = 0) uniform sampler2D diffuse_map; // diffuse
//layout (binding = 1) uniform sampler2D specular_map; // specular
//layout (binding = 2) uniform sampler2D emissive_map; // emissive

void phong(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
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

	// Ambient
	ambient = light.ambient * material.color;

	// Diffuse
	// calculate light intensitly with dot product (normal * direction)
	float intensity = max(dot(light_dir, normal), 0);
	diffuse = light.color * material.color * intensity;

	// Specular
	specular = vec3(0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-light_dir, normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection, view_dir), 0) * spot_intensity;
		intensity = pow(intensity, material.shininess);
		specular = light.color * material.color * intensity;
	}
}

void main()
{
	vec3 ambient, diffuse, specular;
	
	phong(position, normal, ambient, diffuse, specular);
	
	vec2 tcoords = (coords * material.uv_tiling) + material.uv_offset;

	//vec4 tcolor = mix(texture(diffuse_map, tcoords), texture(specular_map, tcoords), 0.8);
	vec4 tcolor = texture(diffuse_map, tcoords);

	fColor = vec4(ambient + diffuse, 1) * tcolor + vec4(specular, 1);
}
