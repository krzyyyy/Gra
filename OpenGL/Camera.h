#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../Core/ICamera.h"

class Camera: public ICamera
{
public:
	Camera();
	void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	glm::mat4 getViewMatrix()const;
	glm::mat4 getProjectionMatrix()const;
	virtual void SetCameraPosition(glm::mat4 objectOrientation) override;
private:
	const glm::vec4 upDirection = glm::vec4(0.f, 1.f, 0.f, 0.f);
	glm::vec3 cameraPosition;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	double zoom =45;

	// Inherited via ICamera

};

