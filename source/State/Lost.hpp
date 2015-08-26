#pragma once

#include "Static\EntityManager.hpp"

#include "Component\Camera.hpp"
#include "Component\Model\Model.hpp"
#include "Component\Spinner.hpp"
#include "Component\Light.hpp"

struct Lost : public State{
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
		won->addComponent(new Model("lost.obj", "lost.png"));

		won->invoke(&Component::load);

		Entity* face = EntityManager::createEntity("trophy");

		face->getComponent<Transform>()->setPosition(Vector3f(0.f, -50.f, 0.f));
		face->getComponent<Transform>()->setRotation(Vector3f(0.f, 180.f, 0.f));
		face->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		face->addComponent(new Spinner(-100.f));
		face->addComponent(new Model("face_happy.obj", "face.png"));

		face->invoke(&Component::load);


		face = EntityManager::createEntity("trophy");

		face->getComponent<Transform>()->setPosition(Vector3f(0.f, -50.f, 0.f));
		face->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		face->addComponent(new Spinner(-100.f));
		face->addComponent(new Model("face_angry.obj", "face.png"));

		face->invoke(&Component::load);

		EntityManager::getEntity("sky")->addComponent(new Spinner(-10.f));
		EntityManager::getEntity("sky")->getComponent<Spinner>()->load();
	}

	void off(){
		EntityManager::destroyAll();
	}
};