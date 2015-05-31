#pragma once

#include "Entity.hpp"
#include "Component.hpp"

class EntityManager{
	EntityManager();

public:
	static EntityManager& instance();

	~EntityManager();
};