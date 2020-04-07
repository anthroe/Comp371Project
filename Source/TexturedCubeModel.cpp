
//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2019 Concordia University. All rights reserved.
//
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include "TexturedCubeModel.h"

using namespace glm;
unsigned int mVAO, mVBO;

struct TexturedColoredVertex //COMMENTTEXTURE
{
    TexturedColoredVertex(vec3 _position, vec3 _color, vec2 _uv)
        : position(_position), color(_color), uv(_uv) {}

    vec3 position;
    vec3 color;
    vec2 uv;
};

// Textured Cube model //COMMENTTEXTURE
const TexturedColoredVertex texturedCubeVertexArray[] = {  // position,                            color
        TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)), //left - red
    TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),

    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)),

    TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)), // far - blue
    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f)),

    TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),
    TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)),
    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),

    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)), // bottom - turquoise
    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),
    TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)),

    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),
    TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f)),
    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),

    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f)), // near - green
    TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),
    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)),

    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f)),
    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)),

    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)), // right - purple
    TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),
    TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)),

    TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),
    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),
    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f)),

    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)), // top - yellow
    TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),

    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f),   vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f),  vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f))
};

TexturedCubeModel::TexturedCubeModel(vec3 size)
{

}
void TexturedCubeModel::createTexturedCubeVertexBufferObject()
{
   
    // Create a vertex array
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texturedCubeVertexArray), texturedCubeVertexArray, GL_STATIC_DRAW); //COMMENTTEXTURE

    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        sizeof(TexturedColoredVertex), // stride - each vertex contain 2 vec3 (position, color) //COMMENTTEXTURE
        (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(TexturedColoredVertex),
        (void*)sizeof(vec3)      // color is offseted a vec3 (comes after position)
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,                            // attribute 2 matches aUV in Vertex Shader
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(TexturedColoredVertex),
        (void*)(2 * sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
    ); //COMMENTTEXTURE
    glEnableVertexAttribArray(2); //COMMENTTEXTURE

    
}

TexturedCubeModel::~TexturedCubeModel()
{
    
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}


void TexturedCubeModel::Draw(Shader * shader, mat4 WorldMatrix)
{
    // Draw the Vertex Buffer
    // Note this draws a Sphere
    // The Model View Projection transforms are computed in the Vertex Shader
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    shader->setMat4("worldMatrix", WorldMatrix);

    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
