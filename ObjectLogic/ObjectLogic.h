#pragma once
#include "IObjectLogic.h"

#ifdef OBJECT_LOGIC_EXPORT
#define EXPORT_OBJECT_LOGIC __declspec(dllexport)
#else
#define EXPORT_OBJECT_LOGIC __declspec(dllimport)
#endif // OBJECT_LOGIC_EXPORT


namespace Logic
{
	class EXPORT_OBJECT_LOGIC ObjectLogic : public IObjectLogic
	{
	public:
		ObjectLogic();
		ObjectLogic(double maxLive_, double currentLive_, double damage_);
		void TakeDamage(double value) override;
		double MaxLive()const override;
		double CurrentLive() const override;
		double Attack() const override;
		bool IsDead() const override;
	private:
		double maxLive;
		double currentLive;
		double damage;
	};
}


