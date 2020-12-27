#pragma once
#include "MultidimensionalVector.h"

namespace ModelCreators
{
	void addTrianglesFromConvexPlane(const std::vector<cv::Point3f>& points, MultidimensionalVector<float, 3>& model);
	float getVectorElement(char dimention, cv::Point3f point);
}

	//void testFunction()
	//{
	//	auto vec1 = MultidimensionalVector<int, 2, 1>{
	//	{1, 2, 3},
	//	{11, 22, 33},
	//	};
	//	auto vec2 = MultidimensionalVector<int, 3>{
	//	{1, 2, 3},
	//	{11, 22, 33},
	//	};
	//	auto vec3 = vec1.concatenate(vec2);
	//}


