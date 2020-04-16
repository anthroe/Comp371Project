#include <EnvironmentDrawer.h>

EnvironmentDrawer::EnvironmentDrawer() {
    createModels();
}
EnvironmentDrawer::~EnvironmentDrawer() {
   
}
void EnvironmentDrawer::draw(Shader * shader) {
    for (int i = 0; i < models.size(); i++) {
		if (models[i]->name == "tree_leaves")
			models[i]->draw(shader, GL_TRIANGLES);
		else if (models[i]->name == "tree_trunk")
			models[i]->draw(shader, GL_TRIANGLE_FAN);
		else if (models[i]->name == "rock")
			models[i]->draw(shader, GL_TRIANGLES);
		else if (models[i]->name == "astronaut")
			models[i]->draw(shader, GL_TRIANGLE_FAN);
    }
}
void EnvironmentDrawer::createModels() {
#if defined(PLATFORM_OSX)
    GLuint rockTextureID = loadTexture("Textures/rock.jpg");
	GLuint treeTextureID = loadTexture("Textures/tree_leaves.jpg");
	GLuint treeTrunkTextureID = loadTexture("Textures/tree_trunk.jpg");
	GLuint astronautTextureID = loadTexture("Textures/astronaut.jpg");
#else
    GLuint rockTextureID = loadTexture("../Resources/Assets/Textures/rock.jpg");
	GLuint treeTextureID = loadTexture("../Resources/Assets/Textures/tree_leaves.jpg");
	GLuint treeTrunkTextureID = loadTexture("../Resources/Assets/Textures/tree_trunk.jpg");
	GLuint astronautTextureID = loadTexture("../Resources/Assets/Textures/astronaut.jpg");
#endif
    models.push_back(new TexturedModel(vec3(10.0f, 0.0f, 10.0f), vec3(0.0f), vec3(1.0f), vec3(1.0f), rockTextureID, "rock"));
	models.push_back(new TexturedModel(vec3(0.0f, 1.0f, 10.0f), vec3(0.0f), vec3(0.5f, 0.1f, 0.5f), vec3(1.0f), treeTrunkTextureID, "tree_trunk"));
	models.push_back(new TexturedModel(vec3(0.0f, 1.0f, 10.0f), vec3(0.0f), vec3(1.5f, 2.0f, 1.5f), vec3(1.0f), treeTextureID, "tree_leaves"));
	models.push_back(new TexturedModel(vec3(5.0f, 0.0f, 10.0f), vec3(0.0f), vec3(1.0f), vec3(1.0f), astronautTextureID, "astronaut"));
}