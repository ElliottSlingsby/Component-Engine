#pragma once

#include <Entity\HelperComponent.hpp>
#include <Component\Transform.hpp>
#include "Component\Model\Model.hpp"

class Ship : public HelperComponent{
	Transform* _transform = 0;
	Entity* _ship = 0;

public:
	void load(){
		_transform = getComponent<Transform>();
	}

	void lateLoad(){
		_ship = EntityManager::createEntity("ship");

		_ship->getComponent<Transform>()->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		_ship->addComponent(new Model("ship.obj", "ship.png"));
		_ship->getComponent<Transform>()->setPosition(_transform->position());
		_ship->getComponent<Transform>()->setRotation(_transform->rotation());
		_ship->getComponent<Transform>()->push(-3.f, 90.f);
		_ship->getComponent<Transform>()->push(10.f);

		_ship->invoke(&Component::load);
	}

	void lateUpdate(){
		_ship->getComponent<Transform>()->setPosition(_transform->position());
		_ship->getComponent<Transform>()->setRotation(_transform->rotation());
		_ship->getComponent<Transform>()->push(-3.f, 90.f);
		_ship->getComponent<Transform>()->push(10.f);
	}
};