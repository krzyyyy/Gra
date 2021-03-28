#pragma once
#include "Program.h"
#include "..\Core\IObject.h"


namespace Render
{
	void RenderObject(const std::shared_ptr<IObject>& object, Program& program);
}