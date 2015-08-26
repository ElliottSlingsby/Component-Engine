#pragma once

#include "Entity\Entity.hpp"
#include "Component\Collider\Collider.hpp"
#include "Component\Model\Model.hpp"
#include "Component\Movement.hpp"

struct Bullet : public Entity{
	Bullet(int id){
		Entity* shooter = EntityManager::getEntity(id);

		_transform->setPosition(shooter->getComponent<Transform>()->position());
		_transform->setRotation(shooter->getComponent<Transform>()->rotation());
		_transform->setScale(Vector3f(0.5f, 0.5f, 0.5f));

		_transform->push(-3.f, 90.f);
		_transform->push(10.f);
	}

	void prefab(){
		addComponent(new Movement(500.f));
		addComponent(new Model("sphere.obj"));
		addComponent(new Sphere(10.f));
	}
};