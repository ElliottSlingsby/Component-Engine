#pragma once

#include "Component\Light.hpp"
#include "Component\Camera.hpp"
#include "Component\Input.hpp"
#include "Component\Model\Model.hpp"
#include "Component\Model\Plane.hpp"
#include "Component\Model\Cube.hpp"
#include "Component\Collider\Sphere.hpp"
#include "Component\Collider\Box.hpp"
#include "Component\Movement.hpp"

// The setup function will be replaced with a gamestate thing eventually.
void setup(){
	// Camera setup
	Entity* camera = EntityManager::createEntity();

	camera->getComponent<Transform>()->setPosition(Vector3f(0.f, -10.f, -75.f));
	camera->addComponent(new Camera);
	camera->addComponent(new Input);
	camera->addComponent(new Light);

	// Checkerboard testing floor
	Entity* floor = EntityManager::createEntity();

	floor->getComponent<Transform>()->setPosition(Vector3f(0.f, -4.f, 0.f));
	floor->getComponent<Transform>()->setScale(Vector3f(50.f, 50.f, 50.f));
	floor->addComponent(new Plane("floor.jpg"));

	
	for (int i = 0; i != 1000; i++){
		Entity* stub = EntityManager::createEntity("stubs");
		
		stub->getComponent<Transform>()->setPosition(Vector3f((float)(rand() % 100) - 50.f, 0.f, (float)(rand() % 100) - 50.f));
		stub->getComponent<Transform>()->setScale(Vector3f(0.01f, 0.01f, 0.01f));
		stub->addComponent(new Model("ship.obj", "ship.png"));
		stub->addComponent(new Movement);
	}
	
	Entity* face = EntityManager::createEntity("face");

	face->getComponent<Transform>()->setPosition(Vector3f(0.f, -50.f, 0.f));
	face->getComponent<Transform>()->setRotation(Vector3f(25.f, 180.f, 0.f));
	face->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
	face->addComponent(new Model("face.obj", "face.png"));

	Entity* ship = EntityManager::createEntity("ship");

	ship->getComponent<Transform>()->setPosition(Vector3f(10.f, -10.f, 0.f));
	ship->getComponent<Transform>()->setRotation(Vector3f(0.f, 180.f, 0.f));
	ship->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
	ship->addComponent(new Model("ship.obj", "ship.png"));

	// Load all
	EntityManager::loadAll();
}