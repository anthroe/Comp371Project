#include "RockDrawer.h"

RockDrawer::RockDrawer()
{
#if defined(PLATFORM_OSX)
	grassTextureID = loadTexture("Textures/rock.jpg");
#else
	rockTextureID = loadTexture("../Resources/Assets/Textures/rock.jpg");
#endif
	vertexCount = 0;
	srand((unsigned)time(NULL));
	generateRock();
}
RockDrawer::~RockDrawer()
{

	glDeleteVertexArrays(1, &vao);
}

void RockDrawer::draw(Shader* shader)
{

	shader->use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, rockTextureID);

	shader->setVec3("objectColor", vec3(1.0f, 1.0f, 1.0f));
	
	shader->setMat4("worldMatrix", translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)));
}

void RockDrawer::generateRock() {
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, rockTextureID);
	// Setting world matrix for the loaded model

	glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}