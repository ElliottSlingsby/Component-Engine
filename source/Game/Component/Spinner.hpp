#pragma once

#include "Entity\HelperComponent.hpp"

class Spinner : public HelperComponent{
	Transform* _transform;
	float _speed;

public:
	Spinner(float speed){
		_speed = speed;
	}

	void load(){
		_transform = getComponent<Transform>();
	}

	void update(float dt){
		_transform->rotate(Vector3f(0.f, _speed * dt, 0.f));
	}
};