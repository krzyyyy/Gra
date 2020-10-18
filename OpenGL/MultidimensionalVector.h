#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <tuple>
#include <map>
#include <ranges>

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
	constexpr static std::size_t feature_count = sizeof...(FeatureSizes);
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

	void push_back(PointRepresentation&& elem);
	void emplace_back(PointRepresentation&& elem);
	void* data();
	int getArraySize();
	/* -------- ITERATORS --------*/
	template<int FeatureID>
	class Iterator;

	//openCV matrix function
	cv::Mat getAllPoints(std::size_t featureId);
	void transform(std::size_t featureId, const cv::Mat& transormMatrix);

	template<int FeatureId>
	Iterator< FeatureId> begin();
	//template<int FeatureId>
	//const iterator begin() const;
	//template<int FeatureId>
	//iterator end();
	//template<int FeatureId>
	//const iterator end() const;
	//template<int FeatureId>
	//const iterator cbegin() const;
	//template<int FeatureId>
	//const iterator cend() const;
	///*----------------------------*/

	///* -------- CAPACITY -------- */
	//bool empty() const;
	//// Returns size of allocated storate capacity
	//size_t capacity() const;
	//// Requests a change in capacity
	//// reserve() will never decrase the capacity.
	//void reserve(int newmalloc);
	//// Changes the Vector's size.
	//// If the newsize is smaller, the last elements will be lost.
	//// Has a default value param for custom values when resizing.
	//void resize(int newsize, T val = T());
	//// Returns the size of the Vector (number of elements). 
	//size_t size() const;
	//// Returns the maximum number of elements the Vector can hold
	//size_t max_size() const;
	//// Reduces capcity to fit the size
	//void shrink_to_fit();
	///*----------------------------*/

	///* ----- ELEMENT ACCESS ----- */
	//// Access elements with bounds checking
	//T& at(int n);
	//// Access elements with bounds checking for constant Vectors.
	//const T& at(int n) const;
	//// Access elements, no bounds checking
	//T& operator[](int i);
	//// Access elements, no bounds checking
	//const T& operator[](int i) const;
	//// Returns a reference to the first element
	//T& front();
	//// Returns a reference to the first element
	//const T& front() const;
	//// Returns a reference to the last element
	//T& back();
	//// Returns a reference to the last element
	//const T& back() const;
	//// Returns a pointer to the array used by Vector
	//T* data();
	//// Returns a pointer to the array used by Vector
	//const T* data() const;
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

template<typename T, std::size_t ...FeatureSizes>
inline void MultidimensionalVector<T, FeatureSizes...>::push_back(PointRepresentation&& elem)
{
	points.push_back(std::forward< PointRepresentation>(elem));
}

template<typename T, std::size_t ...FeatureSizes>
inline void MultidimensionalVector<T, FeatureSizes...>::emplace_back(PointRepresentation&& elem)
{
	points.emplace_back(std::forward<PointRepresentation>(elem));
}

template<typename T, std::size_t ...FeatureSizes>
inline void* MultidimensionalVector<T, FeatureSizes...>::data()
{
	return &points[0];
}

template<typename T, std::size_t ...FeatureSizes>
inline int MultidimensionalVector<T, FeatureSizes...>::getArraySize()
{

	return points.size()* stride_size*sizeof(T);
}

template<typename T, std::size_t ...FeatureSizes>
template<int FeatureID>
class MultidimensionalVector<T, FeatureSizes...>::Iterator
{
public:

	constexpr static std::size_t arraySize = MultidimensionalVector<T, FeatureSizes...>::feature_sizes[FeatureID];
	
	Iterator();
	Iterator(const std::array<T,
		MultidimensionalVector<T, FeatureSizes...>::feature_sizes[FeatureID]>& elem);
	std::array<T, MultidimensionalVector<T, FeatureSizes...>::feature_sizes[FeatureID]>& operator * ();
	Iterator& operator ++();
	Iterator& operator --();

	//Iterator operator ++(int);
	//Iterator operator --(int);
private:
	std::array<T, MultidimensionalVector<T, FeatureSizes...>::feature_sizes[FeatureID]>& featurePointer;
};


template<typename T, std::size_t ...FeatureSizes>
template<int FeatureID>
inline MultidimensionalVector<T, FeatureSizes...>::Iterator<FeatureID>::Iterator()
{
	featurePointer = nullptr;
}

template<typename T, std::size_t ...FeatureSizes>
template<int FeatureID>
inline MultidimensionalVector<T, FeatureSizes...>::Iterator<FeatureID>::
Iterator(const std::array<T, MultidimensionalVector<T,
	FeatureSizes...>::feature_sizes[FeatureID]>& elem):featurePointer(&elem)
{
	featurePointer = &elem;
}

template<typename T, std::size_t ...FeatureSizes>
template<int FeatureID>
inline std::array< T, 
	MultidimensionalVector<T, FeatureSizes...>::feature_sizes[FeatureID] >&
	MultidimensionalVector<T, FeatureSizes...>::Iterator<FeatureID>::operator*()
{
	return featurePointer;
}

template<typename T, std::size_t ...FeatureSizes>
template<int FeatureID>
inline MultidimensionalVector<T, FeatureSizes...>::Iterator< FeatureID>& MultidimensionalVector<T, FeatureSizes...>::Iterator<FeatureID>::operator++()
{
	featurePointer = &featurePointer[0] + MultidimensionalVector<T, FeatureSizes...>::stride_size;
	return *this;
}

template<typename T, std::size_t ...FeatureSizes>
template<int FeatureID>
inline MultidimensionalVector<T, FeatureSizes...>::Iterator< FeatureID>& MultidimensionalVector<T, FeatureSizes...>::Iterator<FeatureID>::operator--()
{
	featurePointer = &featurePointer[0] - MultidimensionalVector<T, FeatureSizes...>::stride_size;
	return *this;
}

//template<typename T, std::size_t ...FeatureSizes>
//template<int FeatureID>
//inline MultidimensionalVector<T, FeatureSizes...>::Iterator< FeatureID> MultidimensionalVector<T, FeatureSizes...>::Iterator<FeatureID>::operator++(int)
//{
//	auto copy = *this;
//	pointer = pointer + MultidimensionalVector<T, FeatureSizes...>::stride_size;
//	return copy;
//}

template<typename T, std::size_t ...FeatureSizes>
inline cv::Mat MultidimensionalVector<T, FeatureSizes...>::getAllPoints(std::size_t featureId)
{
	auto matrix = cv::Mat(points.size() , stride_size,CV_32FC1 , points.data());
	auto columnRange = cv::Range(ranges[featureId], ranges[featureId + 1]);
	auto rowRange = cv::Range(0, matrix.rows);
	return matrix(rowRange, columnRange);
}

template<typename T, std::size_t ...FeatureSizes>
inline void MultidimensionalVector<T, FeatureSizes...>::transform(std::size_t featureId, const cv::Mat& transormMatrix)
{
	auto allPoints = getAllPoints(featureId);
	cv::Mat result = allPoints * transormMatrix;
	if (result.size() != allPoints.size())
		throw std::exception("zla macierz przeksztalcen");
	result.copyTo(allPoints);
}


template<typename T, std::size_t ...FeatureSizes>
template<int FeatureId>
inline MultidimensionalVector<T, FeatureSizes ...>::Iterator<FeatureId> MultidimensionalVector<T, FeatureSizes ...>::begin()
{
	auto rrr = std::array<T,
		MultidimensionalVector<T, FeatureSizes...>::feature_sizes[FeatureId]>();
	return MultidimensionalVector<T, FeatureSizes...>::Iterator<FeatureId>(rrr);
}
