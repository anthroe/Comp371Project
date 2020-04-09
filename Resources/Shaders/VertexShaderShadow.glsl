#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 worldMatrix;
uniform mat4 globalRotationMatrix;

void main()
{
    gl_Position = lightSpaceMatrix * globalRotationMatrix * worldMatrix *  vec4(aPos, 1.0);
}
