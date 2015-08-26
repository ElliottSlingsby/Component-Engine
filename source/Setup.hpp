#pragma once

#include "System\Collision.hpp"

#include "State\Playing.hpp"
#include "State\Lost.hpp"
#include "State\Won.hpp"

void setup(){
	EntityManager::addSystem(new Collision);

	EntityManager::addState(new Playing);
	EntityManager::addState(new Lost);
	EntityManager::addState(new Won);

	EntityManager::changeState<Playing>();
}