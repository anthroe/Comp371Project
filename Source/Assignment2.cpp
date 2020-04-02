// USED:
// COMP 371 Labs Framework
// Created by Nicolas Bergeron on 20/06/2019.
// 
// MODIFIED BY: WALID ENNACEUR TO CREATE THIS ASSIGNMENT 20/02/2020
// 40060735

#include <iostream>
#include <list>
#include <algorithm>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <FreeImageIO.h>
#include <ctime>

#include "SnowManDrawer.h"
#include "SphereModel.h"
#include "TexturedCubeModel.h"
#include "CubeModel.h"
#include "LineModel.h"
#include "PerlinNoise.h"

unsigned const int width = 40, height = 40;
double** depthArray; 

using namespace glm;
using namespace std;
float footRotationFactor = 0;
bool footSwitch = true;

const char* getVertexShaderSource()
{
    // Shader code, sets the modelViewProjection matrix which is the 2D representation of the 3D world [represented with 4D matrixes]
    // globalRotationMatrix is in charge of rotating the world before converting to 2D
    return
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;"
        ""
        "uniform mat4 worldMatrix;"
        "uniform mat4 globalRotationMatrix;"
        "uniform mat4 viewMatrix = mat4(1.0);"  
        "uniform mat4 projectionMatrix = mat4(1.0);"
        ""
        "out vec3 vertexColor;"
        "void main()"
        "{"
        "   mat4 modelViewProjection = projectionMatrix * viewMatrix * globalRotationMatrix * worldMatrix;"//global rotation * world
        "   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
        "}";
}


const char* getFragmentShaderSource()
{
    // code that sets colors to access variable use pointers
    return
        "#version 330 core\n"
        "uniform vec3 objectColor;"
        "out vec4 FragColor;"
        "void main()"
        "{"
        "   FragColor = vec4(objectColor.r, objectColor.g, objectColor.b, 1.0f);"
        "}";
}
const char* getTexturedVertexShaderSource()
{
    // For now, you use a string for your shader code, in the assignment, shaders will be stored in .glsl files
    return
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;"
        "layout (location = 1) in vec3 aColor;"
        "layout (location = 2) in vec2 aUV;" //COMMENTTEXTURE
        ""
        "uniform mat4 worldMatrix;"
        "uniform mat4 viewMatrix = mat4(1.0);"  // default value for view matrix (identity)
        "uniform mat4 projectionMatrix = mat4(1.0);"
        "uniform mat4 globalRotationMatrix;"
        ""
        "out vec3 vertexColor;"
        "out vec2 vertexUV;" //COMMENTTEXTURE
        ""
        "void main()"
        "{"
        "   vertexColor = aColor;"
        "   mat4 modelViewProjection = projectionMatrix * viewMatrix * globalRotationMatrix * worldMatrix;"
        "   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
        "   vertexUV = aUV;" //COMMENTTEXTURE
        "}";
}

const char* getTexturedFragmentShaderSource()
{
    return
        "#version 330 core\n"
        "in vec3 vertexColor;"
        "in vec2 vertexUV;" //COMMENTTEXTURE
        "uniform sampler2D textureSampler;" //COMMENTTEXTURE
        "uniform vec3 objectColor;"
        ""
        "out vec4 FragColor;"
        "void main()"
        "{"
        "   vec4 textureColor = texture( textureSampler, vertexUV );" //COMMENTTEXTURE
        "   FragColor = textureColor * vec4(objectColor.r, objectColor.g, objectColor.b, 1.0f);" //COMMENTTEXTURE
        "}";
}
int compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    // compile and link shader program
    // return shader program id
    // ------------------------------------

    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int loadTexture(char* imagepath)
{
    // Load image using the Free Image library
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imagepath, 0);
    FIBITMAP* image = FreeImage_Load(format, imagepath);
    FIBITMAP* image32bits = FreeImage_ConvertTo32Bits(image);

    // Get an available texture index from OpenGL
    GLuint texture = 0;
    glGenTextures(1, &texture);
    assert(texture != 0);

    // Set OpenGL filtering properties (bi-linear interpolation)
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Retrieve width and hight
    int width = FreeImage_GetWidth(image32bits);
    int height = FreeImage_GetHeight(image32bits);

    // This will upload the texture to the GPU memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
        0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32bits));

    // Free images
    FreeImage_Unload(image);
    FreeImage_Unload(image32bits);

    return texture;
}
void snowManAnimation()
{
    if (footSwitch)
    {
        if (footRotationFactor < 45.0f)
            footRotationFactor += 2.0f;
        else
            footSwitch = false;

    }
    else
    {
        if (footRotationFactor > -45.0f)
            footRotationFactor -= 2.0f;
        else
            footSwitch = true;
    }
}
float snowRotateAnimation(float rotateFactor, float angleRequired)
{
    /*
        1 --> A, 2 --> D, 3 --> W, 4 --> S
    */
    if (fmod(rotateFactor, 360.0f) != angleRequired)
        rotateFactor += 1.0f;
    return rotateFactor;
}


