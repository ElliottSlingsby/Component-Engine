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

#include "Prefab\Player.hpp"

struct Testing : public State{
	const float boundrySize = 500.f;

	void on(){
		Entity* light = EntityManager::createEntity("light");
		light->addComponent(new Light);

		// Camera setup
		Entity* player = EntityManager::createEntity<Player>("player");

		// Sky sphere
		Entity* sky = EntityManager::createEntity("sky");

		sky->getComponent<Transform>()->setScale(Vector3f(boundrySize, boundrySize, boundrySize));
		sky->addComponent(new Sphere(boundrySize, true));
		sky->addComponent(new Model("relaxed_cube.obj", "grid.png"));

		// Evil face model
		Entity* won = EntityManager::createEntity("trophy");

		won->getComponent<Transform>()->setPosition(Vector3f(-10.f, -20.f, 0.f));
		won->getComponent<Transform>()->setRotation(Vector3f(0.f, 180.f, 0.f));
		won->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		won->addComponent(new Spinner(100.f));
		won->addComponent(new Model("lost.obj", "lost.png"));

		Entity* star = EntityManager::createEntity("trophy");

		star->getComponent<Transform>()->setPosition(Vector3f(-10.f, -50.f, 0.f));
		star->getComponent<Transform>()->setRotation(Vector3f(0.f, 180.f, 0.f));
		star->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		star->addComponent(new Spinner(-100.f));
		star->addComponent(new Model("face_happy.obj", "face.png"));
	}

	void off(){
		// Keep camera + sky
		EntityManager::destroyEntities("floor");
		EntityManager::destroyEntities("face");
		EntityManager::destroyEntities("ship");
	}
};