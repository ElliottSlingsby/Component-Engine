#pragma once

#include "Base\HelperComponent.hpp"
#include "Math\Vector3.hpp"

// Testing movement
class Movement : public HelperComponent{
	Transform* _transform = 0;

	Vector3f _speed;

public:

	Movement(){
		_speed = Vector3f(
			(float)(rand() % 1000) / 10,
			(float)(rand() % 1000) / 10,
			(float)(rand() % 1000) / 10
		);
	}

	void load(){
		_transform = _getComponent<Transform>();
	}

	void update(float dt){
		_transform->rotate(_speed * dt);
	}

	Component* clone(){
		return new Movement;
	}
};
