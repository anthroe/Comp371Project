#pragma once
#include <Drawer.h>
#include <TexturedModel.h>

class EnvironmentDrawer : public Drawer {
    public:
        int** treeAndRockArray;
        const int width = 40, height = 40;
        EnvironmentDrawer(double** depthArray);
        ~EnvironmentDrawer();
        void draw(Shader* shader);
        void generateTrees();
        void generateRocks();
        void createModels(double** depthArray);
        /* Models */
        vector<Model*> models;
};