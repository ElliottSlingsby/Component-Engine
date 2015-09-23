#pragma once

#include <Entity\HelperComponent.hpp>

#include "Velocity.hpp"

class Input : public HelperComponent{
	Transform* _transform = 0;
	Velocity* _velocity = 0;

	float _speed;
	float _sensitivity;

public:
	Input(float speed, float sensitivity);

	void load();
	void update(double dt);

	// Movements
	void forward(double dt);
	void back(double dt);

	// Setters
	void setSpeed(float speed);
	void setSensitivity(float sensitivity);
};