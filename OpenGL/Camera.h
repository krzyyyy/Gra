#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "Program.h"

class Camera
{
public:
	Camera();
	void processInput(GLFWwindow* window);
	void mauseCallback(GLFWwindow* window, double posX, double posY);
	void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	glm::mat4 getViewMatrix()const;
	glm::mat4 getProjectionMatrix()const;
	glm::vec3 getCameraPos()const;

private:
	float deltaTime;
	float lastFrameTime;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float lastX = 400, lastY = 300;
	bool firstMouse = true;
	double yaw = 0;
	double pitch = 0;
	double zoom =45;
};

