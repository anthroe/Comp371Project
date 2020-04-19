#pragma once

#include <Drawer.h>

class AstronautDrawer : public Drawer
{
public:

	float scaleNumber = 1.0f;
	float rotateFactor = 0.0f;

	// Animation
	float footRotationFactor = 0;
	bool footSwitch = true;

	vec3 position = vec3(2.0f, 10.0f, 2.0f);
	vec3 scaling = vec3(1.0f);
	vec3 hitbox = vec3(0.5f);
	mat4 groupMatrix;


	// All our models
	vector<Model*> models;
	// For animation
	vector<Model*> footAndArmsModels;

	AstronautDrawer();
	~AstronautDrawer();
	void setGroupMatrix(glm::mat4 groupMatrix);
	void draw(Shader* shader, mat4 worldRotationMatrix);
	bool ContainsModel(Model* model);
	void astronautAnimation();
	void Accelerate(glm::vec3 force, float dt);
	void Angulate(glm::vec3 torque);
	virtual void Update(float dt);
	glm::vec3 mRotationAxis;
	float     mRotationAngleInDegrees;

	glm::vec3 mVelocity;
	glm::vec3 mAngularAxis;
	float     mAngularVelocityInDegrees;
	void Jump();

	float ContainsPoint(glm::vec3 modelPosition);
	bool CollideXZ(Model* model);

	float mMass = 1.0f;

	void createModels();
	double** depthArray;
	void setDepthArray(double** depthArray1) { depthArray = depthArray1; }
};