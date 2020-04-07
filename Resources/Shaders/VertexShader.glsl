#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 worldMatrix;
uniform mat4 globalRotationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 vertexColor;
void main()
{
    mat4 modelViewProjection = projectionMatrix * viewMatrix * globalRotationMatrix * worldMatrix;
    gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
};