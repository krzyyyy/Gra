#pragma once
#include <iostream>
#include "IRenderObject.h"
#include "RenderObject.h"
#include "CilinderCreator.h"
#include "CubeCreator.h"
#include "SphereCreator.h"


class RenderObjectFactory
{
public:
	IRenderObject& CreateRenderObjects(std::string modelName)
	{
		if (modelName == "CubeModel")
		{
			return RenderObject<ModelCreators::CubeCreator>::getInstance();
		}
		else if (modelName == "SphereModel")
		{
			return RenderObject<ModelCreators::SphereCreator>::getInstance();
		}
		else if (modelName == "CilinderModel")
		{
			return RenderObject<ModelCreators::CylinderCreator>::getInstance();
		}
		throw std::exception("Model does not exist");
		//return std::make_unique<IRenderObject>();
	};
};