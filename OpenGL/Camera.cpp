#include "Camera.h"
#include "..\Core\StreamOperators.h"


Camera::Camera(): cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
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
    glm::vec3 cameraPosition = lastObjectPosition - (lastObjectDirection * 6.f);
    return glm::lookAt(cameraPosition, cameraPosition + lastObjectDirection, cameraUp);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective((float)glm::radians(zoom), 800.0f / 600.0f, 0.1f, 100.0f);
}

//glm::vec3 Camera::getCameraPos()const
//{
//    return cameraPos;
//}

void Camera::SetPosition(glm::vec3 position)
{
    lastObjectPosition = position;
}

void Camera::SetDiretion(glm::vec3 direction)
{
    lastObjectDirection = direction;
}
