#pragma once
#include "MultidimensionalVector.h"

namespace ModelCreators
{
	template<typename T>
	void addTrianglesFromConvexPlane(T&& points, MultidimensionalVector<float, 3>& model);
	float getVectorElement(char dimention, cv::Point3f point);
	template<typename T>
	void addTrianglesFromConvexPlane(T&& points, MultidimensionalVector<float, 3>& model)
	{
		for (std::size_t i = 2; i < points.size(); ++i)
		{
			model.push_back({ points[0].x, points[0].y, points[0].z });
			model.push_back({ points[i - 1].x, points[i - 1].y, points[i - 1].z });
			model.push_back({ points[i].x, points[i].y, points[i].z });
		}
	}
	/*std::vector<cv::Point3f> createOneEightSphere(bool positiveX = true, bool positiveY = true, bool positiveZ = true);*/
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


