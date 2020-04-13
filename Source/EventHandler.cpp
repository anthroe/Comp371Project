#include <EventHandler.h>


EventHandler::EventHandler(World * world, GLFWwindow* window) {
	this->world = world;
	this->window = window;
    glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);
}
float  EventHandler::sFrameTime = glfwGetTime() ;
void EventHandler::handleEvents() {
    // Frame time calculation
    float dt = glfwGetTime() - lastFrameTime;
    lastFrameTime += dt;

    SnowManDrawer* snowman = world->snowManDrawer;
    Camera* camera = world->camera;

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



    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) // move camera to the left
    {
        camera->cameraPosition -= camera->cameraSideVector * currentCameraSpeed * dt;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) // move camera to the right
    {
        camera->cameraPosition += camera->cameraSideVector * currentCameraSpeed * dt;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) // move camera up
    {
        camera->cameraPosition -= camera->cameraLookAt * currentCameraSpeed * dt;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) // move camera down
    {
        camera->cameraPosition += camera->cameraLookAt * currentCameraSpeed * dt;
    }
    //TRANSFORMATIONS
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // move olaf to the left
    {
        if (shiftHold && fmod(snowman->rotateFactor, 360.0f) != 270.0f)
        {
            snowman->rotateFactor += 1.0f;
        }
        else
        {
            snowman->translationVector[0] -= 0.1f;
            snowman->snowManAnimation();
        }


    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // move olaf to the right
    {
        if (shiftHold && fmod(snowman->rotateFactor, 360.0f) != 90.0f)
        {
            snowman->rotateFactor += 1.0f;
        }
        else
        {
            snowman->translationVector[0] += 0.1f;
            snowman->snowManAnimation();
        }
    }
    if (!world->flyMode) {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) // move olaf to the right
        {
            snowman->Jump();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // move olaf up
    {
        if (shiftHold && fmod(snowman->rotateFactor, 360.0f) != 0.0f)
        {
            snowman->rotateFactor += 1.0f;
        }
        else
        {
            snowman->translationVector[2] += 0.1f;
            snowman->snowManAnimation();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // move olaf down
    {
        if (shiftHold && fmod(snowman->rotateFactor, 360.0f) != 180.0f)
        {
            snowman->rotateFactor += 1.0f;
        }
        else
        {
            snowman->translationVector[2] -= 0.1f;
            snowman->snowManAnimation();
        }
    }
    if (!shiftHold && glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) // move olaf up
    {
        snowman->rotateFactor += 1.0f;
    }
    if (!shiftHold && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) // move olaf down
    {
        snowman->rotateFactor -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) // reset
    {
        snowman->translationVector *= 0.0f;
        snowman->scaleNumber = snowman->scaleNumber * 0.0f + 1.0f;
        snowman->rotateFactor = snowman->rotateFactor * 0.0f;
        camera->zoomFactor = 0.5f;
        world->worldRotateXFactor = 0.0f;
        world->worldRotateYFactor = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) // Getting bigger
    {
        snowman->scaleNumber -= 0.01f;
        if (snowman->scaleNumber < 0)
        {
            snowman->scaleNumber = snowman->scaleNumber * 0.0f + 1.0f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) // getting smaller
    {
        snowman->scaleNumber += 0.01f;

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
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) // panning
    {
        camera->cameraHorizontalAngle -= dx * camera->cameraAngularSpeed * dt;


    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) // tilting
    {
        camera->cameraVerticalAngle -= dy * camera->cameraAngularSpeed * dt;

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
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) // create olaf with triangles
    {
        world->flyMode = world->flyMode ? false : true;
    }
    if (world->flyMode) {
        world->gravity = 0;
        snowman->mVelocity = vec3(0.0f,0.0f,0.0f);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) // create olaf with triangles
        {
            snowman->translationVector[1] -= 0.1f;
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) // create olaf with triangles
        {
            snowman->translationVector[1] += 0.1f;
        }
    }
    /*
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) // randomly summoning the demon olaf anywhere on the grid
    {
        float x = rand() % 100 - 50.0f;
        float z = rand() % 100 - 50.0f;
        snowman->translationVector[0] = x;
        snowman->translationVector[2] = z;
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