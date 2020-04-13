#include <EnvironmentDrawer.h>

EnvironmentDrawer::EnvironmentDrawer() {
    createModels();
}
EnvironmentDrawer::~EnvironmentDrawer() {
   
}
void EnvironmentDrawer::draw(Shader * shader) {
    for (int i = 0; i < models.size(); i++) {
        models[i]->draw(shader);
    }
}
void EnvironmentDrawer::createModels() {
#if defined(PLATFORM_OSX)
    GLuint rockTextureID = loadTexture("Textures/grass.jpg");
#else
    GLuint rockTextureID = loadTexture("../Resources/Assets/Textures/grass.jpg");
#endif
    models.push_back(new TexturedModel(vec3(10.0f, 0.0f, 10.0f), vec3(0.0f), vec3(1.0f), vec3(1.0f), rockTextureID));
}