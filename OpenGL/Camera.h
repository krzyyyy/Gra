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
	virtual void SetPosition(glm::vec3 position) override;
	virtual void SetDiretion(glm::vec3 direction) override;
private:
	glm::vec3 lastObjectPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 lastObjectDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(1.0f, 0.0f, 0.0f);
	double zoom =45;

	// Inherited via ICamera

};

