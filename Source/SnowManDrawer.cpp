
#include "SnowManDrawer.h"
#include "glm/gtx/string_cast.hpp"
using namespace glm;

SnowManDrawer::SnowManDrawer()
{
    sphere = new SphereModel();
    coloredCube = new CubeModel();
    texturedCube1 = new TexturedCubeModel();
    mMass = 1.0f;
    // Load Textures
    #if defined(PLATFORM_OSX)
        silverTextureID = loadTexture("Textures/silver.jpg");
        carrotTextureID = loadTexture("Textures/carrot.jpg");
        snowTextureID = loadTexture("Textures/snow.jpg");
    #else
        silverTextureID = loadTexture("../Resources/Assets/Textures/silver.jpg");
        carrotTextureID = loadTexture("../Resources/Assets/Textures/carrot.jpg");
        snowTextureID = loadTexture("../Resources/Assets/Textures/snow.jpg");
    #endif
}




SnowManDrawer::~SnowManDrawer()
{

}

void SnowManDrawer::setMode(GLenum drawMode)
{
    mode = drawMode;
}
void SnowManDrawer::setGroupMatrix(mat4 snowManGroupMatrix)
{
    groupMatrix = snowManGroupMatrix;
}

void SnowManDrawer::drawArmsAndLegs(Shader * shader, float footRotationFactor)
{
    shader->use();
    mat4 leftFoot = translate(mat4(1.0f), vec3(0.0f, 0.5f, 0.0f)) * rotate(mat4(1.0f), glm::radians(footRotationBase + footRotationFactor), xRotationVector);
    mat4 rightFoot = translate(mat4(1.0f), vec3(0.0f, 0.5f, 0.0f)) * rotate(mat4(1.0f), glm::radians(footRotationBase - footRotationFactor), xRotationVector);
    mat4 leftArm = translate(mat4(1.0f), vec3(1.55f, 1.5f, 0.0f)) * rotate(mat4(1.0f), glm::radians(footRotationBase + footRotationFactor), xRotationVector);
    mat4 rightArm = translate(mat4(1.0f), vec3(-1.55f, 1.5f, 0.0f)) * rotate(mat4(1.0f), glm::radians(footRotationBase - footRotationFactor), xRotationVector);

    //red right arm
    mat4 groundWorldMatrix = groupMatrix * rightArm * translate(mat4(1.0f), vec3(0.65f, 0.0f, 0.0f)) * rotate(mat4(1.0f), glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 1.5f, 0.2f));
    coloredCube->Draw(shader, groundWorldMatrix, mode);

    //white left arm
    groundWorldMatrix = groupMatrix * leftArm * translate(mat4(1.0f), vec3(-0.65f, 0.0f, 0.0f)) * rotate(mat4(1.0f), glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 1.5f, 0.2f));
    coloredCube->Draw(shader, groundWorldMatrix, mode);

    //left foot yellow
    groundWorldMatrix = groupMatrix * leftFoot * scale(mat4(1.0f), vec3(0.2f, 0.5f, 0.2f)) * translate(mat4(1.0f), vec3(-1.5f, 0.5f, 0.0f));
    coloredCube->Draw(shader, groundWorldMatrix, mode);

    //right foot
    groundWorldMatrix = groupMatrix * rightFoot * scale(mat4(1.0f), vec3(0.2f, 0.5f, 0.2f)) * translate(mat4(1.0f), vec3(1.5f, 0.5f, 0.0f)); //transforming
    coloredCube->Draw(shader, groundWorldMatrix, mode);

}
void SnowManDrawer::drawBody(Shader * shader) //legs and body and head
{
    shader->use();
    mat4 groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.0f, 1.1f, 0.0f)) * scale(mat4(1.0f), vec3(0.75f));
    sphere->Draw(shader, groundWorldMatrix);

    groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.0f, 2.1f, 0.0f)) * scale(mat4(1.0f), vec3(0.60f));
    sphere->Draw(shader, groundWorldMatrix);


}
void SnowManDrawer::drawEyesAndMouth(Shader * shader)
{
    shader->use();
    mat4 groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.12f, 2.3f, 0.60f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.1f)); //transforming
    coloredCube->Draw(shader, groundWorldMatrix, mode);

    //left eye
    groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(-0.12f, 2.3f, 0.60f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.1f)); //transforming
    coloredCube->Draw(shader, groundWorldMatrix, mode);


    //mouth
    groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.0f, 1.9f, 0.60f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.1f)); //transforming
    coloredCube->Draw(shader, groundWorldMatrix, mode);

}
void SnowManDrawer::drawHat(Shader * shader)
{
    shader->use();
    //hat
    mat4 groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.0f, 3.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.3f, 0.7f, 0.3f));
    //coloredCube->Draw(shader, groundWorldMatrix, mode);
    texturedCube1->Draw(shader, groundWorldMatrix);

}
void SnowManDrawer::drawNose(Shader * shader)
{
    shader->use();
    mat4 groundWorldMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.0f, 2.1f, 0.8f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 0.5f)); //transforming
    //coloredCube->Draw(shader, groundWorldMatrix, mode);
    texturedCube1->Draw(shader, groundWorldMatrix);


}
void SnowManDrawer::drawSnow(Shader * shader)
{
    mat4 pillarWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(100.0f, 0.1f, 100.0f));

    texturedCube1->Draw(shader, pillarWorldMatrix);

}

void SnowManDrawer::draw(Shader* shader, Shader* textureShader, mat4 worldRotationMatrix)
{
    // create groupMatrix which is used to transform all the parts, using predifined data
    mat4 groupMatrix = translate(mat4(1.0f), translationVector) * rotate(mat4(1.0f), glm::radians(rotateFactor), yRotationVector) * scale(mat4(1.0f), scaleNumber * vec3(1.0f));
    // create world rotation matrix, which is used to rotate the whole world
    setGroupMatrix(groupMatrix);

    drawBody(shader);
    //building olaf, using relative positioning by applying transformation of the following order T * R * S

    shader->setVec3("objectColor", vec3(0.98f, 0.98f, 0.98f));
    drawArmsAndLegs(shader, footRotationFactor);

    //right eye
    shader->setVec3("objectColor", vec3(0.0f, 0.0f, 0.0f)); // setting color of cube
    drawEyesAndMouth(shader);

    //hat
    textureShader->use();
    glBindTexture(GL_TEXTURE_2D, silverTextureID);
    textureShader->setVec3("objectColor", glm::vec3(0.82f, 0.82f, 0.82f));
    drawHat(textureShader);

    //nose
    glBindTexture(GL_TEXTURE_2D, carrotTextureID);
    textureShader->setVec3("objectColor", glm::vec3(0.90f, 0.65f, 0.0f));
    //glUniform3fv(colorLocation, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.0f))); // setting color of cube
    drawNose(shader);

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
}
float SnowManDrawer::snowRotateAnimation(float rotateFactor, float angleRequired)
{
    /*
        1 --> A, 2 --> D, 3 --> W, 4 --> S
    */
    if (fmod(rotateFactor, 360.0f) != angleRequired)
        rotateFactor += 1.0f;
    return rotateFactor;
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
            if (mVelocity.y > 0.00000) {
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
