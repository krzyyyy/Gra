#pragma once

#ifdef OBJECT_LOGIC_EXPORT
#define EXPORT_OBJECT_LOGIC __declspec(dllexport)
#else
#define EXPORT_OBJECT_LOGIC __declspec(dllimport)
#endif // OBJECT_LOGIC_EXPORT


namespace Logic
{
	struct EXPORT_OBJECT_LOGIC ObjectLogic
	{
		double maxLive;
		double currentLive;
		double damage;
	};
}


