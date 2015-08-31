#pragma once

#include "Static\EntityManager.hpp"

#include "Component\Camera.hpp"
#include "Component\Light.hpp"

#include "Prefab\Trophy.hpp"

struct Lost : public State{
	const float boundrySize = 500.f;

	void on(){
		Entity* camera = EntityManager::createEntity();

		camera->getComponent<Transform>()->setPosition(Vector3f(0.f, -35.f, -70.f));
		camera->addComponent(new Light);
		camera->addComponent(new Camera);

		camera->invoke(&Component::load);

		Entity* won = EntityManager::createEntity<Trophy>("", Vector3f(0.f, -20.f, 0.f), "lost.obj", "lost.png", 100.f);

		won->invoke(&Component::load);
				
		Entity* face = EntityManager::createEntity<Trophy>("", Vector3f(0.f, -50.f, 0.f), "face_happy.obj", "face.png", -50.f);
		face->getComponent<Transform>()->setRotation(Vector3f(0.f, 180.f, 0.f));

		face->invoke(&Component::load);

		face = EntityManager::createEntity<Trophy>("", Vector3f(0.f, -50.f, 0.f), "face_angry.obj", "face.png", -50.f);

		face->invoke(&Component::load);

		EntityManager::getEntity("sky")->addComponent(new Spinner(-10.f));
		EntityManager::getEntity("sky")->getComponent<Spinner>()->load();
	}

	void off(){
		EntityManager::destroyAll();
	}
};