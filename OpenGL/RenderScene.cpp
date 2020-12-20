#include "RenderScene.h"


void RenderScene::RenderObjects(const std::vector<std::shared_ptr<IObject>>& objects, const Camera& camera)
{
	//auto objectsCopy = objects;
	//std::sort(objectsCopy.begin(), objectsCopy.end(), [](const auto& object1, const auto& object2)
	//	{
	//		return object1->GetObjectType() > object2->GetObjectType();
	//	});
	for (const auto& object : objects)
	{
		std::string objectType = object->GetObjectType();
		auto& program = programs[objectType];
		program.useProgram();
		program.setUniform(camera.getViewMatrix(), "view");
		program.setUniform(camera.getProjectionMatrix(), "projection");
		program.Render(object);
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
