#pragma once

#include <Entity\HelperComponent.hpp>
#include "Velocity.hpp"
#include "Input.hpp"

class Movement : public HelperComponent{
	Transform* _transform = 0;
	Velocity* _velocity = 0;
	Input* _input = 0;

	float _speed;
	bool _player;

public:
	Movement(float speed, bool player = false);

	void load();
	void update(double dt);

	// Movements
	void forward(float scalar = 1.f);
	void back(float scalar = 1.f);
	void turn(float scalar = 0.f);

	void left(float scalar = 1.f);
	void right(float scalar = 1.f);

	// Setters
	void setSpeed(float speed);
};