void generateGround() {
    // Define the size of the image

    // Create a PerlinNoise object with the reference permutation vector
    PerlinNoise pn;
    depthArray = new double *[height];
    // Visit every pixel of the image and assign a color generated with Perlin noise
    for (unsigned int i = 0; i < height; ++i) {     // y
        depthArray[i] = new double [width];
        for (unsigned int j = 0; j < width; ++j) {  // x
            double x = (double)j / ((double)width);
            double y = (double)i / ((double)height);

            // Typical Perlin noise
            double n = pn.noise(10 * x, 10 * y, 0.8);

            // Wood like structure
            n = 20 * pn.noise(x, y, 0.8);
            n = n - floor(n);
            //std::cout << n << std::endl;

            depthArray[i][j] = n * 2;

        }
    }


}


void generateMountain()
{
    
    int xCord = rand() % width;
    int zCord = rand() % height;

    //int xCord = 24;
    //int zCord = 20;

    std::cout << xCord << ", " << zCord << endl;

    

    for (int z = zCord - 2; z <= zCord + 2 && zCord - 2 > 0 && zCord + 2 < height; z++)
    {
        for (int x = xCord - 2; x <= xCord + 2 && xCord - 2 > 0 && xCord + 2 < width; x++)
        {
            int additional = rand() % 2;
            depthArray[z][x] = depthArray[zCord][xCord] + 2 + additional;
        }
    }
    for (int z = zCord - 1; z <= zCord + 1 && zCord - 1 > 0 && zCord + 1 < height; z++)
    {
        for (int x = xCord - 1; x <= xCord + 1 && xCord - 1 > 0 && xCord + 1 < width; x++)
        {
            int additional = rand() % 2;
            depthArray[z][x] = depthArray[zCord][xCord] + 2 + additional;
        }
    }
    int additional = rand() % 2;
    depthArray[zCord][xCord] = depthArray[zCord][xCord] + 2 + additional;
}


int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));
    generateGround();
    generateMountain();
    generateMountain();
    generateMountain();

    // Initialize GLFW and OpenGL version
    glfwInit();

