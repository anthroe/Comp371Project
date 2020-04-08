#include "GroundDrawer.h"

GroundDrawer::GroundDrawer()
{
    #if defined(PLATFORM_OSX)
        grassTextureID = loadTexture("Textures/grass.jpg");
    #else
        grassTextureID = loadTexture("../Resources/Assets/Textures/grass.jpg");
    #endif
    texturedCube = new TexturedCubeModel();
    texturedCube->createTexturedCubeVertexBufferObject();

    srand((unsigned)time(NULL));
    generateGround();
    generateMountain();
    generateMountain();
    generateMountain();
}
GroundDrawer::~GroundDrawer()
{
    for (int i = 0; i < 10; ++i) {
        delete[] depthArray[i];
    }
    //Free the array of pointers
    delete[] depthArray;
}
void GroundDrawer::draw(Shader* shader, double** a, int width, int height)
{
    glBindTexture(GL_TEXTURE_2D, grassTextureID);
    shader->setVec3("objectColor", vec3(1.0f, 1.0f, 1.0f));
    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            if (a[z][x] > 0)
            {
                for (int y = 0; y < a[z][x]; y++)
                {
                    mat4 pillarWorldMatrix = translate(mat4(1.0f), vec3(x - width / 2, y, z - height / 2)) * scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
                    texturedCube->Draw(shader, pillarWorldMatrix);
                }
                mat4 pillarWorldMatrix = translate(mat4(1.0f), vec3(x - width / 2, a[z][x], z - height / 2)) * scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
                texturedCube->Draw(shader, pillarWorldMatrix);
            }
        }
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
    srand(time(0));
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