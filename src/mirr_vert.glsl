#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
uniform mat4 model;
uniform mat4 camMatrix;
out vec3 color;
out vec3 Normal;
void main()
{
    gl_Position = camMatrix * model * vec4(aPos, 1.0f);
    color = aColor;
    Normal = aNormal;
}