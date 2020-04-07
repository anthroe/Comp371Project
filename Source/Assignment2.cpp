// USED:
// COMP 371 Labs Framework
// Created by Nicolas Bergeron on 20/06/2019.
// 
// MODIFIED BY: WALID ENNACEUR TO CREATE THIS ASSIGNMENT 20/02/2020
// 40060735

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs
#include "World.h"
#include "EventHandler.h"

using namespace glm;
using namespace std;

World * world;
EventHandler* eventHandler;

int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));
    generateGround();
    generateMountain();
    generateMountain();
    generateMountain();

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
    eventHandler = new EventHandler(world, window);

    // Other OpenGL states to set once
    // Enable Backface culling
    //glEnable(GL_CULL_FACE);

    // @TODO 1 - Enable Depth Test
    // ...
    glEnable(GL_DEPTH_TEST);

    // Entering Main Loop
    while (!glfwWindowShouldClose(window))
    {
      
        // Each frame, reset color of each pixel to glClearColor
        // @TODO 1 - Clear Depth Buffer Bit as well
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Drawing world
        world->draw();
        // Handle inputs
        eventHandler->handleEvents();
        // End Frame
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // Shutdown GLFW
    glfwTerminate();

    for (int i = 0; i < 10; ++i) {
        delete[] depthArray[i];
    }
    //Free the array of pointers
    delete[] depthArray;

    return 0;
}
