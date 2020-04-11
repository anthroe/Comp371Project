#include <World.h>
#include "TexturedModel.h"

GLuint activeVAO;
int activeVerticesCount;					  

				 
						

World::World(GLFWwindow* window) {
    this->window = window;
    // Setup Camera
	camera = new Camera();
    // Setup Shaders
	shader = new Shader("SHADER", "../Resources/Shaders/VertexShader.glsl", "../Resources/Shaders/FragmentShader.glsl");
	textureShader = new Shader("TEXTURE", "../Resources/Shaders/VertexShaderTexture.glsl", "../Resources/Shaders/FragmentShaderTexture.glsl");
    shadowShader = new Shader("SHADOW", "../Resources/Shaders/VertexShaderShadow.glsl", "../Resources/Shaders/FragmentShaderShadow.glsl");
    glGenTextures(1, &depthMap);
    // Bind the texture so the next glTex calls affect it
    glBindTexture(GL_TEXTURE_2D, depthMap);
    // Create the texture and specify it's attributes, including widthn height, components (only depth is stored, no color information)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_HEIGHT, SHADOW_WIDTH, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
        NULL);
    // Set texture sampler parameters.
    // The two calls below tell the texture sampler inside the shader how to upsample and downsample the texture. Here we choose the nearest filtering option, which means we just use the value of the closest pixel to the chosen image coordinate.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // The two calls below tell the texture sampler inside the shader how it should deal with texture coordinates outside of the [0, 1] range. Here we decide to just tile the image.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Variable storing index to framebuffer used for shadow mapping // fbo: framebuffer object
    // Get the framebuffer
    glGenFramebuffers(1, &depthMapFBO);
    // Bind the framebuffer so the next glFramebuffer calls affect it
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    // Attach the depth map texture to the depth map framebuffer
    //glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, depth_map_texture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE); //disable rendering colors, only write depth values
	// Model loading goes here
	int rockVerticesCount;
	TexturedModel* rock = new TexturedModel();
	GLuint rockVAO = rock->setupModelEBO("../Resources/Assets/Models/rock.obj", rockVerticesCount);
	activeVAO = rockVAO;
	activeVerticesCount = rockVerticesCount;							
					   
										   
																								
					 
										 
    /* Shaders init */
    shader->use();
    shader->setInt("shadowMap", 1);
    textureShader->use();
    textureShader->setInt("textureSampler", 0);
    textureShader->setInt("shadowMap", 1);
   
}

void World::draw() {
	camera->setViewProjectionMatrices(shader);
	camera->setViewProjectionMatrices(textureShader);
    setupLighting();
    mat4 worldRotationMatrix = rotate(mat4(1.0f), radians(worldRotateYFactor), yRotationVector) * rotate(mat4(1.0f), radians(worldRotateXFactor), xRotationVector);
    shadowShader->use();
    shadowShader->setMat4("globalRotationMatrix", worldRotationMatrix);
    textureShader->use();
    textureShader->setMat4("globalRotationMatrix", worldRotationMatrix);
    shader->use();
    shader->setMat4("globalRotationMatrix", worldRotationMatrix);

    setupShadows();
    //gridDrawer->draw(shader);
    snowManDrawer->draw(shader, textureShader, worldRotationMatrix);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    groundDrawer->draw(textureShader, groundDrawer->depthArray, groundDrawer->width, groundDrawer->height);
	// Draw models
	textureShader->use();
	glBindVertexArray(activeVAO);
	glDrawElements(GL_TRIANGLES, activeVerticesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);		   		  
    camera->updateLookAt();


}

void World::setupLighting() {
    float near_plane = 1.0f, far_plane = 180.0f;
    mat4 lightProjection = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, near_plane, far_plane);
    mat4 lightView = lookAt(vec3(30.0f, 100.0f, 40.0f), vec3(0.0f), vec3(0.0, 1.0, 0.0));
    mat4 lightSpaceMatrix = lightProjection * lightView;
    // Setting up shadow shader lighting
    shadowShader->use();
    shadowShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    // Setting up texture shader lighting
    textureShader->use();
    textureShader->setVec3("lightPosition", vec3(30.0f, 100.0f, 40.0f));
    textureShader->setVec3("viewPos", camera->cameraPosition);
    textureShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    // Setting up color shader lighting
    shader->use();
    shader->setVec3("lightPosition", vec3(30.0f, 100.0f, 40.0f));
    shader->setVec3("viewPos", camera->cameraPosition);
    shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
}

void World::setupShadows() {
    shadowShader->use();
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, groundDrawer->grassTextureID);
    groundDrawer->draw(shadowShader, groundDrawer->depthArray, groundDrawer->width, groundDrawer->height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Draw models
	glBindVertexArray(activeVAO);
	glDrawElements(GL_TRIANGLES, activeVerticesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);					  
    // reset viewport
    int WIDTH, HEIGHT;
    glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
    glViewport(0, 0, WIDTH, HEIGHT);
}

void World::Update(float dt)
{

    glm::vec3 gravityVector(0.0f, -gravity, 0.0f);
    snowManDrawer->Accelerate(gravityVector, dt);
    snowManDrawer->Update(dt);

    glm::vec3 groundPoint = glm::vec3(0.0f);
    glm::vec3 groundUp = glm::vec3(0.0f, 1.0f, 0.0f);

    //Collisions with ground
    //complexity: O(n)

    if (snowManDrawer->IntersectsPlane(groundPoint, groundUp))
    {
        
        snowManDrawer->BounceOffGround(); //Reverses y velocity
    }
}