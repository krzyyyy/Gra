#pragma once
#include <iostream>
#include "MultidimensionalVector.h"
#include "glm/glm.hpp"

namespace ModelCreators
{
	struct CylinderCreator
	{
        std::vector<cv::Point3f> computeMeshVertexes()
        {
            auto meshVertex = std::vector<cv::Point3f>();
            const double R = 0.5;
            for (float i = 0; i < 2; i = ++i)
            {
                for (float x = 0; x < 360; x += 30)
                {
                    meshVertex.push_back(cv::Point3f(R * sin(glm::radians(x)), R * cos(glm::radians(x)), i));
                }
            }
            return meshVertex;
        }
		MultidimensionalVector<float, 3> getShape()
		{
            auto vector = MultidimensionalVector<float, 3>();
            auto meshVerticles = computeMeshVertexes();
            for (int j = 0; j < meshVerticles.size(); j = j + meshVerticles.size()/2)
            {
                for (int i = 2; i < meshVerticles.size() / 2; ++i)
                {
                    vector.push_back({ meshVerticles[0 + j].x,meshVerticles[0 + j].y, meshVerticles[0 + j].z });
                    vector.push_back({ meshVerticles[i - 1 + j].x,meshVerticles[i - 1 + j].y, meshVerticles[i - 1 + j].z });
                    vector.push_back({ meshVerticles[i + j].x,meshVerticles[i + j].y, meshVerticles[i + j].z });
                }
            }
            std::size_t baseSize = meshVerticles.size() / 2;
            for (int i = 0; i < baseSize; ++i)
            {
               
                //first triangle on wall
                vector.push_back({ meshVerticles[i+ baseSize].x,meshVerticles[i+ baseSize].y, meshVerticles[i+ baseSize].z });
                vector.push_back({ meshVerticles[((i+1)% baseSize)+ baseSize].x,meshVerticles[((i + 1) % baseSize)+ baseSize].y, meshVerticles[((i + 1) % baseSize)+ baseSize].z });
                vector.push_back({ meshVerticles[((i + 1) % baseSize)].x,meshVerticles[((i + 1) % baseSize)].y, meshVerticles[((i + 1) % baseSize)].z });
                //second triangle on wall
                vector.push_back({ meshVerticles[i].x,meshVerticles[i].y, meshVerticles[i].z});
                vector.push_back({ meshVerticles[(i + 1) % baseSize].x,meshVerticles[(i + 1) % baseSize].y, meshVerticles[(i + 1) % baseSize].z });
                vector.push_back({ meshVerticles[i + baseSize].x,meshVerticles[i + baseSize].y, meshVerticles[i + baseSize].z });
            }
            return vector;
		};
        MultidimensionalVector<float, 3, 3, 2> modelShape;
	};
}