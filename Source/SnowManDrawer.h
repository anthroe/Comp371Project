#pragma once

#include <Shader.h>

class SnowManDrawer
{
public:
    SnowManDrawer();
    ~SnowManDrawer();
    void setMode(GLenum mode);
    void setGroupMatrix(glm::mat4 groupMatrix);
    void drawGrid(Shader * shader);
    void drawArmsAndLegs(Shader * shader, float footRotationFactor);
    void drawBody(Shader * shader);
    void drawEyesAndMouth(Shader * shader);
    void drawHat(Shader * shader);
    void drawNose(Shader * shader);
    void drawSnow(Shader * shader);
    

    //protected:
      //  virtual bool ParseLine(const std::vector<ci_string> &token);

private:
    // The vertex format could be different for different types of models
    
};