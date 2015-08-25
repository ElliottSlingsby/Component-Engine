#pragma once

#include "Entity\HelperComponent.hpp"
#include "Math\Vector3.hpp"

// Testing movement
class Movement : public HelperComponent{
	Transform* _transform = 0;

	float _speed;

public:

	Movement(float speed = 10){
		_speed = speed;
	}

	void load(){
		_transform = _getComponent<Transform>();
	}

	void update(float dt){
		//_transform->rotate(_speed * dt);
		_transform->push(_speed * dt);
	}
};
