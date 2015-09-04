#pragma once

#include "Entity\Entity.hpp"
#include "Component\Model.hpp"
#include "Component\Collider.hpp"

class Sky : public Entity{
	float _size;

public:
	Sky(float size = 500.f){
		_size = size;
		_transform->setScale(glm::vec3(_size, _size, _size));
	}

	void prefab(){
		addComponent(new Sphere(_size + 30.f, true));
		addComponent(new Model("relaxed_cube.obj", "grid.png"));
	}
};