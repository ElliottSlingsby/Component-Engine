#pragma once

#include <Static\EntityManager.hpp>

class Playing : public State{
	int _spread = 5;
	int _width = 4096;
	int _height = 2048;

public:
	void on();
	void off();
};