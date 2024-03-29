#pragma once
#include "BasicShapesCreators.h"

namespace ModelCreators
{
	struct RectangleCreator
	{

		MultidimensionalVector<float, 3> getShape()
		{
			const std::vector<cv::Point3f> meshVerticles = std::vector<cv::Point3f>{ cv::Point3f(-0.5, 0.6, 0), cv::Point3f(0.5, 0.6, 0),
			cv::Point3f(0.5, 0.7, 0), cv::Point3f(-0.5, 0.7, 0) };
			auto modelTriangeVector = MultidimensionalVector<float, 3>();
			addTrianglesFromConvexPlane(meshVerticles, modelTriangeVector);
			return modelTriangeVector;
		}
	};

}