#pragma once

#include "Static\EntityManager.hpp"

#include "Component\Light.hpp"
#include "Component\Camera.hpp"
#include "Component\Input.hpp"
#include "Component\Model\Model.hpp"
#include "Component\Model\Plane.hpp"
#include "Component\Ship.hpp"
#include "Component\Physics.hpp"
#include "Component\Spinner.hpp"
#include "Component\Health.hpp"

#include "Prefab\Player.hpp"
#include "Prefab\Enemy.hpp"

struct Playing : public State{
	const float boundrySize = 500.f;

	void on(){
		Entity* light = EntityManager::createEntity("light");
		light->addComponent(new Light);

		// Camera setup
		Entity* player = EntityManager::createEntity<Player>("player", Vector3f(0.f, 0.f, -250.f));

		// Sky sphere
		Entity* sky = EntityManager::createEntity("sky");

		sky->getComponent<Transform>()->setScale(Vector3f(boundrySize, boundrySize, boundrySize));
		sky->addComponent(new Sphere(boundrySize, true));
		sky->addComponent(new Model("relaxed_cube.obj", "grid.png"));


		Entity* face = EntityManager::createEntity<Enemy>("face");
	}

	void off(){
		EntityManager::destroyEntities("player");
		EntityManager::destroyEntities("face");
	}
};