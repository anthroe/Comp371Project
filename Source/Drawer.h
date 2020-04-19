#pragma once

#include <GL/glew.h> 

#include <GLFW/glfw3.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/common.hpp>
#include "glm/gtx/string_cast.hpp"

#include <iostream>

#include <Shader.h>
#include "CubeModel.h"
#include "SphereModel.h"
#include "LineModel.h"
#include "TexturedCubeModel.h"

#include "OBJloader.h"
#include "OBJloaderV2.h"

class Drawer {
    public:
        Drawer();
        ~Drawer();
        virtual void draw(Shader* shader);
        virtual void createModels();
        unsigned int loadTexture(std::string imagePath);
        unsigned int loadCubemap(vector<std::string> faces);
        GLuint setupModelVBO(std::string path, int& vertexCount);
        GLuint setupModelEBO(std::string path, int& vertexCount);
 };
