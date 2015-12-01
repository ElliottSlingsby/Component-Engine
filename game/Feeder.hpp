#pragma once

#include <Entity\HelperComponent.hpp>

#include <Component\Circle2d.hpp>

class Feeder : public HelperComponent{
	Transform* _transform = 0;

	Circle2d* _eating = 0;

	float _speed = 75.f;
	float _decay = 10.f;
	float _nutrition = 100.f;
	float _max = 200.f;

	float _capacity = 100.f;

public:
	void load();
	void update(double dt);
	void onCollision(int id);

	bool eating();
	float capacity();
	glm::vec3 nearestFood();
};