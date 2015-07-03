#pragma once

#include <Base\HelperComponent.hpp>
#include <Component\Transform.hpp>
#include <SDL.h>

class Input : public HelperComponent{
	Transform* _transform = 0;
	float _speed = 0.1f;
	float _sensitivity = 0.2f;

public:
	void load(){
		_transform = _getComponent<Transform>();
	}

	void update(long dt){
		int mouseRX, mouseRY;

		SDL_GetRelativeMouseState(&mouseRX, &mouseRY);

		_transform->rotate(Vector3f((float)mouseRY * _sensitivity, (float)mouseRX * _sensitivity, 0.f));

		const Uint8* keyDown = SDL_GetKeyboardState(0);

		if (keyDown[SDL_SCANCODE_W])
			_transform->push(_speed);

		if (keyDown[SDL_SCANCODE_S])
			_transform->push(-_speed);
	}

	Component* clone(){
		return new Input;
	}
};