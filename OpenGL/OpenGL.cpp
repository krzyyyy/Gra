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

	Program program1;
	auto vertexShaderPath = fs::path("VertexShader.glsl");
	auto fragmenShaderPath = fs::path("FragmentShader.glsl");


	if (!(fs::exists(vertexShaderPath) && fs::exists(fragmenShaderPath)))
	{
		cout << "I can't load shader" << endl;
		throw std::exception();
	}
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

	program1.Initialize(vertexShaderPath, fragmenShaderPath);
	program1.CompileAndLink();

	RenderObject<ModelCreators::CubeCreator>::getInstance().Initialize();
	RenderObject<ModelCreators::CylinderCreator>::getInstance().Initialize();
	//auto cubes = std::vector<Object<RenderObject<ModelCreators::CubeCreator>>>(10);
		//std::make_unique< IObject >(Object<RenderObject<ModelCreators::CubeCreator>>()),
			//std::make_unique< Object<RenderObject<ModelCreators::CubeCreator>>>(),
			//std::make_unique< Object<RenderObject<ModelCreators::CubeCreator>>>(),
			//std::make_unique< Object<RenderObject<ModelCreators::CubeCreator>>>()
	auto cubes = std::vector<std::unique_ptr<IObject>>();
	cubes.emplace_back(std::make_unique< Object<RenderObject<ModelCreators::CubeCreator>>>());
	cubes.emplace_back(std::make_unique< Object<RenderObject<ModelCreators::CubeCreator>>>());
	cubes.emplace_back(std::make_unique< Object<RenderObject<ModelCreators::CylinderCreator>>>());
	cubes.emplace_back(std::make_unique< Object<RenderObject<ModelCreators::CubeCreator>>>());
	cubes.emplace_back(std::make_unique< Object<RenderObject<ModelCreators::CylinderCreator>>>());
	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	for (int i = 0; i < cubes.size(); ++i)
	{
		cubes[i]->translate(cubePositions[i]);
	}



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
		program1.setUniform(camera.getViewMatrix(), "view");
		program1.setUniform(camera.getProjectionMatrix(), "projection");

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		float timeValue = glfwGetTime();
		cv::Mat rotationVector = (cv::Mat_<float>(1, 3) << 0.4, 0.03, 0.000);
		auto rotationMatrix = cv::Mat();
		cv::Rodrigues(rotationVector, rotationMatrix);
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		//glm::mat4 view = glm::mat4(1.0f);
		//glm::mat4 projection = glm::mat4(1.0f);

		for (auto& cube : cubes)
		{

			cube->rotate(glm::radians(1.f), glm::vec3(1.0f, 0.3f, 0.0f));
			cube->render(program1);
		}
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