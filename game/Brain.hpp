#pragma once

#include <Entity\HelperComponent.hpp>

#include "Movement.hpp"
#include "Feeder.hpp"
#include "Vision.hpp"

#include <floatfann.h>
#include <fann_cpp.h>

class Brain : public HelperComponent{
	Transform* _transform = 0;
	Movement* _movement = 0;
	Feeder* _feeder = 0;
	Circle2d* _circle = 0;
	Vision* _vision = 0;

	float _nearestFood;
	float _eating;

	bool _perfect = true;

	FANN::neural_net _network;

public:
	Brain(bool perfect = true);
	~Brain();

	void load();
	void update(double dt);
};