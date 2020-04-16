#pragma once

#include <Drawer.h>
#include <cmath>
#include <ctime>
#include "PerlinNoise.h"

class GroundDrawer : public Drawer  {
    public:
        unsigned const int width = 40, height = 40;
        double** depthArray;
        int** treeAndRockArray;
        TexturedCubeModel* texturedCube;
        CubeModel* regularCube;
        GLuint grassTextureID;
        GroundDrawer();
        ~GroundDrawer();
        void draw(Shader* shader, double** a, int width, int height);
        void generateGround();
        void generateMountain();
        void generateTrees();
        void generateRocks();
};