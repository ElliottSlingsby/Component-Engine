#pragma once

#include "Entity\Entity.hpp"
#include "Component\Collider\Collider.hpp"
#include "Component\Model\Model.hpp"
#include "Component\Health.hpp"

struct Enemy : public Entity{
	Enemy(Vector3f spawn = Vector3f(0.f, 0.f, 0.f)){
		_transform->setPosition(spawn);
		_transform->setRotation(Vector3f(0.f, 180.f, 0.f));
		_transform->setScale(Vector3f(0.1f, 0.1f, 0.1f));
	}

	void prefab(){
		addComponent(new Model("face_angry.obj", "face.png"));
		addComponent(new Sphere(6.f));
		addComponent(new Health(10.f));
	}
};