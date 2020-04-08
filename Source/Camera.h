#pragma once
#define GLEW_STATIC 1  
#include <GL/glew.h>  

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <algorithm>

using namespace glm;
using namespace std;

class Camera {

    public:
        // Camera parameters for view transform
        vec3 cameraPosition = vec3(0.6f, 10.0f, 10.0f);
        vec3 cameraLookAt = vec3(0.0f, 0.0f, -1.0f);
        vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

        vec3 cameraSideVector = vec3(1.0f);
        // Other camera parameters
        float cameraSpeed = 5.0f;
        float cameraFastSpeed = 2 * cameraSpeed;
        float cameraHorizontalAngle = 90.0f;
        float cameraVerticalAngle = 0.0f;

        float zoomFactor =0.5f;

        const float cameraAngularSpeed = 60.0f;

        void setViewProjectionMatrices(Shader * shader);
        void updateLookAt();
};