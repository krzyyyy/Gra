#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <math.h>

#include "RenderObject.h"
#include "Shader.h"
#include <filesystem>
#include "Program.h"
#include <opencv2/opencv.hpp>
#include "MultidimensionalVector.h"
#include <concepts>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Object.h"
#include "IObject.h"
#include "Camera.h"
#include "CilinderCreator.h"
#include "CubeCreator.h"
#include "SceneMenager.h"

namespace fs = std::filesystem;
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
struct temporary
{
	void getShape() {};
};

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
Camera camera;
void mauseCallback(GLFWwindow* window, double posX, double posY);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

int main()
{
	
	auto vertexShaderPath = fs::path("VertexShader.glsl");
	auto fragmenShaderPath = fs::path("FragmentShader.glsl");
	auto fragmenShader2Path = fs::path("FragmentShader2.glsl");

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mauseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	
	RenderObject<ModelCreators::CubeCreator>::getInstance().Initialize();
	RenderObject<ModelCreators::CylinderCreator>::getInstance().Initialize();


	SceneMenager sceneMenager;
	sceneMenager.initilizeShaders(std::make_pair(vertexShaderPath.string(), fragmenShaderPath.string()),
		std::make_pair(vertexShaderPath.string(), fragmenShader2Path.string()));


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnable(GL_DEPTH_TEST);

	// -----------
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// input
		// -----
		processInput(window);
		camera.processInput(window);
		auto time = glfwGetTime();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		float timeValue = glfwGetTime();
		cv::Mat rotationVector = (cv::Mat_<float>(1, 3) << 0.4, 0.03, 0.000);
		auto rotationMatrix = cv::Mat();
		cv::Rodrigues(rotationVector, rotationMatrix);
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		//glm::mat4 view = glm::mat4(1.0f);
		//glm::mat4 projection = glm::mat4(1.0f);
		sceneMenager.UpdateScene(camera);
		//obj2.Render(program2);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
		cv::waitKey(10);
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------


	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void mauseCallback(GLFWwindow* window, double posX, double posY)
{
	camera.mauseCallback(window, posX, posY);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.scrollCallback(window, xOffset, yOffset);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}