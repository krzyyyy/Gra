#pragma once
namespace Logic
{
	class IObjectLogic
	{
	public:
		virtual void TakeDamage(double value) = 0;
		virtual double Attack() const = 0;
		virtual double MaxLive()const = 0;
		virtual double CurrentLive() const = 0;
		virtual bool IsDead() const = 0;
	};
}


