// USED:
// COMP 371 Labs Framework
// Created by Nicolas Bergeron on 20/06/2019.
// 
// MODIFIED BY: WALID ENNACEUR TO CREATE THIS ASSIGNMENT 20/02/2020
// 40060735

#include <iostream>
#include <list>


#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "SnowManDrawer.h"
#include "SphereModel.h"
#include "TexturedCubeModel.h"
#include "CubeModel.h"
#include "LineModel.h"
#include "Shader.h"
#include "World.h"
#include "Camera.h"
using namespace glm;
using namespace std;

World * world;


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
    
    // Black background
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    world = new World();



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


    
    // Entering Main Loop
    while (!glfwWindowShouldClose(window))
    {
        // Frame time calculation
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        // Each frame, reset color of each pixel to glClearColor
        // @TODO 1 - Clear Depth Buffer Bit as well
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        world->draw();
        
        SnowManDrawer* snowman = world->snowManDrawer;
        Camera* camera = world->camera;
        // Handle inputs
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // This was solution for Lab02 - Moving camera exercise
        // We'll change this to be a first or third person camera
        bool fastCam = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
        bool shiftHold = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
        float currentCameraSpeed = (fastCam) ? camera->cameraFastSpeed : camera->cameraSpeed;


        // @TODO 4 - Calculate mouse motion dx and dy
        //         - Update camera horizontal and vertical angle

        double mousePosX, mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY);

        double dx = mousePosX - lastMousePosX;
        double dy = mousePosY - lastMousePosY;

        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;

        //to do shift see fast cam
        // @TODO 5 = use camera lookat and side vectors to update positions with ASDW
        // adjust code below

        

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) // move camera to the left
        {
            camera->cameraPosition -= camera->cameraSideVector * currentCameraSpeed * dt;
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) // move camera to the right
        {
            camera->cameraPosition += camera->cameraSideVector * currentCameraSpeed * dt;
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) // move camera up
        {
            camera->cameraPosition -= camera->cameraLookAt * currentCameraSpeed * dt;
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) // move camera down
        {
            camera->cameraPosition += camera->cameraLookAt * currentCameraSpeed * dt;
        }
        //TRANSFORMATIONS
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // move olaf to the left
        {
            if (shiftHold && fmod(snowman->rotateFactor, 360.0f) != 270.0f)
            {
                snowman->rotateFactor += 1.0f;
            }
            else
            {
                snowman->translationVector[0] -= 0.1f;
                snowman->snowManAnimation();
            }
                
            
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // move olaf to the right
        {
            if (shiftHold && fmod(snowman->rotateFactor, 360.0f) != 90.0f)
            {
                snowman->rotateFactor += 1.0f;
            }
            else
            {
                snowman->translationVector[0] += 0.1f;
                snowman->snowManAnimation();
            }
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // move olaf up
        {
            if (shiftHold && fmod(snowman->rotateFactor, 360.0f) != 0.0f)
            {
                snowman->rotateFactor += 1.0f;
            }
            else
            {
                snowman->translationVector[2] += 0.1f;
                snowman->snowManAnimation();
            }
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // move olaf down
        {
            if (shiftHold && fmod(snowman->rotateFactor, 360.0f) != 180.0f)
            {
                snowman->rotateFactor += 1.0f;
            }
            else
            {
                snowman->translationVector[2] -= 0.1f;
                snowman->snowManAnimation();
            }
        }
        if (!shiftHold && glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) // move olaf up
        {
            snowman->rotateFactor += 1.0f;
        }
        if (!shiftHold && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) // move olaf down
        {
            snowman->rotateFactor -= 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) // reset
        {
            snowman->translationVector *= 0.0f;
            snowman->scaleNumber = snowman->scaleNumber * 0.0f + 1.0f;
            snowman->rotateFactor = snowman->rotateFactor * 0.0f;
            camera->zoomFactor = 0.5f;
            world->worldRotateXFactor = 0.0f;
            world->worldRotateYFactor = 0.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) // Getting bigger
        {
            snowman->scaleNumber -= 0.01f;
            if (snowman->scaleNumber < 0)
            {
                snowman->scaleNumber = snowman->scaleNumber * 0.0f + 1.0f;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) // getting smaller
        {
            snowman->scaleNumber += 0.01f;

        }
        
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) // zooming in and out, holding m and moving along x axis with mouse
        {
            if (dx > 0)
            {
                if (camera->zoomFactor <= 3.13)
                {
                    camera->zoomFactor += 0.01f;
                }
            }
            else if (dx < 0)
            {
                if (camera->zoomFactor >= 0.15)
                {
                    camera->zoomFactor -= 0.01f;
                }
            }

        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) // panning
        {
            camera->cameraHorizontalAngle -= dx * camera->cameraAngularSpeed * dt;
        

        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) // tilting
        {
            camera->cameraVerticalAngle -= dy * camera->cameraAngularSpeed * dt;

        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) // rotate world positive x
        {
            world->worldRotateXFactor += 0.5f;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) // rotate world negative x
        {
            world->worldRotateXFactor -= 0.5f;

        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) // rotate world positive y
        {
            world->worldRotateYFactor += 0.5f;

        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) // rotate world negative y
        {
            world->worldRotateYFactor -= 0.5f;

        }
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) // create olaf with points
        {
            snowman->mode = GL_POINTS;

        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) // create olaf with lines
        {
            snowman->mode = GL_LINES;

        }
        if (!shiftHold && glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) // create olaf with triangles
        {
            snowman->mode = GL_TRIANGLES;

        }
        
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) // randomly summoning the demon olaf anywhere on the grid
        {
            float x = rand() % 100 - 50.0f;
            float z = rand() % 100 - 50.0f;
            snowman->translationVector[0] = x;
            snowman->translationVector[2] = z;
        }
        
        // TODO 6
        // Set the view matrix for first cameras
        // - In first person, camera lookat is set like below

        /* float radius = 5.0f;
        glm::vec3 position = cameraPosition - radius * cameraLookAt;
        viewMatrix = lookAt(position, position + cameraLookAt, cameraUp); */

        // End Frame
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // Shutdown GLFW
    glfwTerminate();

    return 0;
}
