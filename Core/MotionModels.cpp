#include "MotionModels.h"

namespace MotionModels
{

	void RectilinearMotion::GetNextPosition(std::chrono::duration<double> duration, glm::mat4& globalPosition) const
	{

		globalPosition = glm::translate(globalPosition, _moveDirection * (float)duration.count());
	}

	glm::vec3 RectilinearMotion::GetNextDirection() const
	{
		return _moveDirection;
	}


};