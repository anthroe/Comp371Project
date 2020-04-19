#include <EventHandler.h>
#define PI 3.14159265
bool spacePressed = false;
bool fPressed = false;
SnowManDrawer* snowman;
Camera* camera;
vector<Model*> groundModels;
vector<Model*> environmentModels;
EventHandler::EventHandler(World * world, GLFWwindow* window) {
	this->world = world;
	this->window = window;
    glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);
    snowman = world->snowManDrawer;
    camera = world->camera;
    groundModels = world->groundDrawer->models;
    environmentModels = world->environmentDrawer->models;
}
float  EventHandler::sFrameTime = glfwGetTime() ;
void EventHandler::handleEvents() {
    // Frame time calculation
    float dt = glfwGetTime() - lastFrameTime;
    lastFrameTime += dt;

    
   
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // This was solution for Lab02 - Moving camera exercise
    // We'll change this to be a first or third person camera
    bool fastCam = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
    bool shiftHold = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
    float currentCameraSpeed = (fastCam) ? camera->cameraFastSpeed : camera->cameraSpeed;


    // @TODO 4 - Calculate mouse motion dx and dy
    //         - Update camera horizontal and vertical angle

    double mousePosX, mousePosY;
    glfwGetCursorPos(window, &mousePosX, &mousePosY);

    double dx = mousePosX - lastMousePosX;
    double dy = mousePosY - lastMousePosY;

    lastMousePosX = mousePosX;
    lastMousePosY = mousePosY;

    //to do shift see fast cam
    // @TODO 5 = use camera lookat and side vectors to update positions with ASDW
    // adjust code below
    if (world->cameraMode != 1) {
        camera->cameraHorizontalAngle -= dx * camera->cameraAngularSpeed * dt;
       
    }
    else {
        camera->cameraHorizontalAngle = 90.0f+snowman->rotateFactor;
        
    }
    camera->cameraVerticalAngle -= dy * camera->cameraAngularSpeed * dt;
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) //change to first person camera
    {
        world->cameraMode = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_2 ) == GLFW_PRESS) //change to third person camera
    {
        world->cameraMode = 1;
    }
    
    //TRANSFORMATIONS
    if (!world->flyMode) {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressed) // move olaf to the right
        {
            snowman->Jump();
            spacePressed = true;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && spacePressed) // move olaf to the right
        {
            spacePressed = false;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // move olaf to the left
    {
        vec3 newPos = normalize(cross(camera->cameraLookAt, camera->cameraUp));
        snowman->position.x -= newPos.x * currentCameraSpeed;
        snowman->position.z -= newPos.z * currentCameraSpeed;
        bool collision = false;
        for (int i = 0; i < groundModels.size(); i++) {
            if (snowman->CollideXZ(groundModels[i]))
                collision = true;
        }
        for (int i = 0; i < environmentModels.size(); i++) {
            if (snowman->CollideXZ(environmentModels[i]))
                collision = true;
        }
        if (collision) {
            snowman->position.x += newPos.x * currentCameraSpeed;
            snowman->position.z += newPos.z * currentCameraSpeed;
        }
        snowman->snowManAnimation();
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // move olaf to the right
    {
        vec3 newPos = normalize(cross(camera->cameraLookAt, camera->cameraUp));
        snowman->position.x += newPos.x * currentCameraSpeed;
        snowman->position.z += newPos.z * currentCameraSpeed;
      
        bool collision = false;
        for (int i = 0; i < groundModels.size(); i++) {
            if (snowman->CollideXZ(groundModels[i]))
                collision = true;
        }
        for (int i = 0; i < environmentModels.size(); i++) {
            if (snowman->CollideXZ(environmentModels[i]))
                collision = true;
        }
        if (collision) {
            if (world->flyMode) {
                snowman->position.y -= currentCameraSpeed * camera->cameraLookAt.y;
            }
            snowman->position.x -= newPos.x * currentCameraSpeed;
            snowman->position.z -= newPos.z * currentCameraSpeed;
           
        }
        snowman->snowManAnimation();
    }
 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // move olaf up
    {
        if (world->flyMode) {
            snowman->position.y += currentCameraSpeed * camera->cameraLookAt.y;
        }
        snowman->position.x += currentCameraSpeed * camera->cameraLookAt.x;
        snowman->position.z += currentCameraSpeed * camera->cameraLookAt.z;
        if (world->cameraMode != 1) {
            if (camera->cameraLookAt.z > 0) {
                snowman->rotateFactor = atan(camera->cameraLookAt.x / camera->cameraLookAt.z) * 180 / PI + 180.0f;
            }
            else {
                snowman->rotateFactor = atan(camera->cameraLookAt.x / camera->cameraLookAt.z) * 180 / PI ;
            }

        }
        bool collision = false;
        for (int i = 0; i < groundModels.size(); i++) {
            if (snowman->CollideXZ(groundModels[i]))
                collision = true;
        }
        for (int i = 0; i < environmentModels.size(); i++) {
            if (snowman->CollideXZ(environmentModels[i]))
                collision = true;
        }
        if (collision) {
            if (world->flyMode) {
                snowman->position.y -= currentCameraSpeed * camera->cameraLookAt.y;
            }
            snowman->position.x -= currentCameraSpeed * camera->cameraLookAt.x;
            snowman->position.z -= currentCameraSpeed * camera->cameraLookAt.z;

        }
        snowman->snowManAnimation();
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // move olaf down
    {
        if (world->flyMode) {
            snowman->position.y -= currentCameraSpeed * camera->cameraLookAt.y;
        }
        snowman->position.x -= currentCameraSpeed * camera->cameraLookAt.x;
        snowman->position.z -= currentCameraSpeed * camera->cameraLookAt.z;
        if (world->cameraMode != 1) {
            if (camera->cameraLookAt.z > 0) {
                snowman->rotateFactor = atan(camera->cameraLookAt.x / camera->cameraLookAt.z) * 180 / PI + 180.0f;
            }
            else {
                snowman->rotateFactor = atan(camera->cameraLookAt.x / camera->cameraLookAt.z) * 180 / PI ;
            }

        }
        bool collision = false;
        for (int i = 0; i < groundModels.size(); i++) {
            if (snowman->CollideXZ(groundModels[i]))
                collision = true;
        }
        for (int i = 0; i < environmentModels.size(); i++) {
            if (snowman->CollideXZ(environmentModels[i]))
                collision = true;
        }
        if (collision) {
            if (world->flyMode) {
                snowman->position.y += currentCameraSpeed * camera->cameraLookAt.y;
            }
            snowman->position.x += currentCameraSpeed * camera->cameraLookAt.x;
            snowman->position.z += currentCameraSpeed * camera->cameraLookAt.z;
        }
        snowman->snowManAnimation();
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) // move olaf up
    {
        snowman->rotateFactor += 5.0f * currentCameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) // move olaf down
    {
        snowman->rotateFactor -= 5.0f * currentCameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) // reset
    {
        snowman->position *= 0.0f;
        snowman->scaleNumber = snowman->scaleNumber * 0.0f + 1.0f;
        snowman->rotateFactor = snowman->rotateFactor * 0.0f;
        camera->zoomFactor = 0.5f;
        world->worldRotateXFactor = 0.0f;
        world->worldRotateYFactor = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) // zooming in and out, holding m and moving along x axis with mouse
    {
        if (dx > 0)
        {
            if (camera->zoomFactor <= 3.13)
            {
                camera->zoomFactor += 0.01f;
            }
        }
        else if (dx < 0)
        {
            if (camera->zoomFactor >= 0.15)
            {
                camera->zoomFactor -= 0.01f;
            }
        }

    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) // rotate world positive x
    {
        world->worldRotateXFactor += 0.5f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) // rotate world negative x
    {
        world->worldRotateXFactor -= 0.5f;

    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) // rotate world positive y
    {
        world->worldRotateYFactor += 0.5f;

    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) // rotate world negative y
    {
        world->worldRotateYFactor -= 0.5f;

    }
    /*
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) // create olaf with points
    {
        snowman->mode = GL_POINTS;

    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) // create olaf with lines
    {
        snowman->mode = GL_LINES;

    }
    if (!shiftHold && glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) // create olaf with triangles
    {
        snowman->mode = GL_TRIANGLES;
    }
    */
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !fPressed)
    {
        world->flyMode = world->flyMode ? false : true;
        snowman->mVelocity = vec3(0.0f);
        fPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE && fPressed)
    {
        fPressed = false;
        snowman->mVelocity = vec3(0.0f);
    }
    /*
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) // randomly summoning the demon olaf anywhere on the grid
    {
        float x = rand() % 100 - 50.0f;
        float z = rand() % 100 - 50.0f;
        snowman->position.x = x;
        snowman->position.z = z;
    }
    */
    // TODO 6
    // Set the view matrix for first cameras
    // - In first person, camera lookat is set like below

    /* float radius = 5.0f;
    glm::vec3 position = cameraPosition - radius * cameraLookAt;
    viewMatrix = lookAt(position, position + cameraLookAt, cameraUp); */

}
float EventHandler::GetFrameTime()
{
    return sFrameTime;
}