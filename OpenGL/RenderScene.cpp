#include "RenderScene.h"


RenderScene::RenderScene()
{

}

void RenderScene::RenderObjects(const std::vector<std::shared_ptr<IObject>>& objects, const Camera& camera)
{
	//auto objectsCopy = objects;
	//std::sort(objectsCopy.begin(), objectsCopy.end(), [](const auto& object1, const auto& object2)
	//	{
	//		return object1->GetObjectType() > object2->GetObjectType();
	//	});
	for (const auto& object : objects)
	{
		renderObject(object, camera);
		renderParametersBar(object, camera);
	}

}
void RenderScene::InitilizeShaders(const std::vector<std::tuple<std::string, std::string, std::string>>& objectsShadersNames)
{
	for (const auto& names : objectsShadersNames)
	{
		const auto [keyName, vertexName, fragmentName] = names;
		if (!(fs::exists(vertexName) && fs::exists(fragmentName)))
		{
			std::cout << "I can't load elements shader" << std::endl;
			throw std::exception();
		}
		auto newProgram = Program(vertexName, fragmentName);
		//sword shaders loading
		newProgram.CompileAndLink();
		programs.emplace(std::make_pair(std::string(keyName), std::move(newProgram)));
		//
	}

}

void RenderScene::InitializeModels()
{
	for (auto& model : models)
	{
		model.second->Initialize();
	}
}

void RenderScene::AddModel(std::string modelName, IRenderObject& model)
{
	models[modelName] = &model;
}

void RenderScene::renderParametersBar(const std::shared_ptr<IObject>& object, const Camera& camera)
{
	auto liveObject = std::dynamic_pointer_cast<Logic::ILiveObject>(object);
	if (!liveObject)
	{
		return;
	}
	auto& program = programs["LiveBar"];
	program.useProgram();
	program.setUniform(camera.getViewMatrix(), "view");
	program.setUniform(camera.getProjectionMatrix(), "projection");
	glm::mat4 objectGlobalPosition = object->GetGlobalPosition();
	Logic::LiveTypes liveParameters = liveObject->GetLiveParameters();
	auto isLive = std::holds_alternative<Logic::ObjectLogic>(liveParameters);
	if (!isLive)
		return;
	const auto& liveobject = std::get<Logic::ObjectLogic>(liveParameters);
	double liveFactor = liveobject.currentLive / liveobject.maxLive;
	//auto objectGlobalPositionRed = glm::scale(objectGlobalPosition, glm::vec3(1-liveFactor, 1, 1));
	//objectGlobalPositionRed = glm::translate(objectGlobalPositionRed, glm::vec3(-(liveFactor)/2, 0, 0));
	program.setUniform(float(1.f - liveFactor), "liveFactor");
	program.setUniform(true, "lowerBar");
	program.setUniform(glm::vec3(1.f, 0.f, 0.f), "color");
	program.Render(objectGlobalPosition, *models["RectangleModel"]);


	//auto objectGlobalPositionGreen = glm::scale(objectGlobalPosition, glm::vec3( liveFactor, 1, 1));
	//objectGlobalPositionGreen = glm::translate(objectGlobalPositionGreen, glm::vec3(0.4, 0, 0));

	program.setUniform(float(liveFactor), "liveFactor");
	program.setUniform(false, "lowerBar");
	program.setUniform(glm::vec3(0.f, 1.f, 0.f), "color");

	
	program.Render(objectGlobalPosition, *models["RectangleModel"]);


}

void RenderScene::renderObject(const std::shared_ptr<IObject>& object, const Camera& camera)
{
	std::string objectType = object->GetObjectType();
	auto modelName = object->GetObjectModel();
	auto& program = programs[objectType];
	program.useProgram();
	program.setUniform(camera.getViewMatrix(), "view");
	program.setUniform(camera.getProjectionMatrix(), "projection");
	program.Render(object->GetGlobalPosition(), *models[modelName]);
}

