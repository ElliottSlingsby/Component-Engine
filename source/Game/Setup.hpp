#pragma once

#include "Component\Material.hpp"
#include "Component\Mesh.hpp"
#include "Component\Movement.hpp"
#include "Component\Light.hpp"
#include "Component\Camera.hpp"
#include "Component\Input.hpp"
#include "Component\Floor.hpp"
#include "Component\Sphere.hpp"

void setup(){
	// Camera setup (Camera needs to be setup first until projection matrix issue is fixed)
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
	}

	// Collision testing setup
	Entity* test1 = EntityManager::instantiate();
	test1->getComponent<Transform>()->position(Vector3f(0.f, 0.f, 0.f));
	test1->addComponent(new Sphere(10));

	Entity* test2 = EntityManager::instantiate();
	test2->getComponent<Transform>()->position(Vector3f(20.f, 0.f, 0.f));
	test2->addComponent(new Sphere(10));
	
	// Load all
	EntityManager::loadAll();

	// Hit detect test (Shouldn't really be here)
	if (test1->getComponent<Sphere>()->colliding(test2->getComponent<Sphere>()))
		printf("Colliding!");

	AssetLoader::getAsset("torus.obj");
}