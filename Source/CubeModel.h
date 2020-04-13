//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2019 Concordia University. All rights reserved.
//

#pragma once
#include <Model.h>

class CubeModel : public Model
{
public:
    CubeModel();
    CubeModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color);
    CubeModel(vec3 position, vec3 scaling, vec3 color);
    ~CubeModel();
    void draw(Shader * shader, glm::mat4 WorldMatrix);
    void init();

    
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


