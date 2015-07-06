#pragma once

#include "Component\Material.hpp"
#include "Component\Mesh.hpp"
#include "Component\Movement.hpp"
#include "Component\Light.hpp"
#include "Component\Camera.hpp"
#include "Component\Input.hpp"
#include "Component\Floor.hpp"

void setup(){
	// Camera setup
	Entity* camera = EntityManager::instantiate();

	camera->getComponent<Transform>()->position(Vector3f(0.f, -10.f, -75.f));
	camera->addComponent(new Input);
	camera->addComponent(new Camera);
	camera->addComponent(new Light);

	// Checkerboard testing floor
	Entity* floor = EntityManager::instantiate();

	floor->getComponent<Transform>()->position(Vector3f(0.f, -4.f, 0.f));
	floor->addComponent(new Material("floor.jpg"));
	floor->addComponent(new Floor);

	// Making a bunch of randomly positioned spinning cat cubes
	for (int i = 0; i != 1000; i++){
		Entity* texture = EntityManager::instantiate();
		
		texture->getComponent<Transform>()->position(Vector3f((float)(rand() % 100) - 50.f, 0.f, (float)(rand() % 100) - 50.f));
		texture->addComponent(new Material("regressiontest.jpg"));
		texture->addComponent(new Mesh);
		texture->addComponent(new Movement);
		texture->addComponent(new Input); //just for fun
	}

	EntityManager::loadAll();
}