#pragma once

#include <Drawer.h>
#include <cmath>
#include <ctime>
#include "PerlinNoise.h"

class GroundDrawer : public Drawer  {
    private:
        unsigned const int width = 40, height = 40;
        double** depthArray;
        TexturedCubeModel* texturedCube;
        GLuint grassTextureID;
    public:
        GroundDrawer();
        ~GroundDrawer();
        void draw(Shader* shader);
        void generateGround();
        void generateMountain();
};