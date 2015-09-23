#pragma once

#include <Entity\HelperComponent.hpp>

class Velocity : public HelperComponent{
	Transform* _transform = 0;

	glm::vec3 _velocity = glm::vec3(0, 0, 0);
	float _friction;

	float _tolerance;

public:
	Velocity(float friction, float tolerance = 0.001f);

	void load();
	void update(double dt);

	void localPush(const glm::vec3& push);
};