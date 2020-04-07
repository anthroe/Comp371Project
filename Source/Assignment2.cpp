// USED:
// COMP 371 Labs Framework
// Created by Nicolas Bergeron on 20/06/2019.
// 
// MODIFIED BY: WALID ENNACEUR TO CREATE THIS ASSIGNMENT 20/02/2020
// 40060735

#include <iostream>
#include <list>
#include <algorithm>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "SnowManDrawer.h"
#include "SphereModel.h"
#include "TexturedCubeModel.h"
#include "CubeModel.h"
#include "LineModel.h"
#include "Shader.h"

using namespace glm;
using namespace std;
float footRotationFactor = 0;
bool footSwitch = true;

Shader * shader;
Shader * textureShader;


unsigned int loadTexture(std::string imagePath) {
    unsigned int texture;
    glGenTextures(1, &texture);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << imagePath << std::endl;
        stbi_image_free(data);
    }

    return texture;
}
void snowManAnimation()
{
    if (footSwitch)
    {
        if (footRotationFactor < 45.0f)
            footRotationFactor += 2.0f;
        else
            footSwitch = false;

    }
    else
    {
        if (footRotationFactor > -45.0f)
            footRotationFactor -= 2.0f;
        else
            footSwitch = true;
    }
}
float snowRotateAnimation(float rotateFactor, float angleRequired)
{
    /*
        1 --> A, 2 --> D, 3 --> W, 4 --> S
    */
    if (fmod(rotateFactor, 360.0f) != angleRequired)
        rotateFactor += 1.0f;
    return rotateFactor;
}

