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
#include <GridDrawer.h>
#include <SkyDrawer.h>
#include <GroundDrawer.h>
#include <EnvironmentDrawer.h>
#include <AstronautDrawer.h>

#include <math.h>


using namespace glm;
using namespace std;

class World {
	public:
        vector<string> cameraModes = { "firstPerson","thirdPerson","free" };
        int cameraMode = 0;
        bool flyMode = false;
        static const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
        // initializing all the variable that will be used for transformations
        float worldRotateXFactor = 0.0f;
        float worldRotateYFactor = 0.0f;
        float zoomFactor = 0.5f;

        unsigned int depthMap;
        unsigned int depthMapFBO;
        

        LineModel* lineModel = new LineModel();
		AstronautDrawer* astronautDrawer = new AstronautDrawer();
        GridDrawer* gridDrawer = new GridDrawer();
        GroundDrawer * groundDrawer = new GroundDrawer();
        SkyDrawer* skyDrawer = new SkyDrawer();
        EnvironmentDrawer * environmentDrawer = new EnvironmentDrawer(groundDrawer->depthArray);
        GLFWwindow* window;
		Camera* camera;
		Shader* shader;
		Shader* textureShader;
        Shader* shadowShader;
        Shader* skyShader;

		World(GLFWwindow* window);
		void draw();
        void setupLighting();
        void setupShadows();
        void Update(float dt);
        float gravity = 0.0003f;
        float friction = 0.0f;
};

