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
#include "LineModel.h"

using namespace glm;
vec3 lineArray[] = {
        glm::vec3(50.0f,  0.0f, 0.0f),  // top center position
        glm::vec3(-50.0f, 0.0f, 0.0f)
};
LineModel::LineModel(vec3 size)
{
    

    numOfVertices = sizeof(lineArray) / sizeof(Vertex);

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineArray), lineArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // 2nd attribute buffer : vertex normal
    
}
unsigned int* LineModel::createVBOCube()
{

    unsigned int lineVBO, lineVAO;
    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(1, &lineVBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(lineVAO);

    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineArray), lineArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int returnObjCube[2];
    returnObjCube[0] = lineVBO;
    returnObjCube[1] = lineVAO;

    //return vbo and vao
    return returnObjCube;
}
LineModel::~LineModel()
{
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}


void LineModel::draw(Shader * shader, mat4 WorldMatrix)
{
    // Draw the Vertex Buffer
    // Note this draws a Sphere
    // The Model View Projection transforms are computed in the Vertex Shader
    shader->use();
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
 
    shader->setMat4("worldMatrix", WorldMatrix);
    
    // Draw the triangles !
    glDrawArrays(GL_LINES, 0, 2);
}

