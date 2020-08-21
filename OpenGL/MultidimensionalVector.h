#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <map>

#include "MultidimensionalConvertable.h"

//template<int...Args>
//constexpr int Sum() {
//	
//	return Args + Sum<...>();
//};
template<std::size_t size, const auto& arr>
constexpr std::array<std::size_t, size+1> sum()
{
	std::array<std::size_t, size + 1> result;
	result[0] = 0;
	for (std::size_t i = 1; i < size + 1; ++i)
		result[i] = result[i - 1] + arr[i - 1];
	return result;
}

template<typename T, std::size_t... FeatureSizes>
//requires (std::is_same_v<std::pair<const char *, std::size_t>, Args> && ...)
class MultidimensionalVector
{
public:
	// compile time value computation
	constexpr static std::size_t feature_count = sizeof...(FeatureSizes);;
	constexpr static std::size_t stride_size = (FeatureSizes +...);
	constexpr static std::array<std::size_t, feature_count> feature_sizes = {FeatureSizes...};
	constexpr static std::array<std::size_t, feature_count+1> ranges = sum<feature_count, feature_sizes>();
	
	using PointRepresentation = std::array<T, stride_size>;

	//Conctructors
	MultidimensionalVector() = default;
	explicit MultidimensionalVector(int n);
	explicit MultidimensionalVector(int n, const PointRepresentation& inital);
	MultidimensionalVector(const MultidimensionalVector& obj) = default;
	MultidimensionalVector& operator = (const MultidimensionalVector & obj) = default;

	/* -------- ITERATORS --------*/
	class iterator;
	iterator begin();
	const iterator begin() const;
	iterator end();
	const iterator end() const;
	const iterator cbegin() const;
	const iterator cend() const;
	/*----------------------------*/

	/* -------- CAPACITY -------- */
	bool empty() const;
	// Returns size of allocated storate capacity
	size_t capacity() const;
	// Requests a change in capacity
	// reserve() will never decrase the capacity.
	void reserve(int newmalloc);
	// Changes the Vector's size.
	// If the newsize is smaller, the last elements will be lost.
	// Has a default value param for custom values when resizing.
	void resize(int newsize, T val = T());
	// Returns the size of the Vector (number of elements). 
	size_t size() const;
	// Returns the maximum number of elements the Vector can hold
	size_t max_size() const;
	// Reduces capcity to fit the size
	void shrink_to_fit();
	/*----------------------------*/

	/* ----- ELEMENT ACCESS ----- */
	// Access elements with bounds checking
	T& at(int n);
	// Access elements with bounds checking for constant Vectors.
	const T& at(int n) const;
	// Access elements, no bounds checking
	T& operator[](int i);
	// Access elements, no bounds checking
	const T& operator[](int i) const;
	// Returns a reference to the first element
	T& front();
	// Returns a reference to the first element
	const T& front() const;
	// Returns a reference to the last element
	T& back();
	// Returns a reference to the last element
	const T& back() const;
	// Returns a pointer to the array used by Vector
	T* data();
	// Returns a pointer to the array used by Vector
	const T* data() const;
	/*----------------------------*/


	
private:
	std::vector<PointRepresentation> points;
};

template<typename T, std::size_t ...FeatureSizes>
inline MultidimensionalVector<T,  FeatureSizes ...>::MultidimensionalVector(int n)
{
	points = std::vector<PointRepresentation>(n);
}

template<typename T, std::size_t ...FeatureSizes>
inline MultidimensionalVector<T, FeatureSizes...>::MultidimensionalVector(int n, const PointRepresentation& inital)
{
	points = std::vector<PointRepresentation>(n, inital);
}

template<typename T, std::size_t... FeatureSizes>
class MultidimensionalVector< T, FeatureSizes...> Iterator
{

};
