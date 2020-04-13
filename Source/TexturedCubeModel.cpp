
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
#include <TexturedCubeModel.h>

using namespace glm;
TexturedCubeModel::TexturedCubeModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture) :
    Model(position, rotation, scaling, color, texture)
{
    init();
}
TexturedCubeModel::TexturedCubeModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color) :
    Model(position, rotation, scaling, color)
{
    init();
}
TexturedCubeModel::TexturedCubeModel(vec3 position, vec3 scaling, vec3 color) :
    Model(position, scaling, color)
{
    init();
}
TexturedCubeModel::TexturedCubeModel()
{
    init();
}
TexturedCubeModel::~TexturedCubeModel()
{
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}

void TexturedCubeModel::draw(Shader * shader, mat4 groupMatrix)
{
    shader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    shader->setVec3("objectColor", color);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    mat4 worldMatrix = groupMatrix * translate(mat4(1.0f), position);
    worldMatrix = worldMatrix * rotate(mat4(1.0f), glm::radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
    worldMatrix = worldMatrix * rotate(mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 0.0f, 1.0f));
    worldMatrix = worldMatrix * scale(mat4(1.0f),scaling);

    shader->setMat4("worldMatrix", worldMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
void TexturedCubeModel::draw(Shader* shader)
{
    shader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    shader->setVec3("objectColor", color);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    mat4 worldMatrix = translate(mat4(1.0f), position);
    worldMatrix = worldMatrix * rotate(mat4(1.0f), glm::radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
    worldMatrix = worldMatrix * rotate(mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 0.0f, 1.0f));
    worldMatrix = worldMatrix * scale(mat4(1.0f), scaling);

    shader->setMat4("worldMatrix", worldMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
void TexturedCubeModel::init() {
    // Position, Normal, UV
    Vertex texturedCubeVertexArray[] = {
           { vec3(-0.5f, -0.5f, -0.5f), vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},
           { vec3(0.5f, -0.5f, -0.5f), vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},
           { vec3(0.5f,  0.5f, -0.5f), vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},
           { vec3(0.5f,  0.5f, -0.5f), vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},
           { vec3(-0.5f,  0.5f, -0.5f), vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},
           { vec3(-0.5f, -0.5f, -0.5f), vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},

           { vec3(-0.5f, -0.5f,  0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
           { vec3(0.5f, -0.5f,  0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
           { vec3(0.5f,  0.5f,  0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
           { vec3(0.5f,  0.5f,  0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
           { vec3(-0.5f,  0.5f,  0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},
           { vec3(-0.5f, -0.5f,  0.5f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},

           { vec3(-0.5f,  0.5f,  0.5f), vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
           { vec3(-0.5f,  0.5f, -0.5f), vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
           { vec3(-0.5f, -0.5f, -0.5f), vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
           { vec3(-0.5f, -0.5f, -0.5f), vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
           { vec3(-0.5f, -0.5f,  0.5f), vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
           { vec3(-0.5f,  0.5f,  0.5f), vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},

           { vec3(0.5f,  0.5f,  0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
           { vec3(0.5f,  0.5f, -0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
           { vec3(0.5f, -0.5f, -0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
           { vec3(0.5f, -0.5f, -0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
           { vec3(0.5f, -0.5f,  0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
           { vec3(0.5f,  0.5f,  0.5f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},

           { vec3(-0.5f, -0.5f, -0.5f), vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f)},
           { vec3(0.5f, -0.5f, -0.5f), vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 1.0f)},
           { vec3(0.5f, -0.5f,  0.5f), vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)},
           { vec3(0.5f, -0.5f,  0.5f), vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)},
           { vec3(-0.5f, -0.5f,  0.5f), vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 0.0f)},
           { vec3(-0.5f, -0.5f, -0.5f), vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f)},

           { vec3(-0.5f,  0.5f, -0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)},
           { vec3(0.5f,  0.5f, -0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
           { vec3(0.5f,  0.5f,  0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},
           { vec3(0.5f,  0.5f,  0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},
           { vec3(-0.5f,  0.5f,  0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)},
           { vec3(-0.5f,  0.5f, -0.5f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)}
    };
    // Create a vertex array
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texturedCubeVertexArray), texturedCubeVertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(vec3)));
    glEnableVertexAttribArray(2);
}