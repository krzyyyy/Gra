#pragma once
#include <iostream>
#include <functional>
#include <chrono>


class Timer
{
public:
	Timer():interval(0), lastTime(std::chrono::steady_clock::now())
	{
	};
	Timer(std::chrono::duration<double> interval_) :interval(interval_), lastTime(std::chrono::steady_clock::now())
	{};
	void setInterval(std::chrono::duration<double> interval_)
	{
		interval = interval_;
	};
	template<typename Callback, typename... Args>
	std::chrono::duration<double> RunEvent(Callback&& callbackMethod, Args&&...args)
	{
		auto currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsedTime = currentTime - lastTime;
		std::chrono::duration<double> executionTime = std::chrono::duration<double>(0);
		if (elapsedTime >= interval)
		{
			std::invoke(std::forward< Callback>(callbackMethod), std::forward< Args>(args)...);
			auto afterExecutedTime = std::chrono::steady_clock::now();
			executionTime = currentTime - afterExecutedTime;
			lastTime = currentTime;
		}
		return executionTime;
	}

private:
	std::chrono::steady_clock::time_point lastTime;
	std::chrono::duration<double> interval;
};

