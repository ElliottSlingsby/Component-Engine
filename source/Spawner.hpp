#pragma once

#include "Entity.hpp"
#include "Component.hpp"

class Spawner{
	Spawner();

public:
	static Spawner& instance();

	~Spawner();
};