#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 2) in vec3 inNormal;
layout (location = 3) in vec2 inUV;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec3 ourColour;
out vec3 normal;
out vec2 UV;
out vec3 fragPos;

void main(){
    gl_Position = Projection * View * Model * vec4(inPos, 1.0);
    ourColour = vec3(1.0f,0.5f,1.0f);
    normal = inNormal;
    UV = inUV;
    fragPos = vec3(Model * vec4(inPos, 1.0));
}