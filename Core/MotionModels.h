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
		RectilinearMotion();
		//RectilinearMotion(float velocity): _velo
		RectilinearMotion(float velocity, glm::vec3 moveDirection) ;
		RectilinearMotion(glm::vec3 beginTrajectory, glm::vec3 endTrajetory, float velocity) noexcept;

		void GetNextPosition(std::chrono::duration<double> duration, glm::mat4& globalPosition);
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
	}



	class OrbitalMotion
	{
	public:
		OrbitalMotion();
		OrbitalMotion(float angularVelocity, glm::vec3 center, float radius, glm::vec3 rotationAxis);
		OrbitalMotion(glm::vec3 beginTrajectory, glm::vec3 endTrajetory, float velocity);
		void GetNextPosition(std::chrono::duration<double> duration, glm::mat4& globalPosition);
		glm::vec3 GetNextDirection() const;
		template<typename Model>
		void BounceObject(const Model& model, glm::vec3 colisionPoint);

	private:
		float _angularVelocity;
		glm::vec3 _center;
		float _radius;
		glm::vec3 _rotationAxis;
		float _angle;
		glm::vec3 perpendicularToRotation;

	};
	template<typename Model>
	inline void OrbitalMotion::BounceObject(const Model& model, glm::vec3 colisionPoint)
	{
	}
};

