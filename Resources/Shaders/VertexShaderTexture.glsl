#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
        
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 globalRotationMatrix;

out vec3 Normal;
out vec3 FragPos;
out vec2 UV;

void main()
{
    mat4 modelMatrix =  globalRotationMatrix * worldMatrix;
    FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
    UV = aUV;
    Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
    gl_Position = projectionMatrix * viewMatrix  *  vec4(FragPos, 1.0);
};