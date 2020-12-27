#pragma once
#include <iostream>
#include "opencv2/opencv.hpp"
#include "MultidimensionalVector.h"


class IModelCreator
{
	virtual std::vector<cv::Point3f> computeMeshVertexes() = 0;
	virtual MultidimensionalVector<float, 3> getShape() = 0;
};