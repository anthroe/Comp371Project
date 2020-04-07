#pragma once

#include <Shader.h>

class SnowManDrawer
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

    vec3 translationVector = vec3(0.0f);
    vec3 scaleVector = vec3(1.0f);

    vec3 xRotationVector = vec3(1.0f, 0.0f, 0.0f);
    vec3 yRotationVector = vec3(0.0f, 1.0f, 0.0f);

    GLenum mode = GL_TRIANGLES;

    mat4 groupMatrix;

    
    void SnowManDrawer::drawSnowCube(GLuint worldMatrixLocationTexture);
    void SnowManDrawer::drawTestCube(GLuint worldMatrixLocationColor, glm::mat4 cameraPosition);
    void SnowManDrawer::drawSnowCube(GLuint worldMatrixLocationTexture, double **a, int width, int height);

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

    unsigned int loadTexture(std::string imagePath);

    //protected:
      //  virtual bool ParseLine(const std::vector<ci_string> &token);

private:
    // The vertex format could be different for different types of models
    
};