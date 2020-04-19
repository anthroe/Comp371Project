#include <EnvironmentDrawer.h>

EnvironmentDrawer::EnvironmentDrawer(double** depthArray) {
    //initialzing tree and rock array
    treeAndRockArray = new int* [width];
    for (unsigned int i = 0; i < height; i++) {
        treeAndRockArray[i] = new int[height];
        for (unsigned int j = 0; j < width; j++) {
            treeAndRockArray[i][j] = 0;

        }
    }
    // generating first tree species
    tree1.trunkColor = vec3(randomize(0.5f,1.0f), randomize(0.5f,1.0f), randomize(0.5f,1.0f));
    tree1.leavesColor = vec3(randomize(0.5f,1.0f), randomize(0.5f,1.0f), randomize(0.5f,1.0f));
    // generating second tree species
    tree2.trunkColor = vec3(randomize(0.5f, 1.0f), randomize(0.5f,1.0f), randomize(0.5f,1.0f));
    tree2.leavesColor = vec3(randomize(0.5f, 1.0f), randomize(0.5f,1.0f), randomize(0.5f,1.0f));
    // Generating chance of a tree species to appear more than the other
    treeSpeciesRatio = randomize(0.25f, 0.75f);
    // generating first type of rock
    rock1.color = vec3(randomize(0.5f, 1.0f), randomize(0.5f, 1.0f), randomize(0.5f, 1.0f));
    // generating second type of rock
    rock2.color = vec3(randomize(0.5f, 1.0f), randomize(0.5f, 1.0f), randomize(0.5f, 1.0f));
    // Generating chance of a rock type to appear more than the other
    rockTypeRatio = randomize(0.25f, 0.75f);
    createModels(depthArray);
}
EnvironmentDrawer::~EnvironmentDrawer() {
    for (int i = 0; i < 10; ++i) {
        delete[] treeAndRockArray[i];
    }
    //Free the array of pointers
    delete[] treeAndRockArray;
}
void EnvironmentDrawer::draw(Shader * shader) {
    for (int i = 0; i < models.size(); i++) {
	    models[i]->draw(shader);
    }
}

