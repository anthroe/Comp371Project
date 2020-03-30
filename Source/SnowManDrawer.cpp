//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2019 Concordia University. All rights reserved.
//
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include "SnowManDrawer.h"
#include "CubeModel.h"
#include "SphereModel.h"
#include "LineModel.h"
#include "TexturedCubeModel.h"

using namespace glm;

GLenum mode = GL_TRIANGLES;
LineModel* lineModel;
mat4 groupMatrix;
SphereModel* sphere;
CubeModel* coloredCube;
TexturedCubeModel* texturedCube1;
vec3 yRotationVector = vec3(0.0f, 1.0f, 0.0f);
vec3 xRotationVector = vec3(1.0f, 0.0f, 0.0f);
float footRotationBase = 180.0f;
SnowManDrawer::SnowManDrawer()
{
    lineModel = new LineModel();
    sphere = new SphereModel();
    coloredCube = new CubeModel();
    texturedCube1 = new TexturedCubeModel();
    texturedCube1->createTexturedCubeVertexBufferObject();
}

 
SnowManDrawer::~SnowManDrawer()
{

}

void SnowManDrawer::setMode(GLenum drawMode)
{
    mode = drawMode;
}
void SnowManDrawer::setGroupMatrix(mat4 snowManGroupMatrix)
{
    groupMatrix = snowManGroupMatrix;
}
void SnowManDrawer::drawGrid(GLuint worldMatrixLocationColor)
{
    //draw the z axis 100 lines
    mat4 groundWorldMatrix;
    for (int i = 1; i <= 100; i++)
    {
            float z = 1.0f * i;
            groundWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, z - 50.0f));
            lineModel->Draw(worldMatrixLocationColor, groundWorldMatrix);
    }

    //draw the x axis100 lines
    for (int i = 1; i <= 100; i++)
    {
            float x = 1.0f * i;
            groundWorldMatrix = translate(mat4(1.0f), vec3(x - 50.0f, 0.0f, 0.0f)) * rotate(mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            lineModel->Draw(worldMatrixLocationColor, groundWorldMatrix);
    }
        
}
void SnowManDrawer::drawArmsAndLegs(GLuint worldMatrixLocationColor, float footRotationFactor)
{
    mat4 leftFoot = translate(mat4(1.0f), vec3(0.0f, 0.5f, 0.0f)) * rotate(mat4(1.0f), glm::radians(footRotationBase + footRotationFactor), xRotationVector);
    mat4 rightFoot = translate(mat4(1.0f), vec3(0.0f, 0.5f, 0.0f)) * rotate(mat4(1.0f), glm::radians(footRotationBase - footRotationFactor), xRotationVector);
    mat4 leftArm = translate(mat4(1.0f), vec3(1.55f, 1.5f, 0.0f)) * rotate(mat4(1.0f), glm::radians(footRotationBase + footRotationFactor), xRotationVector);
    mat4 rightArm = translate(mat4(1.0f), vec3(-1.55f, 1.5f, 0.0f)) * rotate(mat4(1.0f), glm::radians(footRotationBase - footRotationFactor), xRotationVector);

    //red right arm
    mat4 groundWorldMatrix = groupMatrix * rightArm * translate(mat4(1.0f), vec3(0.65f, 0.0f, 0.0f)) * rotate(mat4(1.0f), glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 1.5f, 0.2f));
    coloredCube->Draw(worldMatrixLocationColor, groundWorldMatrix, mode);

    //white left arm
    groundWorldMatrix = groupMatrix * leftArm * translate(mat4(1.0f), vec3(-0.65f, 0.0f, 0.0f)) * rotate(mat4(1.0f), glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 1.5f, 0.2f));
    coloredCube->Draw(worldMatrixLocationColor, groundWorldMatrix, mode);

    //left foot yellow
    groundWorldMatrix = groupMatrix * leftFoot * scale(mat4(1.0f), vec3(0.2f, 0.5f, 0.2f)) * translate(mat4(1.0f), vec3(-1.5f, 0.5f, 0.0f));
    coloredCube->Draw(worldMatrixLocationColor, groundWorldMatrix, mode);

    //right foot
    groundWorldMatrix = groupMatrix * rightFoot * scale(mat4(1.0f), vec3(0.2f, 0.5f, 0.2f)) * translate(mat4(1.0f), vec3(1.5f, 0.5f, 0.0f)); //transforming
    coloredCube->Draw(worldMatrixLocationColor, groundWorldMatrix, mode);

}
void SnowManDrawer::drawBody(GLuint worldMatrixLocationColor) //legs and body and head
{
    mat4 groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.0f, 1.1f, 0.0f)) * scale(mat4(1.0f), vec3(0.75f));
    sphere->Draw(worldMatrixLocationColor, groundWorldMatrix);

    groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.0f, 2.1f, 0.0f)) * scale(mat4(1.0f), vec3(0.60f));
    sphere->Draw(worldMatrixLocationColor, groundWorldMatrix);


}
void SnowManDrawer::drawEyesAndMouth(GLuint worldMatrixLocationColor)
{
    mat4 groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.12f, 2.3f, 0.60f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.1f)); //transforming
    coloredCube->Draw(worldMatrixLocationColor, groundWorldMatrix, mode);

    //left eye
    groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(-0.12f, 2.3f, 0.60f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.1f)); //transforming
    coloredCube->Draw(worldMatrixLocationColor, groundWorldMatrix, mode);


    //mouth
    groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.0f, 1.9f, 0.60f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.1f)); //transforming
    coloredCube->Draw(worldMatrixLocationColor, groundWorldMatrix, mode);

}
void SnowManDrawer::drawHat(GLuint worldMatrixLocationTexture)
{
    //hat
    mat4 groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.0f, 3.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.3f, 0.7f, 0.3f));
    //coloredCube->Draw(worldMatrixLocationColor, groundWorldMatrix, mode);
    texturedCube1->Draw(worldMatrixLocationTexture, groundWorldMatrix);

}
void SnowManDrawer::drawNose(GLuint worldMatrixLocationTexture)
{
    mat4 groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.0f, 2.1f, 0.8f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.5f)); //transforming
    //coloredCube->Draw(worldMatrixLocationColor, groundWorldMatrix, mode);
    texturedCube1->Draw(worldMatrixLocationTexture, groundWorldMatrix);


}
void SnowManDrawer::drawSnow(GLuint worldMatrixLocationTexture)
{
    mat4 pillarWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(100.0f, 0.1f, 100.0f));

    texturedCube1->Draw(worldMatrixLocationTexture, pillarWorldMatrix);

}


