#pragma once

#include "Component\Material.hpp"
#include "Component\Mesh.hpp"
#include "Component\Movement.hpp"
#include "Component\Light.hpp"
#include "Component\Camera.hpp"
#include "Component\Input.hpp"

void setup(){
	// Camera setup
	Entity* camera = EntityManager::instantiate();

	camera->getComponent<Transform>()->position(Vector3f(2.25f, 0.f, -4.5f));
	camera->addComponent(new Input);
	camera->addComponent(new Camera);
	camera->addComponent(new Light);

	// Spinning cats setup
	for (int i = 0; i != 5; i++){
		Entity* texture = EntityManager::instantiate();

		texture->getComponent<Transform>()->position(Vector3f(0.f, 0.f, -(float)i * 5));
		texture->addComponent(new Material("regressiontest.jpg"));
		texture->addComponent(new Mesh);
		texture->addComponent(new Movement);
	}

	EntityManager::loadAll();
}