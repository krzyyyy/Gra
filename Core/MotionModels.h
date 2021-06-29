#pragma once
#include <chrono>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"


namespace MotionModels
{

	template<typename T>
	concept Moveable = requires(T t, std::chrono::duration<double> period, glm::mat4 matrix)
	{
		{t.GetNextPosition(period, matrix)}->std::convertible_to<void>;
	};
	class RectilinearMotion
	{
	public:
		RectilinearMotion() : _velocity(0) {};
		//RectilinearMotion(float velocity): _velo
		RectilinearMotion(float velocity, glm::vec3 moveDirection) : _velocity(velocity), _moveDirection(moveDirection) {};

		void GetNextPosition(std::chrono::duration<double> duration, glm::mat4& globalPosition) const;
		glm::vec3 GetNextDirection() const;
		template<typename Model>
		void BounceObject(const Model& model, glm::vec3 colisionPoint);


	private:
		/// @brief velocity value in m/s
		float _velocity;
		glm::vec3 _moveDirection;
	};


	template<typename Model>
	void RectilinearMotion::BounceObject(const Model& model, glm::vec3 colisionPoint)
	{
		_moveDirection = model.ComputeNewDirection(colisionPoint, _moveDirection);
	}/*
	class */
};

