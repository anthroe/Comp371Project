#include "GroundDrawer.h"

GroundDrawer::GroundDrawer()
{
    srand((unsigned)time(NULL));
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
void GroundDrawer::createModels() {
    #if defined(PLATFORM_OSX)
        GLuint grassTextureID = loadTexture("Textures/grass.jpg");
        GLuint grassTextureID = loadTexture("Textures/space.jpg");
    #else
        GLuint grassTextureID = loadTexture("../Resources/Assets/Textures/grass.jpg");
        GLuint spaceTextureID = loadTexture("../Resources/Assets/Textures/space.jpg");
    #endif
    //sky
    models.push_back(new TexturedCubeModel(vec3(0.0f,20.0f,0.0f), vec3(0.0f), vec3(2000.0f,1.0f,2000.0f), vec3(1.0f), spaceTextureID));
    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            if (depthArray[z][x] > 0)
            {
                for (int y = 0; y < depthArray[z][x]; y++)
                {
                    /* position, rotation, scaling, color, texture*/
                    models.push_back(new TexturedCubeModel(vec3(x - width / 2, y, z - height / 2), vec3(0.0f), vec3 (1.0f), vec3 (1.0f), grassTextureID));
                }
                models.push_back(new TexturedCubeModel(vec3(x - width / 2, depthArray[z][x], z - height / 2), vec3(0.0f), vec3(1.0f), vec3(1.0f), grassTextureID));
            }
        }
    }
}