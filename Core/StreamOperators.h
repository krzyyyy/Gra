#pragma once
#include <iostream>
#include <fstream>

#include "../glm/glm.hpp"


	std::ostream& operator <<(std::ostream& stream,const glm::vec3& vector)
	{
		stream << vector.x << "," << vector.y << "," << vector.z << std::endl;
		return stream;
	};
	std::ostream& operator << (std::ostream & stream, const glm::mat4 & matrix)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				stream << matrix[i][j] << " , ";
			}
			stream << std::endl;
		}
		
		return stream;
	};