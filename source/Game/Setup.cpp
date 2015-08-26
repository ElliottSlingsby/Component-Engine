#pragma once

#include "Setup.hpp"

#include "State\Playing.hpp"
#include "State\Lost.hpp"
#include "State\Won.hpp"

void setup(){
	EntityManager::addState(new Playing);
	EntityManager::addState(new Lost);
	EntityManager::addState(new Won);

	EntityManager::changeState<Playing>();
}