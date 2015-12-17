#pragma once

#include <Entity\HelperComponent.hpp>

#include <Component\Input.hpp>

class Noclip : public HelperComponent{
	Transform* _transform = 0;
	Input* _input = 0;

	float _speed;
	float _sensitivity;

public:
	Noclip(float speed, float sensitivity);

	void load();
	void update(double dt);

	// Movements
	void left(double dt);
	void right(double dt);
	void forward(double dt);
	void back(double dt);
	void globalForward(double dt);
	void globalBack(double dt);
	void globalUp(double dt);
	void globalDown(double dt);

	// Setters
	void setSpeed(float speed);
	void setSensitivity(float sensitivity);
};