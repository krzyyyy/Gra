#include "BasicShapesCreators.h"

void ModelCreators::addTrianglesFromConvexPlane(const std::vector<cv::Point3f>& points, MultidimensionalVector<float, 3>& model)
{
	for (std::size_t i = 2; i < points.size(); ++i)
	{
		model.push_back({ points[0].x, points[0].y, points[0].z });
		model.push_back({ points[i - 1].x, points[i - 1].y, points[i - 1].z });
		model.push_back({ points[i].x, points[i].y, points[i].z });
	}
}

float ModelCreators::getVectorElement(char dimention, cv::Point3f point)
{
	if (dimention == 'x')
		return point.x;
	else if(dimention == 'y')
		return point.y;
	else if(dimention == 'z')
		return point.z;
	return -1.;
}

