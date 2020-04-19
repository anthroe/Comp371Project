#pragma once

#define GLEW_STATIC 1  
#include <GL/glew.h>  

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Camera.h>
#include <SnowManDrawer.h>
#include <AstronautDrawer.h>
#include <GridDrawer.h>
#include <GroundDrawer.h>
#include <RockDrawer.h>



using namespace glm;
using namespace std;

class World {
	public:

        static const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
        // initializing all the variable that will be used for transformations
        float worldRotateXFactor = 0.0f;
        float worldRotateYFactor = 0.0f;
        float zoomFactor = 0.5f;

        unsigned int depthMap;
        unsigned int depthMapFBO;

        vec3 xRotationVector = vec3(1.0f, 0.0f, 0.0f);
        vec3 yRotationVector = vec3(0.0f, 1.0f, 0.0f);

        LineModel* lineModel = new LineModel();
        SnowManDrawer* snowManDrawer = new SnowManDrawer();
		AstronautDrawer* astronautDrawer = new AstronautDrawer();
		GridDrawer* gridDrawer = new GridDrawer();
        GroundDrawer * groundDrawer = new GroundDrawer();
		RockDrawer* rockDrawer = new RockDrawer();
        GLFWwindow* window;
		Camera* camera;
		Shader* shader;
		Shader* textureShader;
        Shader* shadowShader;

		World(GLFWwindow* window);
		void draw();
        void setupLighting();
        void setupShadows();
        void Update(float dt);
        float gravity = 0.03f;
        float friction = 0.0f;
};

