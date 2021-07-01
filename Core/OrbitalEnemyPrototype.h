#pragma once
#include "IEnemyPrototype.h"


class OrbitalEnemyPrototype: public IEnemyPrototype
{
public:
	OrbitalEnemyPrototype();
	OrbitalEnemyPrototype(float angularVelocity, float radius, glm::vec3 rotationAxis);

	// Inherited via IEnemyPrototype
	virtual std::shared_ptr<IObjectGenerator> Clone() const override;
private:
	float _angularVelocity;
	float _radius;
	glm::vec3 _rotationAxis;

};

