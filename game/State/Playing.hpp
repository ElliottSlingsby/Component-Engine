#pragma once

#include "Static\EntityManager.hpp"
#include "Component\Light.hpp"

#include "Prefab\Player.hpp"
#include "Prefab\Enemy.hpp"
#include "Prefab\Sky.hpp"

struct Playing : public State{
	const float boundrySize = 500.f;

	void on(){
		Entity* sky = EntityManager::createEntity<Sky>("sky");

		Entity* light = EntityManager::createEntity();
		light->addComponent(new Light);

		Entity* player = EntityManager::createEntity<Player>("player", Vector3f(0.f, 0.f, -250.f));

		Entity* enemy = EntityManager::createEntity<Enemy>("enemy");
	}

	void off(){
		EntityManager::destroyEntities("player");
		EntityManager::destroyEntities("enemy");
	}
};