#pragma once
#include <iostream>
#include <fstream>

#include "../glm/glm.hpp"


	std::ostream& operator <<(std::ostream& stream,const glm::vec3& vector)
	{
		stream << vector.x << "," << vector.y << "," << vector.y << std::endl;
		return stream;
	};