#include "Component.hpp"

#include <Static\EntityManager.hpp>

Component::Component(){
	EntityManager::systemHandler().registerToSystem(this);
}

Component::~Component(){
	EntityManager::systemHandler().unregisterFromSystem(this);
}