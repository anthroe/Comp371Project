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
#include "CubeModel.h"

using namespace glm;
vec3 cubeVArray[] = {  // position,                            color
        vec3(-0.5f,-0.5f,-0.5f), //left - red
        vec3(-0.5f,-0.5f, 0.5f),
        vec3(-0.5f, 0.5f, 0.5f),

        vec3(-0.5f,-0.5f,-0.5f),
        vec3(-0.5f, 0.5f, 0.5f),
        vec3(-0.5f, 0.5f,-0.5f),

        vec3(0.5f, 0.5f,-0.5f), // far - blue
        vec3(-0.5f,-0.5f,-0.5f),
        vec3(-0.5f, 0.5f,-0.5f),

        vec3(0.5f, 0.5f,-0.5f),
        vec3(0.5f,-0.5f,-0.5f),
        vec3(-0.5f,-0.5f,-0.5f),

        vec3(0.5f,-0.5f, 0.5f), // bottom - turquoise
        vec3(-0.5f,-0.5f,-0.5f),
        vec3(0.5f,-0.5f,-0.5f),

        vec3(0.5f,-0.5f, 0.5f),
        vec3(-0.5f,-0.5f, 0.5f),
        vec3(-0.5f,-0.5f,-0.5f),

        vec3(-0.5f, 0.5f, 0.5f), // near - green
        vec3(-0.5f,-0.5f, 0.5f),
        vec3(0.5f,-0.5f, 0.5f),

        vec3(0.5f, 0.5f, 0.5f),
        vec3(-0.5f, 0.5f, 0.5f),
        vec3(0.5f,-0.5f, 0.5f),

        vec3(0.5f, 0.5f, 0.5f), // right - purple
        vec3(0.5f,-0.5f,-0.5f),
        vec3(0.5f, 0.5f,-0.5f),

        vec3(0.5f,-0.5f,-0.5f),
        vec3(0.5f, 0.5f, 0.5f),
        vec3(0.5f,-0.5f, 0.5f),

        vec3(0.5f, 0.5f, 0.5f), // top - yellow
        vec3(0.5f, 0.5f,-0.5f),
        vec3(-0.5f, 0.5f,-0.5f),

        vec3(0.5f, 0.5f, 0.5f),
        vec3(-0.5f, 0.5f,-0.5f),
        vec3(-0.5f, 0.5f, 0.5f)
};
CubeModel::CubeModel(vec3 size)
{
    

    numOfVertices = sizeof(cubeVArray) / sizeof(Vertex);

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVArray), cubeVArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 2nd attribute buffer : vertex normal
    
}
unsigned int* CubeModel::createVBOCube()
{

    unsigned int cubeVBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVArray), cubeVArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int returnObjCube[2];
    returnObjCube[0] = cubeVBO;
    returnObjCube[1] = cubeVAO;

    //return vbo and vao
    return returnObjCube;
}
CubeModel::~CubeModel()
{
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}


void CubeModel::Draw(GLuint WorldMatrixLocation, mat4 WorldMatrix)
{
    // Draw the Vertex Buffer
    // Note this draws a Sphere
    // The Model View Projection transforms are computed in the Vertex Shader
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
 
    glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &WorldMatrix[0][0]);
    
    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CubeModel::Draw(GLuint WorldMatrixLocation, mat4 WorldMatrix, GLenum mode)
{
    // Draw the Vertex Buffer
    // Note this draws a Sphere
    // The Model View Projection transforms are computed in the Vertex Shader
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &WorldMatrix[0][0]);

    // Draw the triangles !
    glDrawArrays(mode, 0, 36);
}

