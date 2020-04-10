#pragma once

#include <Drawer.h>

class SnowManDrawer : public Drawer
{
public:
    GLuint silverTextureID;
    GLuint carrotTextureID;
    GLuint snowTextureID;

    float scaleNumber = 1.0f;
    float rotateFactor = 0.0f;

    // Animation
    float footRotationFactor = 0;
    bool footSwitch = true;

    vec3 translationVector = vec3(1.0f);
    vec3 scaleVector = vec3(1.0f);

    vec3 xRotationVector = vec3(1.0f, 0.0f, 0.0f);
    vec3 yRotationVector = vec3(0.0f, 1.0f, 0.0f);

    GLenum mode = GL_TRIANGLES;

    mat4 groupMatrix;

    SphereModel* sphere;
    CubeModel* coloredCube;
    TexturedCubeModel* texturedCube1;
    

    float footRotationBase = 180.0f;

    SnowManDrawer();
    ~SnowManDrawer();
    void setMode(GLenum mode);
    void setGroupMatrix(glm::mat4 groupMatrix);
    void drawArmsAndLegs(Shader * shader, float footRotationFactor);
    void drawBody(Shader * shader);
    void drawEyesAndMouth(Shader * shader);
    void drawHat(Shader * shader);
    void drawNose(Shader * shader);
    void drawSnow(Shader * shader);
    void draw(Shader* shader, Shader * textureShader, mat4 worldRotationMatrix);
    void snowManAnimation();
    float snowRotateAnimation(float rotateFactor, float angleRequired);
    void Accelerate(glm::vec3 force, float dt);
    void Angulate(glm::vec3 torque);
    virtual void Update(float dt);
    glm::vec3 mPosition;
    glm::vec3 mScaling;
    glm::vec3 mRotationAxis;
    float     mRotationAngleInDegrees;

    glm::vec3 mVelocity;
    glm::vec3 mAngularAxis;
    float     mAngularVelocityInDegrees;

    void BounceOffGround();
    bool ContainsPoint(glm::vec3 position);//Whether or not the given point is withing the model. For collisions.
    bool IntersectsPlane(glm::vec3 planePoint, glm::vec3 planeNormal);

    float mMass = 1.0f;

    //protected:
      //  virtual bool ParseLine(const std::vector<ci_string> &token);

private:
    // The vertex format could be different for different types of models
    
};