#pragma once
#include <queue>
#include <mutex>
#include <optional>

template<typename T>
class MultiThreadFIFO
{
public:
	MultiThreadFIFO() noexcept = default;
	MultiThreadFIFO(const MultiThreadFIFO& multiThreadFIFO) = delete;
	MultiThreadFIFO& operator=(const MultiThreadFIFO& multiThreadFIFO) = delete;
	MultiThreadFIFO(MultiThreadFIFO&& multiThreadFIFO) = default;
	MultiThreadFIFO& operator=(MultiThreadFIFO&& multiThreadFIFO) = default;

	std::optional<T> Pop();
	void Push(const T& item);

private:
	std::queue<T> queue;
	std::mutex mutex;

};

template<typename T>
inline std::optional<T> MultiThreadFIFO<T>::Pop()
{
	std::lock_guard lockGuard(mutex);
	if (queue.empty())
		return std::nullopt;
	T value = queue.front();
	queue.pop();
	return std::make_optional(value);
}

template<typename T>
inline void MultiThreadFIFO<T>::Push(const T& item)
{
	std::lock_guard lockGuard(mutex);
	queue.push(item);
}

