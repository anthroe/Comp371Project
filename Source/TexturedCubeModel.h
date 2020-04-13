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
#include <OBJloader.h>
#include <OBJloaderV2.h>

class TexturedCubeModel : public Model
{
public:
    TexturedCubeModel();
    TexturedCubeModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture);
    TexturedCubeModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color);
    TexturedCubeModel(vec3 position, vec3 scaling, vec3 color);
    ~TexturedCubeModel();
    void draw(Shader* shader);
    void draw(Shader * shader, mat4 groupMatrix);
    void init();
    glm::vec3 GetPosition() const { return translationVector; }
    glm::vec3 GetScaling() const { return scaleVector; }
    //protected:
      //  virtual bool ParseLine(const std::vector<ci_string> &token);

private:

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



