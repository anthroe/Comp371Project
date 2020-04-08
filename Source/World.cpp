#include <World.h>


World::World() {

    // Setup Camera
	camera = new Camera();
    // Setup Shaders
	shader = new Shader("SHADER", "../Resources/Shaders/VertexShader.glsl", "../Resources/Shaders/FragmentShader.glsl");
	textureShader = new Shader("TEXTURE", "../Resources/Shaders/VertexShaderTexture.glsl", "../Resources/Shaders/FragmentShaderTexture.glsl");
   
    srand((unsigned)time(NULL));
    generateGround();
    generateMountain();
    generateMountain();
    generateMountain();

}
void World::draw() {
	camera->setViewProjectionMatrices(shader);
	camera->setViewProjectionMatrices(textureShader);
    
    mat4 worldRotationMatrix = rotate(mat4(1.0f), glm::radians(worldRotateYFactor), yRotationVector) * rotate(mat4(1.0f), glm::radians(worldRotateXFactor), xRotationVector);
    gridDrawer->draw(shader, worldRotationMatrix);
    snowManDrawer->draw(shader, textureShader, worldRotationMatrix);
    snowManDrawer->drawSnowCube(shader, depthArray, width, height);
    camera->updateLookAt();
}
void World::generateGround() {
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
void World::generateMountain()
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
            std::cout << "test" << endl;
        }
    }
    for (int z = zCord - 1; z <= zCord + 1 && zCord - 1 > 0 && zCord + 1 < height; z++)
    {
        for (int x = xCord - 1; x <= xCord + 1 && xCord - 1 > 0 && xCord + 1 < width; x++)
        {
            int additional = rand() % 2;
            depthArray[z][x] = depthArray[zCord][xCord] + 2 + additional;
            std::cout << "test" << endl;
        }
    }
    int additional = rand() % 2;
    depthArray[zCord][xCord] = depthArray[zCord][xCord] + 2 + additional;
}