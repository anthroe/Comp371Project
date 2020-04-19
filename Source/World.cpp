#include <World.h>
#include "TexturedModel.h"
#include "glm/gtx/string_cast.hpp"
World::World(GLFWwindow* window) {
    this->window = window;
    // Setup Camera
	camera = new Camera();
    // Setup Shaders
	shader = new Shader("SHADER", "../Resources/Shaders/VertexShader.glsl", "../Resources/Shaders/FragmentShader.glsl");
	textureShader = new Shader("TEXTURE", "../Resources/Shaders/VertexShaderTexture.glsl", "../Resources/Shaders/FragmentShaderTexture.glsl");
    shadowShader = new Shader("SHADOW", "../Resources/Shaders/VertexShaderShadow.glsl", "../Resources/Shaders/FragmentShaderShadow.glsl");
    skyShader = new Shader("SKY", "../Resources/Shaders/VertexShaderSky.glsl", "../Resources/Shaders/FragmentShaderSky.glsl");

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
    /* Shaders init */
    shader->use();
    shader->setInt("shadowMap", 1);
    textureShader->use();
    textureShader->setInt("textureSampler", 0);
    textureShader->setInt("shadowMap", 1);
    skyShader->use();
    skyShader->setInt("skybox", 0);
}

void World::draw() {
	camera->setViewProjectionMatrices(shader);
	camera->setViewProjectionMatrices(textureShader);
    camera->setViewMatrices(skyShader);

    skyDrawer->draw(skyShader);
 
    setupLighting();
    mat4 worldRotationMatrix = rotate(mat4(1.0f), radians(worldRotateYFactor), vec3(0.0f,1.0f,0.0f)) * rotate(mat4(1.0f), radians(worldRotateXFactor), vec3(1.0f,0.0f,0.0f));
    
    shadowShader->use();
    shadowShader->setMat4("globalRotationMatrix", worldRotationMatrix);
    textureShader->use();
    textureShader->setMat4("globalRotationMatrix", worldRotationMatrix);
    shader->use();
    shader->setMat4("globalRotationMatrix", worldRotationMatrix);

    setupShadows();
    //gridDrawer->draw(shader);
    
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    groundDrawer->draw(textureShader);
    // Setting world matrix for the loaded model
    environmentDrawer->draw(textureShader);	
    
    snowManDrawer->draw(shader, worldRotationMatrix);

    camera->updateLookAt();
   
}

void World::setupLighting() {
    float near_plane = 30.0f, far_plane = 240.0f;
    mat4 lightProjection = ortho(-60.0f, 60.0f, -60.0f,60.0f, near_plane, far_plane);
    mat4 lightView = lookAt(vec3(-75.0f, 160.0f, 60.0f), vec3(0.0f), vec3(0.0, 1.0, 0.0));
    mat4 lightSpaceMatrix = lightProjection * lightView;
    // Setting up shadow shader lighting
    shadowShader->use();
    shadowShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    // Setting up texture shader lighting
    textureShader->use();
    textureShader->setVec3("lightPosition", vec3(-75.0f, 160.0f, 60.0f));
    textureShader->setVec3("viewPos", camera->cameraPosition);
    textureShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    // Setting up color shader lighting
    shader->use();
    shader->setVec3("lightPosition", vec3(-75.0f, 160.0f, 60.0f));
    shader->setVec3("viewPos", camera->cameraPosition);
    shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
}

void World::setupShadows() {
    shadowShader->use();
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_FRONT);
    groundDrawer->draw(shadowShader);
    shadowShader->use();
    
    environmentDrawer->draw(shadowShader);
    glCullFace(GL_BACK);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // reset viewport
    int WIDTH, HEIGHT;
    glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
    glViewport(0, 0, WIDTH, HEIGHT);
    
}

void World::Update(float dt)
{
    //first person camera
    if (cameraMode == 0) {
        camera->cameraPosition = snowManDrawer->position + vec3(0.0f, 3.0f, 1.5f);
        snowManDrawer->scaleNumber = 0.0f;
        //lock viewing angle to simulate a fov
        /*
        if (camera->cameraHorizontalAngle > 0.0f) {
            camera->cameraHorizontalAngle = 0.0f;
        }
        if (camera->cameraHorizontalAngle < -180.0f) {
            camera->cameraHorizontalAngle = -180.0f;
        }*/

    }
    //third person camera
    if (cameraMode == 1) {
        camera->cameraPosition = snowManDrawer->position + vec3(0.0f, 4.0f, -4.2f);
        snowManDrawer->rotateFactor = camera->cameraHorizontalAngle + 90.0f;
        snowManDrawer->scaleNumber = 1.0f;
    }
   
    if (flyMode == false) {
        
        vec3 groundPoint = vec3(0.0f);
        // Some out of bound points as default values
        vec3 closestPoint = vec3(-10.0f);
        float smallestDistance = 1000.0f;
        for (int i = 0; i < groundDrawer->models.size(); i++) {
            groundPoint = groundDrawer->models[i]->position;
            float distance = snowManDrawer->ContainsPoint(groundPoint);
            if (distance!=-1 && closestPoint.y < groundPoint.y)  {
                smallestDistance = distance;
                closestPoint = groundPoint;
            }
        }
        // Snowman is on the ground
        
        if (closestPoint != vec3(-10.0f)) {
            snowManDrawer->position.y = closestPoint.y + 0.25;
            snowManDrawer->mVelocity = vec3(0.0f);
        }
        // Snowman is falling
        else {
            vec3 gravityVector(0.0f, -gravity, 0.0f);
            snowManDrawer->Accelerate(gravityVector, dt);
            snowManDrawer->Update(dt);
        }
    }
}