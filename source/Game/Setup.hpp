#pragma once

#include "Component\Material.hpp"
#include "Component\Mesh.hpp"
#include "Component\Movement.hpp"
#include "Component\Light.hpp"
#include "Component\Camera.hpp"
#include "Component\Input.hpp"
#include "Component\Floor.hpp"
#include "Component\Sphere.hpp"
#include "Component\Box.hpp"

void setup(){
	// Camera setup (Camera needs to be setup first until projection matrix issue is fixed)
	Entity* camera = EntityManager::createEntity();

	camera->getComponent<Transform>()->setPosition(Vector3f(0.f, -10.f, -75.f));
	camera->addComponent(new Input);
	camera->addComponent(new Light);
	camera->addComponent(new Camera);

	// Checkerboard testing floor
	Entity* floor = EntityManager::createEntity();

	floor->getComponent<Transform>()->setPosition(Vector3f(0.f, -4.f, 0.f));
	floor->addComponent(new Material("floor.jpg"));
	floor->addComponent(new Floor);

	// Making a bunch of randomly positioned spinning cat cubes
	for (int i = 0; i != 1000; i++){
		Entity* texture = EntityManager::createEntity();
		
		texture->getComponent<Transform>()->setPosition(Vector3f((float)(rand() % 100) - 50.f, 0.f, (float)(rand() % 100) - 50.f));
		texture->addComponent(new Material("regressiontest.jpg"));
		texture->addComponent(new Mesh);
		texture->addComponent(new Movement);
	}

	// Collision testing setup
	Entity* sphere1 = EntityManager::createEntity();
	sphere1->getComponent<Transform>()->setPosition(Vector3f(0.f, 0.f, 0.f));
	sphere1->addComponent(new Sphere(10));

	Entity* sphere2 = EntityManager::createEntity();
	sphere2->getComponent<Transform>()->setPosition(Vector3f(20.f, 0.f, 0.f));
	sphere2->addComponent(new Sphere(10));

	Entity* box1 = EntityManager::createEntity();
	box1->getComponent<Transform>()->setPosition(Vector3f(0.f, 0.f, 0.f));
	box1->addComponent(new Box(Vector3f(10.f, 10.f, 10.f)));

	Entity* box2 = EntityManager::createEntity();
	box2->getComponent<Transform>()->setPosition(Vector3f(0.f, 0.f, 0.f));
	box2->addComponent(new Box(Vector3f(10.f, 10.f, 10.f)));
	
	// Load all
	EntityManager::loadAll();

	// Hit detect test (Shouldn't really be here)
	if (sphere1->getComponent<Sphere>()->isColliding(sphere2->getComponent<Sphere>()))
		printf("Sphere colliding!\n");

	if (box1->getComponent<Box>()->isColliding(box2->getComponent<Box>()))
		printf("Box colliding!\n");

	// Obj load test (Shouldn't be here)
	//AssetLoader::getAsset("torus.obj");


	//MeshData* test = new MeshData(0, 12, 21, 10564);

	//const MeshData* test = AssetLoader::getNewAsset<MeshData>("torus.obj");

	printf("h");
}