#pragma once

#include <Entity\HelperComponent.hpp>

class Velocity : public HelperComponent{
	Transform* _transform = 0;

	glm::vec3 _push;
	glm::quat _torque;
	
	glm::quat _rotation;
	glm::vec3 _velocity;

	float _friction;

	float _tolerance;

public:
	Velocity(float friction, float tolerance = 0.001f);

	void load();
	void update(double dt);

	void localPush(const glm::vec3& push);
	void localTorque(const glm::quat& torque);
};