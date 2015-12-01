#pragma once

#include <Entity\HelperComponent.hpp>

#include "Movement.hpp"

class Brain : public HelperComponent{
	Transform* _transform = 0;
	Movement* _movement = 0;

	int _mode = 0;
	bool _boost = false;

public:
	void load();
	void update(double dt);
};