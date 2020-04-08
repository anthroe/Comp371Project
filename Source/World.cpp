#include <World.h>


World::World() {

    // Setup Camera
	camera = new Camera();
    // Setup Shaders
	shader = new Shader("SHADER", "../Resources/Shaders/VertexShader.glsl", "../Resources/Shaders/FragmentShader.glsl");
	textureShader = new Shader("TEXTURE", "../Resources/Shaders/VertexShaderTexture.glsl", "../Resources/Shaders/FragmentShaderTexture.glsl");
   
    

}
void World::draw() {
	camera->setViewProjectionMatrices(shader);
	camera->setViewProjectionMatrices(textureShader);
    
    mat4 worldRotationMatrix = rotate(mat4(1.0f), glm::radians(worldRotateYFactor), yRotationVector) * rotate(mat4(1.0f), glm::radians(worldRotateXFactor), xRotationVector);
    gridDrawer->draw(shader, worldRotationMatrix);
    snowManDrawer->draw(shader, textureShader, worldRotationMatrix);
    groundDrawer->draw(shader);
    camera->updateLookAt();
}
