
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
    Model(vec3 position, vec3 scaling, vec3 color);
    Model(vec3 position, vec3 rotation, vec3 scaling, vec3 color);
    Model(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture);
    ~Model();
    virtual void draw(Shader* shader, glm::mat4 WorldMatrix);
    virtual void draw(Shader* shader);
    virtual void init();
    vec3 position = vec3(0.0f);
    vec3 scaling = vec3(1.0f);
    vec3 rotation = vec3(0.0f);
    vec3 color = vec3(0.0f);
    GLuint texture = 0;
};