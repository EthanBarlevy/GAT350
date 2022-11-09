#version 430 core 

in layout(location = 0) vec3 vPosition;
in layout(location = 1) vec2 vCoords;
in layout(location = 2) vec3 vNormal;
in layout(location = 3) vec3 vTangent;

out vec3 position;
//out vec3 normal;
out vec2 coords;
out mat3 tbn;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// create mvp matrix
	mat4 model_view = view * model;
	// pass data through
	vec3 normal = normalize(mat3(model_view) * vNormal);
	vec3 tangent = normalize(mat3(model_view) * vTangent);
	vec3 bitangent = cross(normal, tangent);

	tbn = mat3(tangent, bitangent, normal);

	position = vec3(model_view * vec4(vPosition, 1));
	coords = vCoords;

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vPosition, 1.0);;
}
