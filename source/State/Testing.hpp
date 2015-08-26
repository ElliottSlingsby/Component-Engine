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

struct Testing : public State{
	const float boundrySize = 500.f;

	void on(){
		Entity* light = EntityManager::createEntity("light");
		light->addComponent(new Light);

		// Camera setup
		Entity* camera = EntityManager::createEntity("player");

		camera->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		camera->getComponent<Transform>()->setPosition(Vector3f(0.f, -10.f, -75.f));
		camera->addComponent(new Input(200.f));
		camera->addComponent(new Physics(0.5f));
		camera->addComponent(new Model("ship.obj", "ship.png"));
		camera->addComponent(new Ship);

		// Sky sphere
		Entity* sky = EntityManager::createEntity("sky");

		sky->getComponent<Transform>()->setScale(Vector3f(boundrySize, boundrySize, boundrySize));
		sky->addComponent(new Sphere(boundrySize, true));
		sky->addComponent(new Model("relaxed_cube.obj", "grid.png"));

		/*
		// Checkerboard testing floor
		Entity* floor = EntityManager::createEntity("floor");

		floor->getComponent<Transform>()->setPosition(Vector3f(0.f, -4.f, 0.f));
		floor->getComponent<Transform>()->setScale(Vector3f(boundrySize, boundrySize, boundrySize));
		floor->addComponent(new Plane("floor.jpg"));
		*/

		// Evil face model
		Entity* face = EntityManager::createEntity("face");

		face->getComponent<Transform>()->setPosition(Vector3f(-10.f, -20.f, 0.f));
		face->getComponent<Transform>()->setRotation(Vector3f(0.f, 180.f, 0.f));
		face->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		face->addComponent(new Spinner(100.f));
		face->addComponent(new Model("won.obj", "won.png"));

		Entity* star = EntityManager::createEntity("face");

		star->getComponent<Transform>()->setPosition(Vector3f(-10.f, -50.f, 0.f));
		star->getComponent<Transform>()->setRotation(Vector3f(0.f, 180.f, 0.f));
		star->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		star->addComponent(new Spinner(-100.f));
		star->addComponent(new Model("star.obj", "star.png"));
	}

	void off(){
		// Keep camera + sky
		EntityManager::destroyEntities("floor");
		EntityManager::destroyEntities("face");
		EntityManager::destroyEntities("ship");
	}
};