#pragma once
#include <Drawer.h>
class EnvironmentDrawer : public Drawer {
    public:
        int** treeAndRockArray;
        const int width = 40, height = 40;
        EnvironmentDrawer(double** depthArray);
        ~EnvironmentDrawer();
        void draw(Shader* shader);
        void generateForest();
        void generateTrees();
        void generateRocks();
        void createModels(double** depthArray);
        /* Models */
        vector<Model*> models;
};