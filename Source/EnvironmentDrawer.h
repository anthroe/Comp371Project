#pragma once
#include <Drawer.h>
#include <TexturedModel.h>

class EnvironmentDrawer : public Drawer {
    public:
        EnvironmentDrawer();
        ~EnvironmentDrawer();
        void draw(Shader* shader);
        void createModels();
        /* Models */
        vector<Model*> models;
};