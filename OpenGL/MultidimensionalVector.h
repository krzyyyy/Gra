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

#ifndef MULTI_VECTOR
#define MULTI_VECTOR
 // !MULTI_VECTOR

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
	MultidimensionalVector(std::initializer_list< PointRepresentation> l) :points(l) {};
	MultidimensionalVector() = default;
	explicit MultidimensionalVector(int n);
	explicit MultidimensionalVector(int n, const PointRepresentation& inital);
	MultidimensionalVector(const MultidimensionalVector& obj) = default;
	MultidimensionalVector& operator = (const MultidimensionalVector & obj) = default;
	template<std::size_t... FeatureSizes2>
	MultidimensionalVector<T, FeatureSizes... , FeatureSizes2...> concatenate(MultidimensionalVector<T, FeatureSizes2...> multiVector);

	//inserting methods
	void push_back(PointRepresentation&& elem);
	void emplace_back(PointRepresentation&& elem);

	//access method
	void* data();
	int getArraySize();
	std::array<T, (FeatureSizes + ...)>& operator[](std::size_t idx);


	auto size()
	{
		return points.size();
	};
	/* -------- ITERATORS --------*/
	template<int FeatureID>
	class Iterator;

	//openCV matrix function
	cv::Mat getAllPoints(std::size_t featureId);
	void transform(std::size_t featureId, const cv::Mat& transormMatrix);
	
	template<int FeatureId>
	Iterator< FeatureId> begin();



	
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
inline std::array<T, (FeatureSizes + ...)>&
MultidimensionalVector<T, FeatureSizes...>::operator [] (std::size_t idx)
{
	return points[idx];
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
template<std::size_t ...FeatureSizes2>
inline MultidimensionalVector<T, FeatureSizes..., FeatureSizes2...>
MultidimensionalVector<T, FeatureSizes...>::concatenate(MultidimensionalVector<T, FeatureSizes2...> multiVector)
{
	if (size() != multiVector.size())
		throw std::exception("obj1.size() != obj2.size() !!! Different sizes of multivectors");
	auto result = MultidimensionalVector<T, FeatureSizes..., FeatureSizes2...>();
	for (int i = 0; i < size(); ++i)
	{
		auto multivectorElement = std::array<T, stride_size + multiVector.stride_size>();
		std::copy(points[i].cbegin(), points[i].cend(), multivectorElement.begin());
		std::copy(multiVector[i].cbegin(), multiVector[i].cend(), multivectorElement.begin()+stride_size);
		result.push_back(std::move(multivectorElement));
	}
	return result;
}


#endif