#pragma once
#include <iostream>
#include "BasicShapesCreators.h"
#include "ParametricModels.h"

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
		MultidimensionalVector<float, 3> getShape()
		{
			const std::vector<cv::Point3f> meshVerticles = computeMeshVertexes();
			auto modelTriangeVector = MultidimensionalVector<float, 3>();
			auto dimentions = std::set{ 'x', 'y', 'z' };
			for (auto dimention: dimentions)
			{
				for (auto isPositive : { true, false })
				{
					auto planarVerticles = std::vector<cv::Point3f>();
					std::copy_if(meshVerticles.cbegin(), meshVerticles.cend(),std::back_inserter( planarVerticles), [dimention, isPositive](auto pt)
						{
							return (getVectorElement(dimention, pt) > 0.) == isPositive;
					});
					for (int i = 0; i < planarVerticles.size() - 1; ++i)
					{
						auto distance = cv::norm(planarVerticles[i] - planarVerticles[i + 1]);
						if (distance>1.)
						{
							if (i == 0 || i == planarVerticles.size()-2)
							{
								std::swap(planarVerticles[0], planarVerticles[planarVerticles.size() - 1]);
							}
							else
							{
								std::swap(planarVerticles[i + 1], planarVerticles[i + 2]);
							}
						}
					}
					addTrianglesFromConvexPlane(planarVerticles, modelTriangeVector);
				}

			}
		return modelTriangeVector;
		};
		static ParametricCilinder ComputeParametricModel(const glm::mat4& objectPosition, const glm::vec3& scale)
		{
			return ParametricCilinder{
				.Center = glm::vec3(objectPosition[3].x, objectPosition[3].y, objectPosition[3].z),
				.R = scale.x,
			};
		};
	};

}
