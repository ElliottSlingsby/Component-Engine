#pragma once

#include <Entity\HelperComponent.hpp>

#include "Movement.hpp"

class Brain : public HelperComponent{
	Movement* _movement = 0;

	int _mode = 0;

public:
	void load();
	void update(double dt);
};