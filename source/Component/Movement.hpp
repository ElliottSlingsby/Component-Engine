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
			(float)(rand() % 20) / 10,
			(float)(rand() % 20) / 10,
			(float)(rand() % 20) / 10
		);
	}

	void load(){
		_transform = _getComponent<Transform>();
	}

	void update(long dt){
		_transform->rotate(_speed);
	}

	Component* clone(){
		return new Movement;
	}
};
