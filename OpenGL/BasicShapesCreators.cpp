#include "BasicShapesCreators.h"



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

