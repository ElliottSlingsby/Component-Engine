#pragma once

#include "Static\EntityManager.hpp"

#include "Component\Camera.hpp"
#include "Component\Light.hpp"

#include "Prefab\Trophy.hpp"

struct Won : public State{
	const float boundrySize = 500.f;

	void on(){
		Entity* camera = EntityManager::createEntity();

		camera->getComponent<Transform>()->setPosition(Vector3f(0.f, -35.f, -70.f));
		camera->addComponent(new Light);
		camera->addComponent(new Camera);

		camera->invoke(&Component::load);

		Entity* won = EntityManager::createEntity<Trophy>("", Vector3f(0.f, -20.f, 0.f), "won.obj", "won.png", 100.f);

		won->invoke(&Component::load);

		Entity* star = EntityManager::createEntity<Trophy>("", Vector3f(0.f, -50.f, 0.f), "star.obj", "star.png", -50.f);

		star->invoke(&Component::load);

		EntityManager::getEntity("sky")->addComponent(new Spinner(10.f));
		EntityManager::getEntity("sky")->getComponent<Spinner>()->load();
	}

	void off(){
		EntityManager::destroyAll();
	}
};