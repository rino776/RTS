#version 330 core

in vec3 ourColour;
in vec3 normal;
in vec2 UV;

out vec4 FragColor;

void main()
{
	FragColor = vec4(ourColour,1.0);

}