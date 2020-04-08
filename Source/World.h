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
#include <GridDrawer.h>
#include <GroundDrawer.h>




using namespace glm;
using namespace std;

class World {
	public:
      
        // initializing all the variable that will be used for transformations
        float worldRotateXFactor = 0.0f;
        float worldRotateYFactor = 0.0f;
        float zoomFactor = 0.5f;

        
        vec3 xRotationVector = vec3(1.0f, 0.0f, 0.0f);
        vec3 yRotationVector = vec3(0.0f, 1.0f, 0.0f);

        LineModel* lineModel = new LineModel();
        SnowManDrawer* snowManDrawer = new SnowManDrawer();
        GridDrawer* gridDrawer = new GridDrawer();
        GroundDrawer * groundDrawer = new GroundDrawer();
		Camera* camera;
		Shader* shader;
		Shader* textureShader;

		World();
		void draw();
        void setupLighting();
};

