#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec3 ourColor;

void main(){
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
    ourColor = vec3(1.0f,0.5f,1.0f);
   
}