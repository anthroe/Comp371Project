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

class CubeModel
{
public:
    CubeModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
    virtual ~CubeModel(void);
    virtual void Draw(Shader * shader, glm::mat4 WorldMatrix);
    virtual void Draw(Shader * shader, glm::mat4 WorldMatrix, GLenum mode);
    
//protected:
  //  virtual bool ParseLine(const std::vector<ci_string> &token);

private:
    // The vertex format could be different for different types of models
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
    };

    unsigned int mVAO;
    unsigned int mVBO;
    unsigned int numOfVertices;
};


