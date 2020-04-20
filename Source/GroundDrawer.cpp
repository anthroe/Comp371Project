#include "GroundDrawer.h"

GroundDrawer::GroundDrawer()
{
    float r = randomize(0.0f, 1.0f);
    float g = randomize(0.0f, 1.0f);
    float b = randomize(0.0f, 1.0f);
    groundColor = vec3(r, g, b);
    r = randomize(0.5f, 1.0f);
    g = randomize(0.5f, 1.0f);
    b = randomize(0.5f, 1.0f);
    cliffColor = vec3(r, g, b);

    generateGround();
    generateMountain();
    generateMountain();
    generateMountain();
    

    createModels();
}
GroundDrawer::~GroundDrawer()
{
    for (int i = 0; i < 10; ++i) {
        delete[] depthArray[i];
    }
    //Free the array of pointers
    delete[] depthArray;

    
}
void GroundDrawer::draw(Shader* shader)
{
    for (int i = 0; i < models.size(); i++) {
        models[i]->draw(shader);
    }
}

void GroundDrawer::generateGround() {
    // Define the size of the image

    // Create a PerlinNoise object with the reference permutation vector
    PerlinNoise pn;
    depthArray = new double* [width];
    // Visit every pixel of the image and assign a color generated with Perlin noise
    for (unsigned int i = 0; i < height; ++i) {     // y
        depthArray[i] = new double[height];
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

void GroundDrawer::generateMountain()
{
    int xCord = rand() % width;
    int zCord = rand() % height;

    //int xCord = 24;
    //int zCord = 20;



    for (int z = zCord - 2; z <= zCord + 2 && zCord - 2 > 0 && zCord + 2 < height; z++)
    {
        for (int x = xCord - 2; x <= xCord + 2 && xCord - 2 > 0 && xCord + 2 < width; x++)
        {
            int additional = rand() % 2;
            depthArray[z][x] = depthArray[zCord][xCord] + 2 + additional;
            // treeAndRockArray[z][x] = -1;
        }
    }
    for (int z = zCord - 1; z <= zCord + 1 && zCord - 1 > 0 && zCord + 1 < height; z++)
    {
        for (int x = xCord - 1; x <= xCord + 1 && xCord - 1 > 0 && xCord + 1 < width; x++)
        {
            int additional = rand() % 2;
            depthArray[z][x] = depthArray[zCord][xCord] + 2 + additional;
            // treeAndRockArray[z][x] = -1;
        }
    }
    int additional = rand() % 2;
    depthArray[zCord][xCord] = depthArray[zCord][xCord] + 2 + additional;
    // treeAndRockArray[zCord][xCord] = -1;
}
void GroundDrawer::createModels() {
#if defined(PLATFORM_OSX)
    GLuint grassTextureID = loadTexture("Textures/grass.jpg");
    GLuint cliffTextureID = loadTexture("Textures/cliff.jpg");
    GLuint snowTextureID = loadTexture("Textures/snow.jpg");
#else
    GLuint grassTextureID = loadTexture("../Resources/Assets/Textures/grass.jpg");
    GLuint cliffTextureID = loadTexture("../Resources/Assets/Textures/cliff.jpg");
    GLuint snowTextureID = loadTexture("../Resources/Assets/Textures/snow.jpg");
#endif
    float cubeFactor = 2.5f;
    float heightValue = height * cubeFactor;
    float widthValue = width * cubeFactor;
    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            if (depthArray[z][x] > 0)
            {
                float xValue = x * cubeFactor;
                float zValue = z * cubeFactor;
                for (int y = 0; y < depthArray[z][x]; y++)
                {
                    if (y < 2) {
                        /* position, rotation, scaling, color, texture*/
                        models.push_back(new TexturedCubeModel(vec3(xValue - widthValue / 2, y, zValue - heightValue / 2), vec3(0.0f), vec3(cubeFactor, 1.0f, cubeFactor), vec3(groundColor), grassTextureID));
                    }
                    else if (y < 8) {
                        models.push_back(new TexturedCubeModel(vec3(xValue - widthValue / 2, y, zValue - heightValue / 2), vec3(0.0f), vec3(cubeFactor, 1.0f, cubeFactor), vec3(cliffColor), cliffTextureID));
                    }
                    else {
                        models.push_back(new TexturedCubeModel(vec3(xValue - widthValue / 2, y, zValue - heightValue / 2), vec3(0.0f), vec3(cubeFactor, 1.0f, cubeFactor), vec3(1.0f), snowTextureID));
                    }
                }
                if (depthArray[z][x] < 2) {
                    models.push_back(new TexturedCubeModel(vec3(xValue - widthValue / 2, depthArray[z][x], zValue - heightValue / 2), vec3(0.0f), vec3(cubeFactor, 1.0f, cubeFactor), vec3(groundColor), grassTextureID));
                } else if (depthArray[z][x] < 8) {
                    models.push_back(new TexturedCubeModel(vec3(xValue - widthValue / 2, depthArray[z][x], zValue - heightValue / 2), vec3(0.0f), vec3(cubeFactor, 1.0f, cubeFactor), vec3(cliffColor), cliffTextureID));
                }
                else {
                    models.push_back(new TexturedCubeModel(vec3(xValue - widthValue / 2, depthArray[z][x], zValue - heightValue / 2), vec3(0.0f), vec3(cubeFactor, 1.0f, cubeFactor), vec3(1.0f), snowTextureID));
                }
            }
        }
    }

}