
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
	mat4 groupMatrix = translate(mat4(1.0f), position) * rotate(mat4(1.0f), glm::radians(rotateFactor), vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), scaleNumber * vec3(1.0f));
	// create world rotation matrix, which is used to rotate the whole world
	setGroupMatrix(groupMatrix);
	for (int i = 0; i < models.size(); i++) {
		models[i]->draw(shader, groupMatrix, GL_TRIANGLES);
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
	position.y += 0.4f;
	mVelocity.y = 0.05f;
}

float AstronautDrawer::ContainsPoint(glm::vec3 modelPosition)
{
	float distance = glm::distance(position, modelPosition);
	float yDistance = abs(modelPosition.y - position.y);
	if (distance <= 1.84f && yDistance <= 0.5f)
		return distance;
	return -1;
}
bool AstronautDrawer::CollideXZ(glm::vec3 modelPosition) {
	return (modelPosition.y > position.y + 0.5f && abs(modelPosition.x - position.x) < 1.25 && abs(modelPosition.z - position.z) < 1.25);
}
void AstronautDrawer::createModels() {
	#if defined(PLATFORM_OSX)
		GLuint astronautTextureID = loadTexture("Textures/snow.jpg");
	#else
		GLuint astronautTextureID = loadTexture("../Resources/Assets/Textures/snow.jpg");
	#endif
	models.push_back(new TexturedModel(
		vec3(0.0f, 0.5f, 0.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		astronautTextureID,
		"astronaut2"));
}