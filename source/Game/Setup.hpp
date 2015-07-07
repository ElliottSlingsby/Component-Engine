#pragma once

#include "Component\Material.hpp"
#include "Component\Mesh.hpp"
#include "Component\Movement.hpp"
#include "Component\Light.hpp"
#include "Component\Camera.hpp"
#include "Component\Input.hpp"
#include "Component\Floor.hpp"
#include "Component\Cylinder.hpp"

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
	for (int i = 0; i != 500; i++){
		Entity* texture = EntityManager::instantiate();
		
		texture->getComponent<Transform>()->position(Vector3f((float)(rand() % 100) - 50.f, 0.f, (float)(rand() % 100) - 50.f));
		texture->addComponent(new Material("regressiontest.jpg"));
		texture->addComponent(new Mesh);
		texture->addComponent(new Movement);
		texture->addComponent(new Input); //just for fun
	}

	Entity* test1 = EntityManager::instantiate();
	test1->getComponent<Transform>()->position(Vector3f(0.f, 0.f, 0.f));
	test1->addComponent(new Cylinder(10));

	Entity* test2 = EntityManager::instantiate();
	test2->getComponent<Transform>()->position(Vector3f(21.f, 0.f, 0.f));
	test2->addComponent(new Cylinder(10));
	
	EntityManager::loadAll();

	if (test1->getComponent<Cylinder>()->colliding(test2->getComponent<Cylinder>()))
		printf("Colliding!");
}