void EnvironmentDrawer::generateForest()
{
    #if defined(PLATFORM_OSX)
        GLuint treeTextureID = loadTexture("Textures/grass.jpg");
    #else
        GLuint treeTextureID = loadTexture("../Resources/Assets/Textures/grass.jpg");
    #endif
    bool treeDrawn = false;
    while (!treeDrawn)
    {
        int xCord = rand() % width;
        int zCord = rand() % height;
        for (int z = zCord - 4; z <= zCord + 4 && zCord - 4 > 0 && zCord + 4 < height; z++)
        {
            for (int x = xCord - 4; x <= xCord + 4 && xCord - 4 > 0 && xCord + 4 < width; x++)
            {
                int oddsOfTree = rand() % 100;
                if (treeAndRockArray[z][x] != -1 && oddsOfTree <= 80)
                {
                    treeAndRockArray[z][x] = 1;
                }

            }
            treeDrawn = true;
        }
    }
}
// 5% chance of tree generation
void EnvironmentDrawer::generateTrees()
{
#if defined(PLATFORM_OSX)
    GLuint treeTextureID = loadTexture("Textures/grass.jpg");
#else
    GLuint treeTextureID = loadTexture("../Resources/Assets/Textures/grass.jpg");
#endif    
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            int oddsOfTree = rand() % 100;
            if (treeAndRockArray[i][j] != -1 && treeAndRockArray[i][j] != 1 && oddsOfTree <= 5)
            {
                treeAndRockArray[i][j] = 1;
            }
        }
    }
}
// 10% chance of tree generation
void EnvironmentDrawer::generateRocks()
{
    #if defined(PLATFORM_OSX)
        GLuint rockTextureID = loadTexture("Textures/rock.jpg");
    #else
        GLuint rockTextureID = loadTexture("../Resources/Assets/Textures/rock.jpg");
    #endif
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            int oddsOfTree = rand() % 100;
            if (treeAndRockArray[i][j] != -1 && treeAndRockArray[i][j] != 1 && oddsOfTree <= 10)
            {
                treeAndRockArray[i][j] = 2;
            }
        }
    }


}
void EnvironmentDrawer::createModels(double** depthArray) {
    #if defined(PLATFORM_OSX)
        GLuint rockTextureID = loadTexture("Textures/rock.jpg");
		GLuint treeTrunkTextureID = loadTexture("Textures/tree_trunk.jpg");
		GLuint treeLeavesTextureID = loadTexture("Textures/tree_leaves.jpg");
    #else
        GLuint rockTextureID = loadTexture("../Resources/Assets/Textures/rock.jpg");
		GLuint treeTrunkTextureID = loadTexture("../Resources/Assets/Textures/tree_trunk.jpg");
		GLuint treeLeavesTextureID = loadTexture("../Resources/Assets/Textures/tree_leaves.jpg");
    #endif

    int rockVerticesCount;
    GLuint rockVAO = setupModelEBO("../Resources/Assets/Models/rock.obj", rockVerticesCount);
    int trunkVerticesCount;
    GLuint trunkVAO = setupModelEBO("../Resources/Assets/Models/tree_trunk.obj", trunkVerticesCount);
    int leavesVerticesCount;
    GLuint leavesVAO = setupModelEBO("../Resources/Assets/Models/tree_leaves.obj", leavesVerticesCount);

    generateForest();
    generateForest();
    generateForest();
    generateTrees();
    generateRocks();
    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            cout << treeAndRockArray[z][x] << ",";

        }
        cout << endl;
    }
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (treeAndRockArray[i][j] == 1) {
                vec3 trunkColor = vec3(1.0f);
                vec3 leavesColor = vec3(1.0f);
                if (randomize(0.0f, 1.0f) >= treeSpeciesRatio) {
                    trunkColor = tree1.trunkColor;
                    leavesColor = tree1.leavesColor;
                }
                else {
                    trunkColor = tree2.trunkColor;
                    leavesColor = tree2.leavesColor;
                }
                vec3 scaleFactor = vec3(0.5f,0.6f,0.5f);
                vec3 dimensions = vec3(1.0f, 5.0f, 1.0f);
                float xzScale = 0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - 0.2f)));
                float yScale = 0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - 0.2f)));
                float yAngle = 0.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (180.0f - 0.0f)));
                // Adding tree trunk
				/* position, rotation, scaling, color, texture, drawingPrimitive */
                TexturedModel* trunk = new TexturedModel(
                    vec3((j - width / 2) * 2.5f, depthArray[i][j] + 0.5f + dimensions.y * scaleFactor.y * yScale, (i - height / 2) * 2.5f),
                    vec3(0.0f, yAngle, 0.0f),
                    scaleFactor*vec3(xzScale , yScale, xzScale),
                    dimensions * vec3(xzScale / 2, yScale/2, xzScale / 2),
                    trunkColor,
                    treeTrunkTextureID,
                    GL_TRIANGLE_FAN
                );
                // The trunk has a centering offset since it's 0,0,0 position is centered at its base in y. This
                // offset allows us to do calculation on it as if it was centered at half its height in y.
                trunk->centeringOffset = vec3(0.0f, -dimensions.y * scaleFactor.y * yScale, 0.0f);
                trunk->setVAO(trunkVAO, trunkVerticesCount);
				models.push_back(trunk);
    
                scaleFactor = vec3(2.5f);
                // Adding tree leaves
                TexturedModel* leaves = new TexturedModel(
                    vec3((j - width / 2) * 2.5f, depthArray[i][j] - trunk->centeringOffset.y/2, (i - height / 2) * 2.5f),
                    vec3(0.0f, yAngle, 0.0f),
                    scaleFactor * vec3(xzScale, yScale, xzScale),
                    vec3(0.0f),
                    leavesColor,
                    treeLeavesTextureID,
                    GL_TRIANGLES
                );
                leaves->setVAO(leavesVAO, leavesVerticesCount);
				models.push_back(leaves);
            }
            if (treeAndRockArray[i][j] == 2) {
                vec3 color = vec3(1.0f);
                if (randomize(0.0f, 1.0f) >= rockTypeRatio) {
                    color = rock1.color;
                }
                else {
                    color = rock2.color;
                }
                vec3 scaleFactor = vec3(0.2f,0.05f,0.2f);
                vec3 dimensions = vec3(1.0f, 2.0f, 1.0f);
                float xScale = 0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - 0.2f)));
                float yScale = 0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - 0.2f)));
                float zScale = 0.2f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - 0.2f)));
                float yAngle = 0.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (180.0f - 0.0f)));
                /* position, rotation, scaling, hitbox, color, texture, renderType*/
                TexturedModel* rock = new TexturedModel(
                    vec3((j - width / 2) * 2.5f, depthArray[i][j] + 0.5f + dimensions.y * scaleFactor.y * yScale, (i - height / 2) * 2.5f),
                    vec3(0.0f, yAngle, 0.0f),
                    scaleFactor*vec3(xScale, yScale, zScale),
                    dimensions*vec3(xScale/2, yScale/2, zScale/2),
                    color,
                    rockTextureID,
                    GL_TRIANGLES
                );
                
                rock->setVAO(rockVAO, rockVerticesCount);
                models.push_back(rock);
			}
        }
    }

}