#pragma once

#include "Entity\Entity.hpp"
#include "Component\Model.hpp"
#include "Component\Input.hpp"
#include "Component\Physics.hpp"
#include "Component\Ship.hpp"

struct Player : public Entity{
	Player(Vector3f spawn = Vector3f(0.f, -10.f, -75.f)){
		_transform->setScale(Vector3f(0.1f, 0.1f, 0.1f));
		_transform->setPosition(spawn);
	}

	void prefab(){
		addComponent(new Input(200.f));
		addComponent(new Physics(0.5f));
		addComponent(new Model("ship.obj", "ship.png"));
		addComponent(new Ship);
		addComponent(new Sphere(1.f));
	}
};