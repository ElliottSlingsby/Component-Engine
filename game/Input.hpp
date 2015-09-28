#pragma once

#include <Entity\HelperComponent.hpp>

#include "Velocity.hpp"
#include "Follow.hpp"

class Input : public HelperComponent{
	Transform* _transform = 0;
	Velocity* _velocity = 0;
	Follow* _follow = 0;

	float _speed;
	float _sensitivity;

public:
	Input(float speed, float sensitivity);

	void load();
	void lateLoad();
	void update(double dt);

	// Movements
	void forward();
	void back();

	// Setters
	void setSpeed(float speed);
	void setSensitivity(float sensitivity);
};