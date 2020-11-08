#pragma once
#include "Program.h"

class IRenderObject
{
public:
	virtual void Initialize() = 0;
	//virtual void Render(const Program& program) = 0;
	virtual ~IRenderObject() {};
};