#pragma once

#include <Entity\HelperComponent.hpp>

#include "Velocity.hpp"
#include "Input.hpp"


class Movement : public HelperComponent{
	Transform* _transform = 0;
	Velocity* _velocity = 0;

	float _speed;
	bool _player;

public:
	Movement(float speed, bool player = false);

	void load();
	void update(double dt);

	// Movements
	void forward();
	void back();

	void left();
	void right();

	// Setters
	void setSpeed(float speed);
};