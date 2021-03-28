#pragma once
#include "LiveTypes.h"

namespace Logic
{
	class ILiveObject
	{
	public:
		virtual LiveTypes GetLiveParameters() const = 0;
		virtual void SetLiveParameters(LiveTypes newLiveParameters) = 0;
		virtual ~ILiveObject() {};
	};

}