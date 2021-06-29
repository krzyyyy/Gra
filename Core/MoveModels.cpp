#include "MoveModels.h"

namespace MoveModels
{

	void RectilinearMovement::GetNextPosition(std::chrono::duration<double> duration, glm::mat4& globalPosition) const
	{

		globalPosition = glm::translate(globalPosition, _moveDirection * (float)duration.count());
	}

	glm::vec3 RectilinearMovement::GetNextDirection() const
	{
		return _moveDirection;
	}


};