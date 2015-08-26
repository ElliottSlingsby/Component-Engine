#pragma once

#include "Entity\Entity.hpp"
#include "Component\Collider.hpp"
#include "Component\Model.hpp"
#include "Component\Health.hpp"

struct Enemy : public Entity{
	Enemy(Vector3f spawn = Vector3f(0.f, 0.f, 0.f)){
		_transform->setPosition(spawn);
		_transform->setRotation(Vector3f(0.f, 180.f, 0.f));
		_transform->setScale(Vector3f(0.5f, 0.5f, 0.5f));
	}

	void prefab(){
		addComponent(new Model("face_happy.obj", "face.png"));
		addComponent(new Sphere(50.f));
		addComponent(new Health(10.f));
	}
};