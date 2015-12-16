#pragma once

#include <Entity\HelperComponent.hpp>

class Spin : public HelperComponent{
	Transform* _transform = 0;

	float _speed;

public:
	Spin(float speed);

	void load();
	void update(double dt);
};