int main(int argc, char* argv[])
{
    
    // Initialize GLFW and OpenGL version
    glfwInit();

#if defined(PLATFORM_OSX)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    // On windows, we set OpenGL version to 2.1, to support more hardware
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif

    // Create Window and rendering context using GLFW, resolution is 800x600
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Comp371 - Lab 03", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // @TODO 3 - Disable mouse cursor
    // ...
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Load Textures
    #if defined(PLATFORM_OSX)
        GLuint silverTextureID = loadTexture("Textures/silver.jpg");
        GLuint carrotTextureID = loadTexture("Textures/carrot.jpg");
        GLuint snowTextureID = loadTexture("Textures/snow.jpg");
    #else
        GLuint silverTextureID = loadTexture("../Resources/Assets/Textures/silver.jpg");
        GLuint carrotTextureID = loadTexture("../Resources/Assets/Textures/carrot.jpg");
        GLuint snowTextureID = loadTexture("../Resources/Assets/Textures/snow.jpg");
    #endif
    // Black background
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);


    shader = new Shader("SHADER", "../Resources/Shaders/VertexShader.glsl", "../Resources/Shaders/FragmentShader.glsl");
    textureShader = new Shader("TEXTURE", "../Resources/Shaders/VertexShaderTexture.glsl", "../Resources/Shaders/FragmentShaderTexture.glsl");

    // Camera parameters for view transform
    vec3 cameraPosition(0.6f, 1.0f, 10.0f);
    vec3 cameraLookAt(0.0f, 0.0f, -1.0f);
    vec3 cameraUp(0.0f, 1.0f, 0.0f);

    // Other camera parameters
    float cameraSpeed = 5.0f;
    float cameraFastSpeed = 2 * cameraSpeed;
    float cameraHorizontalAngle = 90.0f;
    float cameraVerticalAngle = 0.0f;

    // For frame time
    float lastFrameTime = glfwGetTime();
    int lastMouseLeftState = GLFW_RELEASE;
    double lastMousePosX, lastMousePosY;
    glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);

    // Other OpenGL states to set once
    // Enable Backface culling
    //glEnable(GL_CULL_FACE);

    // @TODO 1 - Enable Depth Test
    // ...
    glEnable(GL_DEPTH_TEST);


    // initializing all the variable that will be used for transformations
    float worldRotateXFactor = 0.0f;
    float worldRotateYFactor = 0.0f;
    float zoomFactor = 0.5f;

    GLenum mode = GL_TRIANGLES;
   
    float scaleNumber = 1.0f;
    float rotateFactor = 0.0f;
    
    vec3 translationVector = vec3(0.0f);
    vec3 scaleVector = vec3(1.0f);
    vec3 yRotationVector = vec3(0.0f, 1.0f, 0.0f);
    vec3 xRotationVector = vec3(1.0f, 0.0f, 0.0f);

    LineModel* lineModel = new LineModel();
    SnowManDrawer* snowManDrawer = new SnowManDrawer();
    // Entering Main Loop
    while (!glfwWindowShouldClose(window))
    {
        // Frame time calculation
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        // Each frame, reset color of each pixel to glClearColor
        // @TODO 1 - Clear Depth Buffer Bit as well
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 projectionMatrix = glm::mat4(1.0f);
        mat4 viewMatrix = glm::mat4(1.0f);
        // Set projection matrix for shader
        projectionMatrix = glm::perspective(zoomFactor,            // field of view in degrees
            1024.0f / 768.0f,  // aspect ratio
            0.01f, 100.0f);   // near and far (near > 0)
        

        // Set initial view matrix
        viewMatrix = lookAt(cameraPosition,  // eye
            cameraPosition + cameraLookAt,  // center
            cameraUp); // up

        // creating pointers to matrices that compose modelViewProjection (and the rotationMatrix
        shader->use();
        shader->setMat4("viewMatrix", viewMatrix);
        shader->setMat4("projectionMatrix", projectionMatrix);

        textureShader->use();
        textureShader->setMat4("viewMatrix", viewMatrix);
        textureShader->setMat4("projectionMatrix", projectionMatrix);
        
        // Draw ground
        mat4 groundWorldMatrix;

        // create groupMatrix which is used to transform all the parts, using predifined data
        mat4 groupMatrix =  translate(mat4(1.0f), translationVector) * rotate(mat4(1.0f), glm::radians(rotateFactor), yRotationVector) * scale(mat4(1.0f), scaleNumber * vec3(1.0f));
        mat4 worldRotationMatrix = rotate(mat4(1.0f), glm::radians(worldRotateYFactor), yRotationVector) * rotate(mat4(1.0f), glm::radians(worldRotateXFactor), xRotationVector);

        // create world rotation matrix, which is used to rotate the whole world
        snowManDrawer->setGroupMatrix(groupMatrix);
        textureShader->setMat4("globalRotationMatrix", worldRotationMatrix);

        glBindTexture(GL_TEXTURE_2D, snowTextureID);
        textureShader->setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
        mat4 pillarWorldMatrix;
        //snowManDrawer->drawSnow(textureShader);

 

        shader->use();
        shader->setVec3("objectColor", vec3(0.0f, 1.0f, 0.0f));
        textureShader->setMat4("globalRotationMatrix", worldRotationMatrix);


        snowManDrawer->drawGrid(shader);
        //drawing the axis
        //x is blue
        shader->setVec3("objectColor", vec3(0.0f, 0.0f, 1.0f));
        groundWorldMatrix = scale(mat4(1.0f), vec3(0.05f)) * translate(mat4(1.0f), vec3(50.0f, 0.01f, 0.0f));
        lineModel->Draw(shader, groundWorldMatrix);

        //z is red
        shader->setVec3("objectColor", vec3(1.0f, 0.0f, 0.0f));
        groundWorldMatrix = scale(mat4(1.0f), vec3(0.05f)) * translate(mat4(1.0f), vec3(0.0f, 0.01f, 50.0f)) * rotate(mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        lineModel->Draw(shader, groundWorldMatrix);
        
        //y is white
        shader->setVec3("objectColor", vec3(1.0f, 1.0f, 1.0f));
        groundWorldMatrix = scale(mat4(1.0f), vec3(0.05f)) * translate(mat4(1.0f), vec3(0.0f, 50.01f, 0.0f)) * rotate(mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        lineModel->Draw(shader, groundWorldMatrix);

        snowManDrawer->drawBody(shader);
        //building olaf, using relative positioning by applying transformation of the following order T * R * S
        
        shader->setVec3("objectColor", vec3(0.98f, 0.98f, 0.98f));
        snowManDrawer->drawArmsAndLegs(shader, footRotationFactor);

        //right eye
        shader->setVec3("objectColor", vec3(0.0f, 0.0f, 0.0f)); // setting color of cube
        snowManDrawer->drawEyesAndMouth(shader);

        //hat
        textureShader->use();
        glBindTexture(GL_TEXTURE_2D, silverTextureID);
        textureShader->setVec3("objectColor", glm::vec3(0.82f, 0.82f, 0.82f));
        snowManDrawer->drawHat(textureShader);

        //nose
        glBindTexture(GL_TEXTURE_2D, carrotTextureID);
        textureShader->setVec3("objectColor", glm::vec3(0.90f, 0.65f, 0.0f));
        //glUniform3fv(colorLocation, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.0f))); // setting color of cube
        snowManDrawer->drawNose(shader);

        // Handle inputs
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // This was solution for Lab02 - Moving camera exercise
        // We'll change this to be a first or third person camera
        bool fastCam = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
        bool shiftHold = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
        float currentCameraSpeed = (fastCam) ? cameraFastSpeed : cameraSpeed;


        // @TODO 4 - Calculate mouse motion dx and dy
        //         - Update camera horizontal and vertical angle

        double mousePosX, mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY);

        double dx = mousePosX - lastMousePosX;
        double dy = mousePosY - lastMousePosY;

        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;

        // Convert to spherical coordinates
        const float cameraAngularSpeed = 60.0f;
        

        // Clamp vertical angle to [-85, 85] degrees
        cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, cameraVerticalAngle));
        if (cameraHorizontalAngle > 360)
        {
            cameraHorizontalAngle -= 360;
        }
        else if (cameraHorizontalAngle < -360)
        {
            cameraHorizontalAngle += 360;
        }

        float theta = radians(cameraHorizontalAngle);
        float phi = radians(cameraVerticalAngle);

        cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
        vec3 cameraSideVector = glm::cross(cameraLookAt, vec3(0.0f, 1.0f, 0.0f));

        glm::normalize(cameraSideVector);

        //to do shift see fast cam
        // @TODO 5 = use camera lookat and side vectors to update positions with ASDW
        // adjust code below
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) // move camera to the left
        {
            cameraPosition -= cameraSideVector * currentCameraSpeed * dt;
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) // move camera to the right
        {
            cameraPosition += cameraSideVector * currentCameraSpeed * dt;
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) // move camera up
        {
            cameraPosition -= cameraLookAt * currentCameraSpeed * dt;
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) // move camera down
        {
            cameraPosition += cameraLookAt * currentCameraSpeed * dt;
        }
        //TRANSFORMATIONS
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // move olaf to the left
        {
            if (shiftHold && fmod(rotateFactor, 360.0f) != 270.0f)
            {
                rotateFactor += 1.0f;
            }
            else
            {
                translationVector[0] -= 0.1f;
                snowManAnimation();
            }
                
            
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // move olaf to the right
        {
            if (shiftHold && fmod(rotateFactor, 360.0f) != 90.0f)
            {
                rotateFactor += 1.0f;
            }
            else
            {
                translationVector[0] += 0.1f;
                snowManAnimation();
            }
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // move olaf up
        {
            if (shiftHold && fmod(rotateFactor, 360.0f) != 0.0f)
            {
                rotateFactor += 1.0f;
            }
            else
            {
                translationVector[2] += 0.1f;
                snowManAnimation();
            }
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // move olaf down
        {
            if (shiftHold && fmod(rotateFactor, 360.0f) != 180.0f)
            {
                rotateFactor += 1.0f;
            }
            else
            {
                translationVector[2] -= 0.1f;
                snowManAnimation();
            }
        }
        if (!shiftHold && glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) // move olaf up
        {
            rotateFactor += 1.0f;
        }
        if (!shiftHold && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) // move olaf down
        {
            rotateFactor -= 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) // reset
        {
            translationVector *= 0.0f;
            scaleNumber = scaleNumber * 0.0f + 1.0f;
            rotateFactor = rotateFactor * 0.0f;
            zoomFactor = 0.5f;
            worldRotateXFactor = 0.0f;
            worldRotateYFactor = 0.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) // Getting bigger
        {
            scaleNumber -= 0.01f;
            if (scaleNumber < 0)
            {
                scaleNumber = scaleNumber * 0.0f + 1.0f;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) // getting smaller
        {
            scaleNumber += 0.01f;

        }
        
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) // zooming in and out, holding m and moving along x axis with mouse
        {
            if (dx > 0)
            {
                if (zoomFactor <= 3.13)
                {
                    zoomFactor += 0.01f;
                }
            }
            else if (dx < 0)
            {
                if (zoomFactor >= 0.15)
                {
                    zoomFactor -= 0.01f;
                }
            }

        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) // panning
        {
            cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;
        

        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) // tilting
        {
            cameraVerticalAngle -= dy * cameraAngularSpeed * dt;

        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) // rotate world positive x
        {
            worldRotateXFactor += 0.5f;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) // rotate world negative x
        {
            worldRotateXFactor -= 0.5f;

        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) // rotate world positive y
        {
            worldRotateYFactor += 0.5f;

        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) // rotate world negative y
        {
            worldRotateYFactor -= 0.5f;

        }
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) // create olaf with points
        {
            mode = GL_POINTS;

        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) // create olaf with lines
        {
            mode = GL_LINES;

        }
        if (!shiftHold && glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) // create olaf with triangles
        {
            mode = GL_TRIANGLES;

        }
        
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) // randomly summoning the demon olaf anywhere on the grid
        {
            float x = rand() % 100 - 50.0f;
            float z = rand() % 100 - 50.0f;
            translationVector[0] = x;
            translationVector[2] = z;
        }
        

        // TODO 6
        // Set the view matrix for first cameras
        // - In first person, camera lookat is set like below

        float radius = 5.0f;
        glm::vec3 position = cameraPosition - radius * cameraLookAt;
        viewMatrix = lookAt(position, position + cameraLookAt, cameraUp);

        // End Frame
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // Shutdown GLFW
    glfwTerminate();

    return 0;
}
