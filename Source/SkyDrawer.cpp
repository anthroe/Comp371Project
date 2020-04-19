#include "SkyDrawer.h"

SkyDrawer::SkyDrawer() {
	createModels();
}

void SkyDrawer::draw(Shader* shader) {
    skyBox->draw(shader);
}
void SkyDrawer::createModels() {
    vector<std::string> faces
    {

        "../Resources/Assets/Textures/Skybox/front.tga",
        "../Resources/Assets/Textures/Skybox/back.tga",
        "../Resources/Assets/Textures/Skybox/up.tga",
        "../Resources/Assets/Textures/Skybox/down.tga",
        "../Resources/Assets/Textures/Skybox/right.tga",
        "../Resources/Assets/Textures/Skybox/left.tga",
    };
    GLuint cubemapTexture = loadCubemap(faces);
    skyBox = new SkyBoxModel(cubemapTexture);
}
