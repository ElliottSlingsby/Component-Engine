#pragma once

#include "Entity\HelperComponent.hpp"
#include "Math\Vector3.hpp"

// Testing Bullet
class Movement : public HelperComponent{
	Transform* _transform = 0;

	float _speed;

public:

	Movement(float speed = 10){
		_speed = speed;
	}

	void load(){
		_transform = getComponent<Transform>();
	}

	void update(long double dt){
		_transform->push((float)(_speed * dt));
	}

	void onCollision(int id){
		if (EntityManager::getEntity("sky") == EntityManager::getEntity(id))
			parent()->destroy();
	}
};
