#version 330 core

in vec3 ourColour;
in vec3 normal;
in vec2 UV;
in vec3 fragPos;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ambientStrength = 0.2f;
float specularStrength = 0.5f;

//white light
vec3 lightColour = vec3(1.0,1.0,1.0);

void main()
{
	vec3 ambient = ambientStrength * lightColour;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColour;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir),0.0),64);
	vec3 specular = specularStrength * spec * lightColour;

	vec3 result = (ambient + diffuse + specular) * ourColour;

	FragColor = vec4(result,1.0);
}