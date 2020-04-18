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
		if (models[i]->name == "tree_leaves")
			models[i]->draw(shader, GL_TRIANGLES);
		else if (models[i]->name == "tree_trunk")
			models[i]->draw(shader, GL_TRIANGLE_FAN);
		else if (models[i]->name == "rock")
			models[i]->draw(shader, GL_TRIANGLES);
		else if (models[i]->name == "astronaut")
			models[i]->draw(shader, GL_TRIANGLE_FAN);
    }
}
void EnvironmentDrawer::generateTrees()
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
    generateTrees();
    generateTrees();
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
				float xScale = 0.1f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.25f - 0.1f)));
				float yScale = 0.05f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.15f - 0.05f)));
				float zScale = 0.1f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.25f - 0.1f)));
				float yAngle = 0.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (180.0f - 0.0f)));
				/* position, rotation, scaling, color, texture*/
				models.push_back(new TexturedModel(
					vec3((j - width / 2) * 1.0f, depthArray[i][j] + 0.0f, (i - height / 2.0f)),
					vec3(0.0f, yAngle, 0.0f),
					vec3(xScale * 2.0, yScale * 2.0, zScale * 2.0),
					vec3(1.0f), treeTrunkTextureID,
					"tree_trunk"));
				models.push_back(new TexturedModel(
					vec3((j - width / 2) * 1.0f, depthArray[i][j] + 0.0f, (i - height / 2.0f)),
					vec3(0.0f, yAngle, 0.0f),
					vec3(xScale * 7.0, yScale * 18.0, zScale * 7.0),
					vec3(1.0f), treeLeavesTextureID,
					"tree_leaves"));
            }
            if (treeAndRockArray[i][j] == 2) {
                float xScale = 0.1f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.25f - 0.1f)));
                float yScale = 0.05f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.15f - 0.05f)));
                float zScale = 0.1f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.25f - 0.1f)));
                float yAngle = 0.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (180.0f - 0.0f)));
                /* position, rotation, scaling, color, texture*/
                models.push_back(new TexturedModel(
					vec3((j - width / 2) * 2.5f, 
					depthArray[i][j] +0.4, (i - height/2) * 2.5f),
					vec3(0.0f, yAngle, 0.0f),
					vec3(xScale, yScale, zScale),
					vec3(1.0f),
					rockTextureID,
					"rock"));

			}
        }
    }

}