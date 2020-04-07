#version 330 core
in vec3 vertexColor;
in vec2 vertexUV; //COMMENTTEXTURE
uniform sampler2D textureSampler; //COMMENTTEXTURE
uniform vec3 objectColor;

out vec4 FragColor;
void main()
{
    vec4 textureColor = texture( textureSampler, vertexUV ); //COMMENTTEXTURE
    FragColor = textureColor * vec4(objectColor.r, objectColor.g, objectColor.b, 1.0f); //COMMENTTEXTURE
};