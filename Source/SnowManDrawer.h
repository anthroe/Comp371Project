#pragma once
class SnowManDrawer
{
public:
    SnowManDrawer();
    ~SnowManDrawer();
    void setMode(GLenum mode);
    void setGroupMatrix(glm::mat4 groupMatrix);
    void drawGrid(GLuint worldMatrixLocationColor);
    void drawArmsAndLegs(GLuint worldMatrixLocationColor, float footRotationFactor);
    void drawBody(GLuint worldMatrixLocationColor);
    void drawEyesAndMouth(GLuint worldMatrixLocationColor);
    void drawHat(GLuint worldMatrixLocationColor);
    void drawNose(GLuint worldMatrixLocationColor);
    void drawSnow(GLuint worldMatrixLocationColor);
    

    //protected:
      //  virtual bool ParseLine(const std::vector<ci_string> &token);

private:
    // The vertex format could be different for different types of models
    
};