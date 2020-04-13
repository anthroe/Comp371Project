
#include "SnowManDrawer.h"
#include "glm/gtx/string_cast.hpp"
using namespace glm;

SnowManDrawer::SnowManDrawer()
{
    createModels();
    mMass = 1.0f;
}

SnowManDrawer::~SnowManDrawer()
{

}
void SnowManDrawer::setGroupMatrix(mat4 snowManGroupMatrix)
{
    groupMatrix = snowManGroupMatrix;
}

void SnowManDrawer::draw(Shader* shader, mat4 worldRotationMatrix)
{
    // create groupMatrix which is used to transform all the parts, using predifined data
    mat4 groupMatrix = translate(mat4(1.0f), translationVector) * rotate(mat4(1.0f), glm::radians(rotateFactor), vec3(0.0f,1.0f,0.0f)) * scale(mat4(1.0f), scaleNumber * vec3(1.0f));
    // create world rotation matrix, which is used to rotate the whole world
    setGroupMatrix(groupMatrix);
    for (int i = 0; i < models.size(); i++) {
        models[i]->draw(shader, groupMatrix);
    }
}
void SnowManDrawer::snowManAnimation()
{
    if (footSwitch)
    {
        if (footRotationFactor < 45.0f)
            footRotationFactor += 2.0f;
        else
            footSwitch = false;

    }
    else
    {
        if (footRotationFactor > -45.0f)
            footRotationFactor -= 2.0f;
        else
            footSwitch = true;
    }
    // Left arm
    footAndArmsModels[0]->rotation.x = 180.0f + footRotationFactor;
    // Right arm
    footAndArmsModels[1]->rotation.x = 180.0f - footRotationFactor;
    // Left foot
    footAndArmsModels[2]->rotation.x = 180.0f + footRotationFactor;
    // Right foot
    footAndArmsModels[3]->rotation.x = 180.0f - footRotationFactor;
}

void SnowManDrawer::Update(float dt)
{
    translationVector += dt * mVelocity;
    //mPosition += dt * mVelocity;
    
    //std::cout << dt << std::endl;
}

void SnowManDrawer::Accelerate(glm::vec3 acceleration, float delta)
{
    if (mMass != 0.0f) { //No acceleration for massless objects
        if (translationVector.y > 0.0f) {
            if (mVelocity.y > -0.010000) {
                mVelocity += acceleration * delta;
            }
        }
    }
}

void SnowManDrawer::Angulate(glm::vec3 torque)
{
    if (mMass != 0.0f) {//No angular acceleration for massless objects
        mAngularAxis = torque;
        mAngularVelocityInDegrees += glm::dot(mAngularAxis, mRotationAxis);
    }
}

void SnowManDrawer::BounceOffGround()
{
    translationVector.y = 0.0f;
    mVelocity.y = 0.0f;
}
void SnowManDrawer::Jump()
{
    translationVector.y = 3.0f;
    mVelocity.y = 0.0f;
}

//Assumes the sphere is evenly scaled
bool SnowManDrawer::IntersectsPlane(glm::vec3 planePoint, glm::vec3 planeNormal)
{
    //TODO 1 - Make spheres bounce on the ground
    
    //We simply compare the distance between the ground and sphere center, with its radius
    float radius = GetScaling().x;
    
   
    return glm::dot(planeNormal, GetPosition() - planePoint) < radius;

    return false;
}

bool SnowManDrawer::ContainsPoint(glm::vec3 position)
{
    float radius = GetScaling().x; //This is where the assumption lies
    float distance = glm::distance(GetPosition(), position);

    return distance <= radius;
}
void SnowManDrawer::createModels() {
    /* position, rotation, scaling, color*/
    // Body
    models.push_back(new SphereModel(vec3(0.0f, 1.1f, 0.0f), vec3(0.75f), vec3(1.0f,1.0f,1.0f)));
    models.push_back(new SphereModel(vec3(0.0f, 2.1f, 0.0f), vec3(0.60f), vec3(1.0f,1.0f,1.0f)));
    // Eyes and mouth
    models.push_back(new CubeModel(vec3(0.12f, 2.3f, 0.60f), vec3(0.1f), vec3(0.0f, 0.0f, 0.0f)));
    models.push_back(new CubeModel(vec3(-0.12f, 2.3f, 0.60f), vec3(0.1f), vec3(0.0f, 0.0f, 0.0f)));
    models.push_back(new CubeModel(vec3(0.0f, 1.9f, 0.60f), vec3(0.1f), vec3(0.0f, 0.0f, 0.0f)));
    // Nose
    models.push_back(new CubeModel(vec3(0.0f, 2.1f, 0.8f), vec3(0.1f, 0.1f, 0.5f), vec3(0.90f, 0.65f, 0.0f)));
    // Hat
    models.push_back(new CubeModel(vec3(0.0f, 3.0f, 0.0f), vec3(0.3f, 0.7f, 0.3f), vec3(0.82f, 0.82f, 0.82f)));
    // Left arm
    models.push_back(new CubeModel(vec3(0.9f, 1.5f, 0.0f), vec3(180.0f, 0.0f, -60.0f), vec3(0.2f, 1.5f, 0.2f), vec3(0.98f, 0.98f, 0.98f)));
    footAndArmsModels.push_back(models[7]);
    // Right arm
    models.push_back(new CubeModel(vec3(-0.9f, 1.5f, 0.0f), vec3(180.0f, 0.0f, 60.0f), vec3(0.2f, 1.5f, 0.2f), vec3(0.98f, 0.98f, 0.98f)));
    footAndArmsModels.push_back(models[8]);
    // Left foot
    models.push_back(new CubeModel(vec3(-0.5f, 0.0f, 0.0f), vec3(180.0f, 0.0f, 0.0f), vec3(0.2f, 0.5f, 0.2f), vec3(0.98f, 0.98f, 0.98f)));
    footAndArmsModels.push_back(models[9]);
    // Right foot
    models.push_back(new CubeModel(vec3(0.5f, 0.0f, 0.0f), vec3(180.0f, 0.0f, 0.0f), vec3(0.2f, 0.5f, 0.2f), vec3(0.98f, 0.98f, 0.98f)));
    footAndArmsModels.push_back(models[10]);
}