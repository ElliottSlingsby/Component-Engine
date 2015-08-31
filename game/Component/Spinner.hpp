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

	void update(long double dt){
		_transform->rotate(Vector3f(0.f, (float)(_speed * dt), 0.f));

		const Uint8* keyDown = SDL_GetKeyboardState(0);
	}
};