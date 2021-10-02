#include "MotionModels.h"
#include "..\SharedUtilities\MathHelperFunctions.h"

namespace MotionModels
{
	RectilinearMotion::RectilinearMotion() : _velocity(0)
	{}
	RectilinearMotion::RectilinearMotion(float velocity, glm::vec3 moveDirection) : _velocity(velocity), _moveDirection(moveDirection) 
	{}
	RectilinearMotion::RectilinearMotion(glm::vec3 beginTrajectory, glm::vec3 endTrajetory, float velocity) noexcept:
		_velocity(velocity),
		_moveDirection(endTrajetory - beginTrajectory)
	{
		_moveDirection = _moveDirection / (glm::length(_moveDirection));
	}
	void RectilinearMotion::GetNextPosition(std::chrono::duration<double> duration, glm::mat4& globalPosition)
	{

		globalPosition = glm::translate(globalPosition, _moveDirection * _velocity*(float)duration.count());
	}

	glm::vec3 RectilinearMotion::GetNextDirection() const
	{
		return _moveDirection;
	}


	OrbitalMotion::OrbitalMotion():_angularVelocity(0), _center(0. , 0., 0.), _radius(0.), _rotationAxis(0., 0., 1.), _angle(0.)
	{
		perpendicularToRotation = glm::vec3(1., 0., 0.);
	}

	OrbitalMotion::OrbitalMotion(float angularVelocity, glm::vec3 center, float radius, glm::vec3 rotationAxis) :
		_angularVelocity(angularVelocity),
		_center(center),
		_radius(radius),
		_rotationAxis(rotationAxis),
		_angle(0.)
	{
		_rotationAxis = glm::normalize(_rotationAxis);
		perpendicularToRotation = glm::cross(rotationAxis, glm::vec3(1., 0., 0.));
		if(glm::length(perpendicularToRotation) < 0.1)
			perpendicularToRotation = glm::cross(rotationAxis, glm::vec3(0., 1., 0.));
		perpendicularToRotation = glm::normalize(perpendicularToRotation) * radius;
	}

	OrbitalMotion::OrbitalMotion(glm::vec3 beginTrajectory, glm::vec3 endTrajetory, float velocity)
	{
	}

	void OrbitalMotion::GetNextPosition(std::chrono::duration<double> duration, glm::mat4& globalPosition)
	{
		_angle += _angularVelocity * (float)duration.count();
		auto objectPosition = glm::mat4(1);
		objectPosition = glm::translate(objectPosition, perpendicularToRotation);
		auto rotation = glm::rotate(glm::mat4(1), _angle, _rotationAxis);
		objectPosition =  rotation* objectPosition;
		objectPosition = glm::translate(objectPosition, _center);
		globalPosition = objectPosition;
	}

	glm::vec3 OrbitalMotion::GetNextDirection() const
	{
		return glm::vec3();
	}

};