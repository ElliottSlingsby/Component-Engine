#pragma once

#include "Static\EntityManager.hpp"

#include "Component\Camera.hpp"
#include "Component\Model.hpp"
#include "Component\Spinner.hpp"
#include "Component\Light.hpp"

struct Won : public State{
	const float boundrySize = 500.f;

	void on(){
		Entity* camera = EntityManager::createEntity("camera");

		camera->getComponent<Transform>()->setPosition(Vector3f(0.f, -35.f, -70.f));
		camera->addComponent(new Light);
		camera->addComponent(new Camera);

		camera->invoke(&Component::load);

		// Evil face model
		Entity* won = EntityManager::createEntity("text");

		won->getComponent<Transform>()->setPosition(Vector3f(0.f, -20.f, 0.f));
		won->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		won->addComponent(new Spinner(100.f));
		won->addComponent(new Model("won.obj", "won.png"));

		won->invoke(&Component::load);

		Entity* star = EntityManager::createEntity("trophy");

		star->getComponent<Transform>()->setPosition(Vector3f(0.f, -50.f, 0.f));
		star->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		star->addComponent(new Spinner(-100.f));
		star->addComponent(new Model("star.obj", "star.png"));

		star->invoke(&Component::load);

		EntityManager::getEntity("sky")->addComponent(new Spinner(10.f));
		EntityManager::getEntity("sky")->getComponent<Spinner>()->load();
	}

	void off(){
		EntityManager::destroyAll();
	}
};