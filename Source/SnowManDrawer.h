#pragma once

#include <Drawer.h>

class SnowManDrawer : public Drawer
{
public:

    float scaleNumber = 1.0f;
    float rotateFactor = 0.0f;

    // Animation
    float footRotationFactor = 0;
    bool footSwitch = true;

    vec3 position = vec3(2.0f, 10.0f, 2.0f);
    vec3 scaling = vec3(1.0f);

    mat4 groupMatrix;

    // All our models
    vector<Model*> models;
    // For animation
    vector<Model*> footAndArmsModels;

    SnowManDrawer();
    ~SnowManDrawer();
    void setGroupMatrix(glm::mat4 groupMatrix);
    void draw(Shader* shader, mat4 worldRotationMatrix);
    void snowManAnimation();
    void Accelerate(glm::vec3 force, float dt);
    void Angulate(glm::vec3 torque);
    virtual void Update(float dt);
    glm::vec3 mRotationAxis;
    float     mRotationAngleInDegrees;
    
    glm::vec3 mVelocity;
    glm::vec3 mAngularAxis;
    float     mAngularVelocityInDegrees;
    void Jump();

    float ContainsPoint(glm::vec3 modelPosition);
    bool CollideXZ(glm::vec3 modelPosition);

    float mMass = 1.0f;

    void createModels();
    double** depthArray;
    void setDepthArray(double** depthArray1) { depthArray = depthArray1; }
};