#pragma once

#include <Static\EntityManager.hpp>

struct Playing : public State{
	const float boundrySize = 500.f;

	void on();
	void off();
};