#pragma once
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language

#include "LineModel.h"



using namespace glm;
class GridDrawer {
	public:
		LineModel* lineModel;
		GridDrawer();
		void drawGrid(Shader* shader);
		void draw(Shader* shader, mat4 worldRotationMatrix);
};