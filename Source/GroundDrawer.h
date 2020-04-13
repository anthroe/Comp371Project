#pragma once

#include <Drawer.h>
#include <Model.h>
#include <cmath>
#include <ctime>
#include "PerlinNoise.h"

class GroundDrawer : public Drawer  {
    public:
        const int width = 40, height = 40;
        double** depthArray;
        // All our models
        vector<Model*> models;

        GroundDrawer();
        ~GroundDrawer();
        void draw(Shader* shader);
        void generateGround();
        void generateMountain();
        void createModels();
};