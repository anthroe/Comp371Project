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

    vec3 translationVector = vec3(1.0f);
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
    glm::vec3 mPosition = vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 mScaling = vec3(0.1f, 0.1f, 0.1f);
    glm::vec3 mRotationAxis;
    float     mRotationAngleInDegrees;
    
    glm::vec3 mVelocity;
    glm::vec3 mAngularAxis;
    float     mAngularVelocityInDegrees;
    void Jump();
    void BounceOffGround();
    bool ContainsPoint(glm::vec3 position);//Whether or not the given point is withing the model. For collisions.
    bool IntersectsPlane(glm::vec3 planePoint, glm::vec3 planeNormal);

    glm::vec3 GetScaling() const { return mScaling; }
    glm::vec3 GetPosition() const { return translationVector; }

    float mMass = 1.0f;

    void createModels();
    //protected:
      //  virtual bool ParseLine(const std::vector<ci_string> &token);

private:
    // The vertex format could be different for different types of models
    
};