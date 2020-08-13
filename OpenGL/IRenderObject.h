#pragma once
#include "Program.h"

class IRenderObject
{
public:
	virtual void Initialize(float movement) = 0;
	virtual void Render(const Program& program) = 0;
	virtual ~IRenderObject() {};
};