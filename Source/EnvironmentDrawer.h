#pragma once
#include <Drawer.h>
class EnvironmentDrawer : public Drawer {
    public:
        int** treeAndRockArray;
        const int width = 40, height = 40;
        
        vec3 treeColor1 = vec3(1.0f);
        vec3 leavesColor1 = vec3(1.0f);
        vec3 treeColor2 = vec3(1.0f);
        vec3 leavesColor2 = vec3(1.0f);
        float treeSpeciesRatio = 0.5f;
        vec3 rockColor1 = vec3(1.0f);
        vec3 rockColor2 = vec3(1.0f);
        float rockTypeRatio = 0.5f;

        EnvironmentDrawer(double** depthArray);
        ~EnvironmentDrawer();
        void draw(Shader* shader);
        void generateForest();
        void generateTrees();
        void generateRocks();
        void createModels(double** depthArray);
        /* Models */
        vector<Model*> models;

        struct Tree {
            vec3 trunkColor;
            vec3 leavesColor;
            vec3 scale;
            float treeHeight;
        } tree1, tree2;
        struct Rock {
            vec3 color;
        } rock1, rock2;
};