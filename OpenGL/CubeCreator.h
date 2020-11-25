#pragma once
#include <iostream>
#include "MultidimensionalVector.h"

namespace ModelCreators
{
	struct CubeCreator
	{
		std::vector<cv::Point3f> computeMeshVertexes()
		{
			auto meshVertex = std::vector<cv::Point3f>();

			auto axisValue = std::array<float, 2>({ -0.5, 0.5 });
			for (auto xValue : axisValue)
			{
				for (auto yValue : axisValue)
				{
					for (auto zValue : axisValue)
					{
						meshVertex.push_back(cv::Point3f(xValue, yValue, zValue));
					}
				}
			}
			return meshVertex;
		};
		MultidimensionalVector<float, 3, 3, 2>	getShape()
		{
			auto meshVerticles = computeMeshVertexes();
		auto vector = MultidimensionalVector<float, 3, 3, 2>{ { -0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f, 0.0f, 0.0f },
	{ 0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f, 1.0f, 0.0f},
	 { 0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
	 {0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
	 {-0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
	 {-0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},

	 {-0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},
	 { 0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},
	 { 0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
	 { 0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
	 {-0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
	 {-0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},

	 {-0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},
	 {-0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
	 {-0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
	 {-0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
	 {-0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},
	 {-0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},

	 {0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},
	 { 0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
	 {0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
	 {0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
	 {0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},
	 {0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},

	 {-0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
	 {0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
	 {0.5f, -0.5f,  0.5f, 0.f, 1.f, 0.f, 1.0f, 0.0f},
	 { 0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},
	 {-0.5f, -0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},
	 {-0.5f, -0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},

	 {-0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f},
	 {0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  1.0f, 1.0f},
	 {0.5f,  0.5f,  0.5f, 0.f, 1.f, 0.f, 1.0f, 0.0f},
	 { 0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  1.0f, 0.0f},
	 {-0.5f,  0.5f,  0.5f,0.f, 1.f, 0.f,  0.0f, 0.0f},
	 {-0.5f,  0.5f, -0.5f,0.f, 1.f, 0.f,  0.0f, 1.0f}
			};
		return vector;
		};
	};

}
