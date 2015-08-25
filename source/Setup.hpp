#pragma once

#include "State\Testing.hpp"

void setup(){
	EntityManager::addState(new Testing);
	EntityManager::changeState<Testing>();
}