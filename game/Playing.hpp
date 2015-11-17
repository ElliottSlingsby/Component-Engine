#pragma once

#include <Static\EntityManager.hpp>

struct Playing : public State{
	void on();
	void off();
};