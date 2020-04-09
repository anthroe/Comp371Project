#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 worldMatrix;
uniform mat4 globalRotationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 lightSpaceMatrix;

out vec3 Normal;
out vec3 FragPos;
out vec3 Color;
out vec4 FragPosLightSpace;

void main()
{
    mat4 modelMatrix = globalRotationMatrix * worldMatrix;
    FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(modelMatrix))) * aNormal; 
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
    gl_Position =  projectionMatrix * viewMatrix  * vec4(FragPos, 1.0);
};