#version 330 core\n
layout (location = 0) in vec3 aPos;

uniform mat4 worldMatrix;
uniform mat4 globalRotationMatrix;
uniform mat4 viewMatrix = mat4(1.0);  
uniform mat4 projectionMatrix = mat4(1.0);

out vec3 vertexColor;
void main()
{
    mat4 modelViewProjection = projectionMatrix * viewMatrix * globalRotationMatrix * worldMatrix;//global rotation * world
    gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
};