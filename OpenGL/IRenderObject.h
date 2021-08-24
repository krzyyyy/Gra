#pragma once
#include <iostream>
#include "Program.h"

class IRenderObject
{
public:
	virtual void Initialize() = 0;
	virtual void Load(Program& program) = 0;
	virtual ~IRenderObject() {};
};