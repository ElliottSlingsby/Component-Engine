#pragma once

#include "Entity\Entity.hpp"
#include "Component\Model\Model.hpp"
#include "Component\Collider\Collider.hpp"

class Sky : public Entity{
	float _size;

public:
	Sky(float size = 500.f){
		_size = size;
		_transform->setScale(Vector3f(_size, _size, _size));
	}

	void prefab(){
		addComponent(new Sphere(_size, true));
		addComponent(new Model("relaxed_cube.obj", "grid.png"));
	}
};