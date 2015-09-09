#pragma once

#include <Entity\HelperComponent.hpp>

class Input : public HelperComponent{
	Transform* _transform = 0;

	float _speed = 20.f;
	float _sensitivity = 1.f;

public:
	Input(float speed, float sensitivity);

	void load();
	void update(double dt);

	// Movements
	void left(double dt);
	void right(double dt);
	void forward(double dt);
	void back(double dt);
	void up(double dt);
	void down(double dt);

	// Setters
	void setSpeed(float speed);
	void setSensitivity(float sensitivity);
};