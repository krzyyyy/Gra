#include "Camera.h"
#include "..\SharedUtilities\StreamOperators.h"
#include "..\SharedUtilities\MathHelperFunctions.h"


Camera::Camera():
    cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    cameraPosition(0.0f, 0.0f, 0.0f),
    cameraDirection(0.0f, 0.0f, 0.0f)
{
}



void Camera::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    zoom -= (float)yOffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective((float)glm::radians(zoom), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Camera::SetCameraPosition(glm::mat4 objectOrientation)
{
    auto cameraModelFrontVector = glm::normalize(glm::vec4(0.f, -0.4f, 1.f, 0.f));
    cameraDirection = objectOrientation * cameraModelFrontVector;
    glm::vec3 objectPosition = Math::GetVectorPosition(objectOrientation);
    cameraPosition = objectPosition - (cameraDirection * 2.f);

}


