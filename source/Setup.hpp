#pragma once

#include "State\Testing.hpp"
#include "System\Collision.hpp"

void setup(){
	EntityManager::addSystem(new Collision);

	EntityManager::addState(new Testing);
	EntityManager::changeState<Testing>();
}