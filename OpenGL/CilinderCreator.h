#pragma once
#include <iostream>
#include "MultidimensionalVector.h"
#include "../glm/glm.hpp"
#include "BasicShapesCreators.h"

namespace ModelCreators
{
	struct CylinderCreator
	{
        const double radius = 0.5;
        const double H = 1;
        std::vector<cv::Point3f> computeMeshVertexes()
        {
            auto meshVertex = std::vector<cv::Point3f>();
            
            for (double i = -H/2; i <= H/2; i = i=i+H)
            {
                for (float x = 0; x < 360; x += 30)
                {
                    meshVertex.push_back(cv::Point3f(radius * sin(glm::radians(x)), radius * cos(glm::radians(x)), i));
                }
            }
            return meshVertex;
        }
		MultidimensionalVector<float, 3> getShape()
		{
            auto vector = MultidimensionalVector<float, 3>();
            auto meshVerticles = computeMeshVertexes();
            std::size_t sizeOfBase = meshVerticles.size() / 2;
            
            ModelCreators::addTrianglesFromConvexPlane(std::vector<cv::Point3f>(meshVerticles.cbegin(), meshVerticles.cbegin() + sizeOfBase),
                vector);
            ModelCreators::addTrianglesFromConvexPlane(std::vector<cv::Point3f>(meshVerticles.cbegin()+sizeOfBase, meshVerticles.cend()),
                vector);
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

	};
}