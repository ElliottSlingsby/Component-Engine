#pragma once

#include <Entity\HelperComponent.hpp>

#include "Movement.hpp"
#include "Feeder.hpp"
#include <fann.h>

class Brain : public HelperComponent{
	Transform* _transform = 0;
	Movement* _movement = 0;
	Feeder* _feeder = 0;

	float _nearestFood;
	float _eating;

public:
	void load();
	void update(double dt);
};