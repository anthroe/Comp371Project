#include <Camera.h>

void Camera::setViewProjectionMatrices(Shader * shader) {
    mat4 projectionMatrix = glm::mat4(1.0f);
    mat4 viewMatrix = glm::mat4(1.0f);
    // Set projection matrix for shader
    projectionMatrix = glm::perspective(zoomFactor,            // field of view in degrees
        1024.0f / 768.0f,  // aspect ratio
        0.01f, 100.0f);   // near and far (near > 0)


    // Set initial view matrix
    viewMatrix = lookAt(cameraPosition,  // eye
        cameraPosition + cameraLookAt,  // center
        cameraUp); // up

    // creating pointers to matrices that compose modelViewProjection (and the rotationMatrix
    shader->use();
    shader->setMat4("viewMatrix", viewMatrix);
    shader->setMat4("projectionMatrix", projectionMatrix);
}

void Camera::updateLookAt() {
    // Convert to spherical coordinates
    const float cameraAngularSpeed = 60.0f;


    // Clamp vertical angle to [-85, 85] degrees
    cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, cameraVerticalAngle));
    if (cameraHorizontalAngle > 360)
    {
        cameraHorizontalAngle -= 360;
    }
    else if (cameraHorizontalAngle < -360)
    {
        cameraHorizontalAngle += 360;
    }

    float theta = radians(cameraHorizontalAngle);
    float phi = radians(cameraVerticalAngle);

    cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
    vec3 cameraSideVector = glm::cross(cameraLookAt, vec3(0.0f, 1.0f, 0.0f));

    glm::normalize(cameraSideVector);
}