#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV; //COMMENTTEXTURE
        
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 globalRotationMatrix;
        
out vec3 vertexColor;
out vec2 vertexUV; //COMMENTTEXTURE
        
void main()
{
    vertexColor = aColor;
    mat4 modelViewProjection = projectionMatrix * viewMatrix * globalRotationMatrix * worldMatrix;
    gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexUV = aUV; //COMMENTTEXTURE
};