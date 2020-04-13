//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2019 Concordia University. All rights reserved.
//

#pragma once
#include <Shader.h>

class TexturedCubeModel
{
public:
    TexturedCubeModel();
    ~TexturedCubeModel();
    void Draw(Shader * shader, glm::mat4 WorldMatrix);
    glm::vec3 GetPosition() const { return translationVector; }
    glm::vec3 GetScaling() const { return scaleVector; }

    vec3 translationVector = vec3(1.0f);
    vec3 scaleVector = vec3(1.0f);
    //protected:
      //  virtual bool ParseLine(const std::vector<ci_string> &token);

private:
    // The vertex format could be different for different types of models
    struct Vertex
    {
        vec3 position;
        vec3 normal;
        vec2 uv;
    };

    unsigned int mVAO;
    unsigned int mVBO;
    unsigned int numOfVertices;
};


