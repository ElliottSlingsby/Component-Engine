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

	bool _2d = false;
	float _zoom = 1.f;

public:
	Input(float speed, float sensitivity);

	void load();
	void lateLoad();
	void update(double dt);

	// Movements
	void forward();
	void back();

	void up(double dt);
	void down(double dt);
	void left(double dt);
	void right(double dt);

	// Setters
	void set2d(bool mode);
	void setSpeed(float speed);
	void setSensitivity(float sensitivity);
};