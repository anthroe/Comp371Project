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

    vec3 translationVector = vec3(2.0f);
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
    glm::vec3 mPosition = vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 mScaling = vec3(1.0f, 1.0f, 1.0f);
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

    double** depthArray;
    void setDepthArray(double** depthArray1) { depthArray = depthArray1; }
};