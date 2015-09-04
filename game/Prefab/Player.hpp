#pragma once

#include "Entity\Entity.hpp"
#include "Component\Model.hpp"
#include "Component\Input.hpp"
#include "Component\Camera.hpp"

struct Player : public Entity{
	Player(glm::vec3 spawn = glm::vec3(0.f, -10.f, -75.f)){
		_transform->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
		_transform->setPosition(spawn);
	}

	void prefab(){
		addComponent(new Input(100.f, 0.2f));
		//addComponent(new Model("ship.obj", "ship.png"));
		addComponent(new Sphere(1.f));
		addComponent(new Camera);
	}
};