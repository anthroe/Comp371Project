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

CubeModel::CubeModel()
{
    init();
}
CubeModel::CubeModel(vec3 translateVector, vec3 rotateVector, vec3 scaleVector, vec3 color) : 
    Model(translateVector, rotateVector, scaleVector, color)
{
    init();
}
CubeModel::CubeModel(vec3 translateVector, vec3 scaleVector, vec3 color) :
    Model(translateVector, scaleVector, color)
{
    init();
}
CubeModel::~CubeModel()
{
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}


void CubeModel::Draw(Shader * shader, mat4 groupMatrix)
{
    shader->use();

    shader->setVec3("objectColor", color);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    mat4 worldMatrix = groupMatrix * translate(mat4(1.0f), translateVector);
    worldMatrix = worldMatrix * rotate(mat4(1.0f), glm::radians(rotateVector.x), vec3(1.0f, 0.0f, 0.0f));
    worldMatrix = worldMatrix * rotate(mat4(1.0f), glm::radians(rotateVector.y), glm::vec3(0.0f, 1.0f, 0.0f));
    worldMatrix = worldMatrix * rotate(mat4(1.0f), glm::radians(rotateVector.z), glm::vec3(0.0f, 0.0f, 1.0f));
    worldMatrix = worldMatrix * scale(mat4(1.0f), scaleVector);

    shader->setMat4("worldMatrix", worldMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CubeModel::init() {
    Vertex cubeVArray[] = {
            { vec3(-0.5f, -0.5f, -0.5f), vec3(0.0f, 0.0f, -1.0f)},
           { vec3(0.5f, -0.5f, -0.5f), vec3(0.0f, 0.0f, -1.0f)},
           { vec3(0.5f,  0.5f, -0.5f), vec3(0.0f, 0.0f, -1.0f)},
           { vec3(0.5f,  0.5f, -0.5f), vec3(0.0f, 0.0f, -1.0f)},
           { vec3(-0.5f,  0.5f, -0.5f), vec3(0.0f, 0.0f, -1.0f)},
           { vec3(-0.5f, -0.5f, -0.5f), vec3(0.0f, 0.0f, -1.0f)},

           { vec3(-0.5f, -0.5f,  0.5f), vec3(0.0f, 0.0f, 1.0f)},
           { vec3(0.5f, -0.5f,  0.5f), vec3(0.0f, 0.0f, 1.0f)},
           { vec3(0.5f,  0.5f,  0.5f), vec3(0.0f, 0.0f, 1.0f)},
           { vec3(0.5f,  0.5f,  0.5f), vec3(0.0f, 0.0f, 1.0f)},
           { vec3(-0.5f,  0.5f,  0.5f), vec3(0.0f, 0.0f, 1.0f)},
           { vec3(-0.5f, -0.5f,  0.5f), vec3(0.0f, 0.0f, 1.0f)},

           { vec3(-0.5f,  0.5f,  0.5f), vec3(-1.0f, 0.0f, 0.0f)},
           { vec3(-0.5f,  0.5f, -0.5f), vec3(-1.0f, 0.0f, 0.0f)},
           { vec3(-0.5f, -0.5f, -0.5f), vec3(-1.0f, 0.0f, 0.0f)},
           { vec3(-0.5f, -0.5f, -0.5f), vec3(-1.0f, 0.0f, 0.0f)},
           { vec3(-0.5f, -0.5f,  0.5f), vec3(-1.0f, 0.0f, 0.0f)},
           { vec3(-0.5f,  0.5f,  0.5f), vec3(-1.0f, 0.0f, 0.0f)},

           { vec3(0.5f,  0.5f,  0.5f), vec3(1.0f, 0.0f, 0.0f)},
           { vec3(0.5f,  0.5f, -0.5f), vec3(1.0f, 0.0f, 0.0f)},
           { vec3(0.5f, -0.5f, -0.5f), vec3(1.0f, 0.0f, 0.0f)},
           { vec3(0.5f, -0.5f, -0.5f), vec3(1.0f, 0.0f, 0.0f)},
           { vec3(0.5f, -0.5f,  0.5f), vec3(1.0f, 0.0f, 0.0f)},
           { vec3(0.5f,  0.5f,  0.5f), vec3(1.0f, 0.0f, 0.0f)},

           { vec3(-0.5f, -0.5f, -0.5f), vec3(0.0f, -1.0f, 0.0f)},
           { vec3(0.5f, -0.5f, -0.5f), vec3(0.0f, -1.0f, 0.0f)},
           { vec3(0.5f, -0.5f,  0.5f), vec3(0.0f, -1.0f, 0.0f)},
           { vec3(0.5f, -0.5f,  0.5f), vec3(0.0f, -1.0f, 0.0f)},
           { vec3(-0.5f, -0.5f,  0.5f), vec3(0.0f, -1.0f, 0.0f)},
           { vec3(-0.5f, -0.5f, -0.5f), vec3(0.0f, -1.0f, 0.0f)},

           { vec3(-0.5f,  0.5f, -0.5f), vec3(0.0f, 1.0f, 0.0f)},
           { vec3(0.5f,  0.5f, -0.5f), vec3(0.0f, 1.0f, 0.0f)},
           { vec3(0.5f,  0.5f,  0.5f), vec3(0.0f, 1.0f, 0.0f)},
           { vec3(0.5f,  0.5f,  0.5f), vec3(0.0f, 1.0f, 0.0f)},
           { vec3(-0.5f,  0.5f,  0.5f), vec3(0.0f, 1.0f, 0.0f)},
           { vec3(-0.5f,  0.5f, -0.5f), vec3(0.0f, 1.0f, 0.0f)}
    };

    numOfVertices = sizeof(cubeVArray) / sizeof(Vertex);

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVArray), cubeVArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

