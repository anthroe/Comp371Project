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
    setupLighting();
    mat4 worldRotationMatrix = rotate(mat4(1.0f), radians(worldRotateYFactor), yRotationVector) * rotate(mat4(1.0f), radians(worldRotateXFactor), xRotationVector);
    textureShader->use();
    textureShader->setMat4("globalRotationMatrix", worldRotationMatrix);
    shader->use();
    shader->setMat4("globalRotationMatrix", worldRotationMatrix);

    gridDrawer->draw(shader);
    snowManDrawer->draw(shader, textureShader, worldRotationMatrix);
    groundDrawer->draw(textureShader, groundDrawer->depthArray, groundDrawer->width, groundDrawer->height);
    camera->updateLookAt();
}

void World::setupLighting() {
    // Setting up texture shader lighting
    textureShader->use();
    textureShader->setVec3("lightDirection", vec3(-0.2f, -1.0f, -0.3f));
    textureShader->setVec3("viewPos", camera->cameraPosition);
    // Setting up color shader lighting
    shader->use();
    shader->setVec3("lightDirection", vec3(-0.2f, -1.0f, -0.3f));
    shader->setVec3("viewPos", camera->cameraPosition);

}
