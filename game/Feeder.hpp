#pragma once

#include <Entity\HelperComponent.hpp>

#include <Component\Circle2d.hpp>

class Feeder : public HelperComponent{
	Circle2d* _eating = 0;

	float _speed;

public:
	Feeder(float speed = 100.f);

	void update(double dt);
	void onCollision(int id);

	bool eating();
};