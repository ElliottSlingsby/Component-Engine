#pragma once

#include <Entity\HelperComponent.hpp>

#include <Component\Circle2d.hpp>

class Feeder : public HelperComponent{
	Circle2d* _eating = 0;

	float _speed = 75.f;
	float _decay = 10.f;
	float _nutrition = 100.f;
	float _max = 200.f;

	float _capacity = 100.f;

public:
	void update(double dt);
	void onCollision(int id);

	bool eating();
	float capacity();
};