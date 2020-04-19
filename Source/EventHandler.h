#pragma once

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
#include "World.h"

#include "math.h"

using namespace glm;
using namespace std;

// initializing OpenGL and binding inputs
class EventHandler {
	GLFWwindow* window;
	World* world;
	// For frame time
	float lastFrameTime = glfwGetTime();
	int lastMouseLeftState = GLFW_RELEASE;
	double lastMousePosX, lastMousePosY;
	

	public:
		EventHandler(World * world, GLFWwindow * window);
		void handleEvents();
		static float GetFrameTime();
		static float sFrameTime;

};