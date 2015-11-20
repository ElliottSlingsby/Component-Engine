#pragma once

#include <Entity\HelperComponent.hpp>

#include "Velocity.hpp"
#include "Follow.hpp"

class Movement : public HelperComponent{
	Transform* _transform = 0;
	Velocity* _velocity = 0;
	Follow* _follow = 0;

	float _speed;
	float _sensitivity;

	bool _2d = true;
	float _zoom = 1.f;

public:
	Movement(float speed, float sensitivity);

	void load();
	void lateLoad();
	void update(double dt);

	// Movements
	void forward();
	void back();

	void up();
	void down();
	void left();
	void right();

	// Setters
	void set2d(bool mode);
	void setSpeed(float speed);
	void setSensitivity(float sensitivity);
};