#pragma once
#include <iostream>
#include "MultidimensionalVector.h"
#include "glm/glm.hpp"

namespace ModelCreators
{
	struct CylinderCreator
	{
		MultidimensionalVector<float, 3, 3, 2>	getShape()
		{
            auto vector = MultidimensionalVector<float, 3, 3, 2>();
            auto meshPoints = std::vector<cv::Point3f>();
            const double R = 1;
            for (float i = 0; i < 2; i = ++i)
            {
                for (float x = 0; x < 360; x += 30)
                {
                    meshPoints.push_back(cv::Point3f(R * sin(glm::radians(x)), R * cos(glm::radians(x)), i));
                }
            }
            for (int j = 0; j < 24; j = j + 12)
            {

                for (int i = 2; i < 12; ++i)
                {
                    vector.push_back({ meshPoints[0 + j].x,meshPoints[0 + j].y, meshPoints[0 + j].z, 0.f, 1.f, 0.f, 0.5f, 0.0f });
                    vector.push_back({ meshPoints[i - 1 + j].x,meshPoints[i - 1 + j].y, meshPoints[i - 1 + j].z, 0.f, 1.f, 0.f, 0.0f, 0.5f });
                    vector.push_back({ meshPoints[i + j].x,meshPoints[i + j].y, meshPoints[i + j].z, 0.f, 1.f, 0.f, 0.0f, 1.0f });
                }
            }
            return vector;
		};
	};
}