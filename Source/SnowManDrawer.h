#pragma once
class SnowManDrawer
{
public:
    SnowManDrawer::SnowManDrawer();
    SnowManDrawer::~SnowManDrawer();
    void SnowManDrawer::setMode(GLenum mode);
    void SnowManDrawer::setGroupMatrix(glm::mat4 groupMatrix);
    void SnowManDrawer::drawGrid(GLuint worldMatrixLocationColor);
    void SnowManDrawer::drawArmsAndLegs(GLuint worldMatrixLocationColor, float footRotationFactor);
    void SnowManDrawer::drawBody(GLuint worldMatrixLocationColor);
    void SnowManDrawer::drawEyesAndMouth(GLuint worldMatrixLocationColor);
    void SnowManDrawer::drawHat(GLuint worldMatrixLocationColor);
    void SnowManDrawer::drawNose(GLuint worldMatrixLocationColor);
    void SnowManDrawer::drawSnow(GLuint worldMatrixLocationColor);
    void SnowManDrawer::drawSnowCube(GLuint worldMatrixLocationTexture);
    void SnowManDrawer::drawSnowCube(GLuint worldMatrixLocationTexture, double **a, int width, int height);

    //protected:
      //  virtual bool ParseLine(const std::vector<ci_string> &token);

private:
    // The vertex format could be different for different types of models
    
};