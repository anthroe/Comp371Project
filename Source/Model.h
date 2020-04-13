
#pragma once
#include <Shader.h>
#include <GL/glew.h>

#include <GLFW/glfw3.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

class Model {
public:
    Model();
    Model(vec3 translateVector, vec3 scaleVector, vec3 color);
    Model(vec3 translateVector, vec3 rotateVector, vec3 scaleVector, vec3 color);
    ~Model();
    virtual void Draw(Shader* shader, glm::mat4 WorldMatrix);
    virtual void init();
    vec3 translateVector = vec3(0.0f);
    vec3 scaleVector = vec3(1.0f);
    vec3 rotateVector = vec3(0.0f);
    vec3 color = vec3(0.0f);
};