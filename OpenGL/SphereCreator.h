#pragma once
#include <iostream>
#include <numbers>
#include <vector>
#include "opencv2/opencv.hpp"
#include "MultidimensionalVector.h"

//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"

namespace ModelCreators
{
	struct SphereCreator
	{
		const float radius = 0.5;
        const int sectorCount  = 12;
        const int stackCount = 14;
        std::vector<cv::Point3f> computeMeshVertexes()
		{
            auto vertices = std::vector<cv::Point3f>();
            auto normals = std::vector<cv::Point3f>();
            auto textureCordinates = std::vector<cv::Point2f>();
            //std::vector<float>().swap(normals);
            //std::vector<float>().swap(texCoords);

            float x, y, z, xy;                              // vertex position
            float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
            float s, t;                                     // vertex texCoord

            float sectorStep = 2 * std::numbers::pi / sectorCount;
            float stackStep = std::numbers::pi / stackCount;
            double sectorAngle, stackAngle;

            for (int i = 0; i <= stackCount; ++i)
            {
                stackAngle = std::numbers::pi / 2 - double(i * stackStep);        // starting from pi/2 to -pi/2
                xy = radius * cosf(stackAngle);             // r * cos(u)
                z = radius * sinf(stackAngle);              // r * sin(u)

                // add (sectorCount+1) vertices per stack
                // the first and last vertices have same position and normal, but different tex coords
                for (int j = 0; j <= sectorCount; ++j)
                {
                    sectorAngle = j * sectorStep;           // starting from 0 to 2pi

                    // vertex position (x, y, z)
                    x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
                    y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
                    vertices.push_back(cv::Point3f(x, y, z));


                    // normalized vertex normal (nx, ny, nz)
                    nx = x * lengthInv;
                    ny = y * lengthInv;
                    nz = z * lengthInv;
                    normals.push_back(cv::Point3f(nx, ny, nz));

                    // vertex tex coord (s, t) range between [0, 1]
                    s = (float)j / sectorCount;
                    t = (float)i / stackCount;
                    textureCordinates.push_back(cv::Point2f(s, t));

                }
            }
            return vertices;
		}
        MultidimensionalVector<float, 3> getShape()
        {
            auto result = MultidimensionalVector<float, 3>();
            auto vertexes = computeMeshVertexes();
            for (int i = 0; i < stackCount; ++i)
            {
                int k1 = i * (sectorCount + 1);     // beginning of current stack
                int k2 = k1 + sectorCount + 1;      // beginning of next stack

                for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
                {
                    // 2 triangles per sector excluding first and last stacks
                    // k1 => k2 => k1+1
                    if (i != 0)
                    {
                        result.push_back({ vertexes[k1].x, vertexes[k1].y, vertexes[k1].z });
                        result.push_back({ vertexes[k2].x, vertexes[k2].y, vertexes[k2].z });
                        result.push_back({ vertexes[k1 + 1].x, vertexes[k1 + 1].y, vertexes[k1 + 1].z });
                        //indices.push_back(k1);
                        //indices.push_back(k2);
                        //indices.push_back(k1 + 1);
                    }

                    // k1+1 => k2 => k2+1
                    if (i != (stackCount - 1))
                    {
                        result.push_back({ vertexes[k1 + 1].x, vertexes[k1 + 1].y, vertexes[k1 + 1].z });
                        result.push_back({ vertexes[k2].x, vertexes[k2].y, vertexes[k2].z });
                        result.push_back({ vertexes[k2 + 1].x, vertexes[k2 + 1].y, vertexes[k2 + 1].z });
                        //indices.push_back(k1 + 1);
                        //indices.push_back(k2);
                        //indices.push_back(k2 + 1);
                    }

                }
            }
            return result;
        }
	};

}