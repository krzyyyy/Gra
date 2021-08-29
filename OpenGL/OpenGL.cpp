#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <math.h>



#include "RenderObject.h"
#include "Shader.h"
#include <filesystem>
#include "Program.h"
#include <opencv2/opencv.hpp>
#include <concepts>

#include "Camera.h"
#include "RenderObjectFactory.h"
#include "..\Core\SceneMenager.h"
#include "RenderScene.h"
#include "BasicShapesCreators.h"
#include "SphereCreator.h"
#include "..\SharedUtilities\MultiThreadFIFO.h"
#include "..\ShipControler\KeyboardInfo.h"
#include "stb_image.h"


#include "..\ShipControler\ShipControler.h"



namespace fs = std::filesystem;
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::shared_ptr< glm::vec2> mausePosition;
std::shared_ptr< MultiThreadFIFO<char>> clickedButtons;


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
Camera camera;
void mauseCallback(GLFWwindow* window, double posX, double posY);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

int main()
{
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
	mausePosition = std::make_shared<glm::vec2>();
	clickedButtons = std::make_shared<MultiThreadFIFO<char>>();
	auto keyboardInfo = KeyboardInfo(clickedButtons);
	

	auto vertexShaderPath = fs::path("VertexShader.glsl");
	auto fragmenShaderPath = fs::path("FragmentShader.glsl");
	auto fragmenShader2Path = fs::path("FragmentShader2.glsl");
	auto fragmenShaderGeneratorPath = fs::path("GeneratorsFragmentShader.glsl");
	auto fragmenShaderParametesBar = fs::path("ParametersBarFragmentShader.glsl");
	auto vertexShaderParametesBar = fs::path("ParametersBarVertexShader.glsl");

	auto vertexShaderModel = fs::path("VertexShaderModel.glsl");
	auto fragmentShaderModel = fs::path("FragmentShaderModel.glsl");
	RenderObjectFactory renderObjectFactory;

	auto renderScene = RenderScene();
	SceneMenager sceneMenager;
	auto shipControler = std::make_shared<ShipControler>(mausePosition);
	keyboardInfo.AddCommand('w',
		[shipControler]()
		{
			shipControler->SetAction(ShipActions::PitchUp);
		}
	);
	keyboardInfo.AddCommand('s',
		[shipControler]()
		{
			shipControler->SetAction(ShipActions::PitchDown);
		}
	);
	keyboardInfo.AddCommand('a',
		[shipControler]()
		{
			shipControler->SetAction(ShipActions::YawDown);
		}
	);
	keyboardInfo.AddCommand('d',
		[shipControler]()
		{
			shipControler->SetAction(ShipActions::YawUp);
		}
	);
	keyboardInfo.AddCommand('r',
		[shipControler]()
		{
			shipControler->SetAction(ShipActions::Foreward);
		}
	);
	sceneMenager.SetShipControler(shipControler);
	renderScene.InitilizeShaders({
		std::make_tuple("Bullet", vertexShaderPath.string(), fragmenShaderPath.string()),
		std::make_tuple("Sword", vertexShaderPath.string(), fragmenShader2Path.string()),
		std::make_tuple("Generator", vertexShaderPath.string(), fragmenShaderGeneratorPath.string()),
		std::make_tuple("LiveBar", vertexShaderParametesBar.string(), fragmenShaderParametesBar.string()),
		std::make_tuple("Model", vertexShaderModel.string(), fragmentShaderModel.string())
		});
	Model ship2 = Model("models/ship2/OBJ/Intergalactic_Spaceships_Version_2.obj");
	//Model shipModel = Model("models/ship/Ship.obj");
	Model shot = Model("models/shot2/shot2.obj");
	auto swordModel = Model("models/sword/sword.obj");
	renderScene.AddModel(
		"CubeModel",
		renderObjectFactory.CreateRenderObjects("CubeModel")
	);
	renderScene.AddModel(
		"CilinderModel",
		renderObjectFactory.CreateRenderObjects("CilinderModel")
	);
	renderScene.AddModel(
		"SphereModel",
		renderObjectFactory.CreateRenderObjects("SphereModel")
	);
	renderScene.AddModel(
		"RectangleModel",
		renderObjectFactory.CreateRenderObjects("RectangleModel")
	);
	renderScene.AddModel(
		"Ship2",
		ship2
	);
	//renderScene.AddModel(
	//	"ShipModel",
	//	shipModel
	//);
	renderScene.AddModel(
		"ShotModel",
		shot
	);
	renderScene.AddModel(
		"SwordModel",
		swordModel
	);
	renderScene.InitializeModels();

	//OpenGL initialization
	


	stbi_set_flip_vertically_on_load(false);
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
		auto time = glfwGetTime();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		keyboardInfo.ProccessCommands();
		sceneMenager.UpdateScene(camera);
		std::vector<std::shared_ptr<IObject>> objects = sceneMenager.GetObjects();
		renderScene.RenderObjects(objects, camera);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
		cv::waitKey(1);
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
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		clickedButtons->Push('w');
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		clickedButtons->Push('s');
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		clickedButtons->Push('a');
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		clickedButtons->Push('d');
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		clickedButtons->Push('r');
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		clickedButtons->Push('f');
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		clickedButtons->Push('k');
	}
}

void mauseCallback(GLFWwindow* window, double posX, double posY)
{
	*mausePosition = glm::vec2(posX, posY);
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