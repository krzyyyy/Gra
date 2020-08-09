#pragma once
template<typename Derived>
class ObjectCounter
{
public:
	ObjectCounter()
	{
		++objectCreated;
		++objectAlive;
	}
	ObjectCounter(const ObjectCounter& object)
	{
		++objectCreated;
		++objectAlive;
	}
	static int getQuantityCreated()
	{
		return objectCreated;
	}
	static int getQuantityAlived()
	{
		return objectAlive;
	}
protected:
	~ObjectCounter()
	{
		--objectAlive;
	}
private:
	static int objectCreated;
	static int objectAlive;
};
template<typename Derived> int ObjectCounter<Derived>::objectCreated(0);
template<typename Derived> int ObjectCounter<Derived>::objectAlive(0);

