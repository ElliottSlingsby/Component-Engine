#pragma once

#include "Static\EntityManager.hpp"

#include "Component\Light.hpp"
#include "Component\Camera.hpp"
#include "Component\Input.hpp"
#include "Component\Model\Model.hpp"
#include "Component\Model\Plane.hpp"

struct Testing : public State{
	void on(){
		// Camera setup
		Entity* camera = EntityManager::createEntity("player");

		camera->getComponent<Transform>()->setPosition(Vector3f(0.f, -10.f, -75.f));
		camera->addComponent(new Camera);
		camera->addComponent(new Input);
		camera->addComponent(new Light);

		// Sky sphere
		Entity* sky = EntityManager::createEntity("sky");

		sky->getComponent<Transform>()->setScale(Vector3f(10.f, 10.f, 10.f));
		sky->addComponent(new Model("inverse_sphere.obj", "sphere.png"));

		// Checkerboard testing floor
		Entity* floor = EntityManager::createEntity("floor");

		floor->getComponent<Transform>()->setPosition(Vector3f(0.f, -4.f, 0.f));
		floor->getComponent<Transform>()->setScale(Vector3f(50.f, 50.f, 50.f));
		floor->addComponent(new Plane("floor.jpg"));

		// Evil face model
		Entity* face = EntityManager::createEntity("face");

		face->getComponent<Transform>()->setPosition(Vector3f(-10.f, -20.f, 0.f));
		face->getComponent<Transform>()->setRotation(Vector3f(0.f, 180.f, 0.f));
		face->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		face->addComponent(new Model("face.obj", "face.png"));

		// Space ship model
		Entity* ship = EntityManager::createEntity("ship");

		ship->getComponent<Transform>()->setPosition(Vector3f(10.f, -20.f, 0.f));
		ship->getComponent<Transform>()->setRotation(Vector3f(0.f, 180.f, 0.f));
		ship->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		ship->addComponent(new Model("ship.obj", "ship.png"));
	}

	void off(){
		// Keep camera + sky
		EntityManager::deleteEntities("floor");
		EntityManager::deleteEntities("face");
		EntityManager::deleteEntities("ship");
	}
};