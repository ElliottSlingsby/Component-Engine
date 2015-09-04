#pragma once

#include "Static\EntityManager.hpp"
#include "Prefab\Player.hpp"
#include "Prefab\Sky.hpp"

struct Playing : public State{
	const float boundrySize = 500.f;

	void on(){
		EntityManager::createEntity<Sky>("sky");
		EntityManager::createEntity<Player>("player", glm::vec3(0.f, 0.f, -250.f));	}

	void off(){
		EntityManager::destroyEntities("player");
		EntityManager::destroyEntities("sky");
	}
};