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

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;
using namespace glm;

static inline bool is_not_alnum_space(char c)
{
    return !(isalnum(c));
}

bool isAlphaNumeric(const std::string& str)
{
    return find_if(str.begin(), str.end(), is_not_alnum_space) == str.end();
}

void gen_random(char* s, const int len) {
    static const char alpha[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alpha[rand() % (sizeof(alpha) - 1)];
    }

    s[len] = 0;
}

string generateSeed()
{
    char* s = new char;
    gen_random(s, 8);

    string seedInput; // Data in which user will input info that will be have arithmetic done on it and will be displayed 
    cout << "Enter a seed value, if you want a seed to be generated, enter period:\n";
    cin >> seedInput;
    cout << endl;
    while (seedInput != "." && !isAlphaNumeric(seedInput))
    {

        cout << "Enter a seed value, if you want a seed to be generated, press period:\n";
        cin >> seedInput;
        cout << endl;
    }
    if (seedInput == ".")
    {
        seedInput = s;
        cout << "A seed has been generated for you: " << seedInput << " \n";

    }
    else
    {
        cout << "The seed you have entered is : " << seedInput << " \n";
    }
    return seedInput;
}

World * world;
EventHandler* eventHandler;

int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));
    string seed = generateSeed();
    srand(std::hash<std::string>{}(seed));
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
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    world = new World(window);
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
        float dt = glfwGetTime();

        world->Update(dt);
        world->draw();
        
        // Handle inputs
        eventHandler->handleEvents();
        // End Frame
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // Shutdown GLFW
    glfwTerminate();

    

    return 0;
}