#if defined(PLATFORM_OSX)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    // On windows, we set OpenGL version to 2.1, to support more hardware
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif

    // Create Window and rendering context using GLFW, resolution is 800x600
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Comp371 - Lab 03", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // @TODO 3 - Disable mouse cursor
    // ...
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Load Textures
    #if defined(PLATFORM_OSX)
        GLuint silverTextureID = loadTexture("Textures/silver.jpg");
        GLuint carrotTextureID = loadTexture("Textures/carrot.jpg");
        GLuint snowTextureID = loadTexture("Textures/snow.jpg");
        GLuint grassTextureID = loadTexture("Textures/grass.jpg");
    #else
        GLuint silverTextureID = loadTexture("../Assets/Textures/silver.jpg");
        GLuint carrotTextureID = loadTexture("../Assets/Textures/carrot.jpg");
        GLuint snowTextureID = loadTexture("../Assets/Textures/snow.jpg");
        GLuint grassTextureID = loadTexture("../Assets/Textures/grass.jpg");
    #endif
    // Black background
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    // Compile and link shaders here ...
    int shaderProgram = compileAndLinkShaders(getVertexShaderSource(), getFragmentShaderSource());
    int texturedShaderProgram = compileAndLinkShaders(getTexturedVertexShaderSource(), getTexturedFragmentShaderSource());

    // We can set the shader once, since we have only one
    glUseProgram(texturedShaderProgram);
    GLuint texturedColorLocation = glGetUniformLocation(texturedShaderProgram, "objectColor");
    glUseProgram(shaderProgram);


    // Camera parameters for view transform
    vec3 cameraPosition(0.6f, 1.0f, 10.0f);
    vec3 cameraLookAt(0.0f, 0.0f, -1.0f);
    vec3 cameraUp(0.0f, 1.0f, 0.0f);

    // Other camera parameters
    float cameraSpeed = 5.0f;
    float cameraFastSpeed = 2 * cameraSpeed;
    float cameraHorizontalAngle = 90.0f;
    float cameraVerticalAngle = 0.0f;

    // For frame time
    float lastFrameTime = glfwGetTime();
    int lastMouseLeftState = GLFW_RELEASE;
    double lastMousePosX, lastMousePosY;
    glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);

    // Other OpenGL states to set once
    // Enable Backface culling
    //glEnable(GL_CULL_FACE);

    // @TODO 1 - Enable Depth Test
    // ...
    glEnable(GL_DEPTH_TEST);

    GLuint colorLocation = glGetUniformLocation(shaderProgram, "objectColor");


    // initializing all the variable that will be used for transformations
    float worldRotateXFactor = 0.0f;
    float worldRotateYFactor = 0.0f;


    GLenum mode = GL_TRIANGLES;
   
    float scaleNumber = 1.0f;
    float rotateFactor = 0.0f;
    
    vec3 translationVector = vec3(0.0f);
    vec3 translationVector2 = vec3(0.0f);
    vec3 scaleVector = vec3(1.0f);
    vec3 yRotationVector = vec3(0.0f, 1.0f, 0.0f);
    vec3 xRotationVector = vec3(1.0f, 0.0f, 0.0f);

    LineModel* lineModel = new LineModel();
    SnowManDrawer* snowManDrawer = new SnowManDrawer();
    // Entering Main Loop
    while (!glfwWindowShouldClose(window))
    {
        // Frame time calculation
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        // Each frame, reset color of each pixel to glClearColor
        // @TODO 1 - Clear Depth Buffer Bit as well
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Set projection matrix for shader
        mat4 projectionMatrix = glm::perspective(0.5f,            // field of view in degrees
            1024.0f / 768.0f,  // aspect ratio
            0.01f, 100.0f);   // near and far (near > 0)
        

        // Set initial view matrix
        mat4 viewMatrix = lookAt(cameraPosition,  // eye
            cameraPosition + cameraLookAt,  // center
            cameraUp); // up

        // creating pointers to matrices that compose modelViewProjection (and the rotationMatrix
        glUseProgram(shaderProgram);
        GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
        GLuint worldMatrixLocationColor = glGetUniformLocation(shaderProgram, "worldMatrix");
        GLuint rotationColorMatrixLocation = glGetUniformLocation(shaderProgram, "globalRotationMatrix");

        glUseProgram(texturedShaderProgram);
        viewMatrixLocation = glGetUniformLocation(texturedShaderProgram, "viewMatrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        projectionMatrixLocation = glGetUniformLocation(texturedShaderProgram, "projectionMatrix");
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
        GLuint worldMatrixLocationTexture = glGetUniformLocation(texturedShaderProgram, "worldMatrix");
        GLuint rotationMatrixLocation = glGetUniformLocation(texturedShaderProgram, "globalRotationMatrix");

        // setting initial color (green) for the grid
        glUniform3fv(colorLocation, 1, glm::value_ptr(glm::vec3(0.0f, 1.0f, 0.0f)));

        // Draw ground
        mat4 groundWorldMatrix;

        // create groupMatrix which is used to transform all the parts, using predifined data
        translationVector[1] = 2.5f;
        mat4 groupMatrix =  translate(mat4(1.0f), translationVector) * rotate(mat4(1.0f), glm::radians(rotateFactor), yRotationVector) * scale(mat4(1.0f), scaleNumber * vec3(1.0f));
        mat4 worldRotationMatrix = rotate(mat4(1.0f), glm::radians(worldRotateYFactor), yRotationVector) * rotate(mat4(1.0f), glm::radians(worldRotateXFactor), xRotationVector);

        // create world rotation matrix, which is used to rotate the whole world
        snowManDrawer->setGroupMatrix(groupMatrix);
        glUniformMatrix4fv(rotationMatrixLocation, 1, GL_FALSE, &worldRotationMatrix[0][0]);

        glBindTexture(GL_TEXTURE_2D, grassTextureID);
        glUniform3fv(texturedColorLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        mat4 pillarWorldMatrix;

        snowManDrawer->drawSnowCube(worldMatrixLocationTexture, depthArray,width,height);

        glUseProgram(shaderProgram);
        glUniform3fv(colorLocation, 1, glm::value_ptr(glm::vec3(0.0f, 1.0f, 0.0f)));

        glUniformMatrix4fv(rotationColorMatrixLocation, 1, GL_FALSE, &worldRotationMatrix[0][0]);


        snowManDrawer->drawGrid(worldMatrixLocationColor);
        //drawing the axis
        //x is blue
        glUniform3fv(colorLocation, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 1.0f)));
        groundWorldMatrix = scale(mat4(1.0f), vec3(0.05f)) * translate(mat4(1.0f), vec3(50.0f, 0.01f, 0.0f));
        lineModel->Draw(worldMatrixLocationColor, groundWorldMatrix);

        //z is red
        glUniform3fv(colorLocation, 1, glm::value_ptr(glm::vec3(1.0f, 0.0f, 0.0f)));
        groundWorldMatrix = scale(mat4(1.0f), vec3(0.05f)) * translate(mat4(1.0f), vec3(0.0f, 0.01f, 50.0f)) * rotate(mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        lineModel->Draw(worldMatrixLocationColor, groundWorldMatrix);
        
        //y is white
        glUniform3fv(colorLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        groundWorldMatrix = scale(mat4(1.0f), vec3(0.05f)) * translate(mat4(1.0f), vec3(0.0f, 50.01f, 0.0f)) * rotate(mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        lineModel->Draw(worldMatrixLocationColor, groundWorldMatrix);

        mat4 cubeMatrix = translate(mat4(1.0f), vec3((float)cameraPosition.x - 1.0f, (float)cameraPosition.y - 1.0f, (float)cameraPosition.z));
        //snowManDrawer->drawTestCube(worldMatrixLocationColor, cubeMatrix);

        snowManDrawer->drawBody(worldMatrixLocationColor);
        //building olaf, using relative positioning by applying transformation of the following order T * R * S
        
        glUniform3fv(colorLocation, 1, glm::value_ptr(glm::vec3(0.98f, 0.98f, 0.98f)));
        snowManDrawer->drawArmsAndLegs(worldMatrixLocationColor, footRotationFactor);

        //right eye
        glUniform3fv(colorLocation, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f))); // setting color of cube
        snowManDrawer->drawEyesAndMouth(worldMatrixLocationColor);

        //hat
        glUseProgram(texturedShaderProgram);
        glBindTexture(GL_TEXTURE_2D, silverTextureID);
        glUniform3fv(texturedColorLocation, 1, glm::value_ptr(glm::vec3(0.82f, 0.82f, 0.82f)));
        snowManDrawer->drawHat(worldMatrixLocationTexture);

        //nose
        glBindTexture(GL_TEXTURE_2D, carrotTextureID);
        glUniform3fv(texturedColorLocation, 1, glm::value_ptr(glm::vec3(0.90f, 0.65f, 0.0f)));
        //glUniform3fv(colorLocation, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.0f))); // setting color of cube
        snowManDrawer->drawNose(worldMatrixLocationColor);

        // Handle inputs
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // This was solution for Lab02 - Moving camera exercise
        // We'll change this to be a first or third person camera
        bool fastCam = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
        bool shiftHold = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
        float currentCameraSpeed = (fastCam) ? cameraFastSpeed : cameraSpeed;


        // @TODO 4 - Calculate mouse motion dx and dy
        //         - Update camera horizontal and vertical angle

        double mousePosX, mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY);

        double dx = mousePosX - lastMousePosX;
        double dy = mousePosY - lastMousePosY;

        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;

        // Convert to spherical coordinates
        const float cameraAngularSpeed = 60.0f;
        
        

        // Clamp vertical angle to [-85, 85] degrees
        cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, cameraVerticalAngle));
        if (cameraHorizontalAngle > 360)
        {
            cameraHorizontalAngle -= 360;
        }
        else if (cameraHorizontalAngle < -360)
        {
            cameraHorizontalAngle += 360;
        }

        float theta = radians(cameraHorizontalAngle);
        float phi = radians(cameraVerticalAngle);

        cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
        vec3 cameraSideVector = glm::cross(cameraLookAt, vec3(0.0f, 1.0f, 0.0f));

        glm::normalize(cameraSideVector);

        cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;
        cameraVerticalAngle -= dy * cameraAngularSpeed * dt;

        //to do shift see fast cam
        // @TODO 5 = use camera lookat and side vectors to update positions with ASDW
        // adjust code below
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) // move camera to the left
        {
            cameraPosition -= cameraSideVector * currentCameraSpeed * dt;
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) // move camera to the right
        {
            cameraPosition += cameraSideVector * currentCameraSpeed * dt;
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) // move camera up
        {
            cameraPosition -= cameraLookAt * currentCameraSpeed * dt;
        }

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) // move camera down
        {
            cameraPosition += cameraLookAt * currentCameraSpeed * dt;
        }
        //TRANSFORMATIONS
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // move olaf to the left
        {
            if (shiftHold && fmod(rotateFactor, 360.0f) != 270.0f)
            {
                rotateFactor += 1.0f;
            }
            else
            {
                translationVector[0] -= 0.1f;
                snowManAnimation();
            }
                
            
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // move olaf to the right
        {
            if (shiftHold && fmod(rotateFactor, 360.0f) != 90.0f)
            {
                rotateFactor += 1.0f;
            }
            else
            {
                translationVector[0] += 0.1f;
                snowManAnimation();
            }
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // move olaf up
        {
            if (shiftHold && fmod(rotateFactor, 360.0f) != 0.0f)
            {
                rotateFactor += 1.0f;
            }
            else
            {
                translationVector[2] += 0.1f;
                snowManAnimation();
            }
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // move olaf down
        {
            if (shiftHold && fmod(rotateFactor, 360.0f) != 180.0f)
            {
                rotateFactor += 1.0f;
            }
            else
            {
                translationVector[2] -= 0.1f;
                snowManAnimation();
            }
        }
        if (!shiftHold && glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) // move olaf up
        {
            rotateFactor += 1.0f;
        }
        if (!shiftHold && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) // move olaf down
        {
            rotateFactor -= 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) // reset
        {
            translationVector *= 0.0f;
            scaleNumber = scaleNumber * 0.0f + 1.0f;
            rotateFactor = rotateFactor * 0.0f;
            worldRotateXFactor = 0.0f;
            worldRotateYFactor = 0.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) // Getting bigger
        {
            scaleNumber -= 0.01f;
            if (scaleNumber < 0)
            {
                scaleNumber = scaleNumber * 0.0f + 1.0f;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) // getting smaller
        {
            scaleNumber += 0.01f;

        }
        
        

        // TODO 6
        // Set the view matrix for first cameras
        // - In first person, camera lookat is set like below

        float radius = 5.0f;
        glm::vec3 position = cameraPosition - radius * cameraLookAt;
        viewMatrix = lookAt(position, position + cameraLookAt, cameraUp);

        // End Frame
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // Shutdown GLFW
    glfwTerminate();

    for (int i = 0; i < 10; ++i) {
        delete[] depthArray[i];
    }
    //Free the array of pointers
    delete[] depthArray;

    return 0;
}
