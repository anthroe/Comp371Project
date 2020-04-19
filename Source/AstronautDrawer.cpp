
#include "AstronautDrawer.h"
#include "glm/gtx/string_cast.hpp"

using namespace glm;

AstronautDrawer::AstronautDrawer()
{
	createModels();
	mMass = 1.0f;
}

AstronautDrawer::~AstronautDrawer()
{

}
void AstronautDrawer::setGroupMatrix(mat4 astronautGroupMatrix)
{
	groupMatrix = astronautGroupMatrix;
}

void AstronautDrawer::draw(Shader* shader, mat4 worldRotationMatrix)
{
	// create groupMatrix which is used to transform all the parts, using predifined data
	mat4 groupMatrix = translate(mat4(1.0f), position) * rotate(mat4(1.0f), glm::radians(rotateFactor + 180.0f), vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), scaleNumber * vec3(1.0f));
	// create world rotation matrix, which is used to rotate the whole world

	for (int i = 0; i < models.size(); i++) {
		models[i]->draw(shader, groupMatrix);
	}
}
void AstronautDrawer::astronautAnimation()
{
}

void AstronautDrawer::Update(float dt)
{

	position += dt * mVelocity;
	//mPosition += dt * mVelocity;

	//std::cout << dt << std::endl;
}

void AstronautDrawer::Accelerate(glm::vec3 acceleration, float delta)
{
	if (mMass != 0.0f) { //No acceleration for massless objects
		if (position.y > 0.0f) {
			if (mVelocity.y > -0.010000) {
				mVelocity += acceleration * delta;
			}
		}
	}
}

void AstronautDrawer::Angulate(glm::vec3 torque)
{
	if (mMass != 0.0f) {//No angular acceleration for massless objects
		mAngularAxis = torque;
		mAngularVelocityInDegrees += glm::dot(mAngularAxis, mRotationAxis);
	}
}

void AstronautDrawer::Jump()
{
	position.y += 1.5f;
	mVelocity.y = 0.05f;
}

bool AstronautDrawer::ContainsModel(Model* model)
{
	vec3 modelPosition = model->position;
	vec3 modelHitbox = model->hitbox;
	float distance = glm::distance(position, modelPosition);
	float yDistance = abs(modelPosition.y - position.y);
	// Calculating distance between the center point and the farthest point in the model
	float XZHitbox = sqrt((modelHitbox.x * modelHitbox.x) + (modelHitbox.z * modelHitbox.z));
	float diagonalHitbox = sqrt((XZHitbox * XZHitbox) + (modelHitbox.y * modelHitbox.y));
	return distance <= diagonalHitbox && yDistance <= modelHitbox.y;
}
bool AstronautDrawer::CollideXZ(Model* model) {
	return (model->position.y > position.y + model->hitbox.y
		&& abs(model->position.x - position.x) < model->hitbox.x + hitbox.x
		&& abs(model->position.z - position.z) < model->hitbox.z + hitbox.z);
}
void AstronautDrawer::createModels() {
	int astronautVerticesCount;
	GLuint astronautVAO = setupModelEBO("../Resources/Assets/Models/astronaut.obj", astronautVerticesCount);

	#if defined(PLATFORM_OSX)
		GLuint astronautTextureID = loadTexture("Textures/snow.jpg");
	#else
		GLuint astronautTextureID = loadTexture("../Resources/Assets/Textures/snow.jpg");
	#endif
		/* position, rotation, scaling, hitbox, color, texture, renderType*/
		TexturedModel* astronaut = new TexturedModel(
			vec3(0.0f, 0.5f, 0.0f),
			vec3(0.0f, 0.0f, 0.0f),
			vec3(0.75f, 0.75f, 0.75f),
			vec3(0.5f, 1.0f, 0.5f),
			vec3(1.0f, 1.0f, 1.0f),
			astronautTextureID,
			GL_TRIANGLES);

	astronaut->setVAO(astronautVAO, astronautVerticesCount);
	models.push_back(astronaut);
}