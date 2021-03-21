#pragma once
#include <iostream>
#include <variant>
#include <utility>
#include "ObjectLogic.h"
#include "Bullet.h"

namespace Logic
{
	using LiveTypes = std::variant<ObjectLogic, Bullet>;
}