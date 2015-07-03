#pragma once

#include <Base\HelperComponent.hpp>
#include <Component\Transform.hpp>
#include <SDL.h>

class Input : public HelperComponent{
	Transform* _transform = 0;
	float _speed = 20.f; // Movement speed
	float _sensitivity = 0.2f; // Mouse sensitivity

public:
	void load(){
		_transform = _getComponent<Transform>();
	}

	void update(float dt){
		int mouseRX, mouseRY;

		SDL_GetRelativeMouseState(&mouseRX, &mouseRY);

		// Rotate camera FPS style
		_transform->rotate(Vector3f((float)mouseRY * _sensitivity, (float)mouseRX * _sensitivity, 0.f));

		const Uint8* keyDown = SDL_GetKeyboardState(0);

		// W = forward
		if (keyDown[SDL_SCANCODE_W]){
			_transform->push(_speed * dt);

			// Shift = Speed boost
			if (keyDown[SDL_SCANCODE_LSHIFT])
				_transform->push(_speed * dt);
		}

		// S = back
		if (keyDown[SDL_SCANCODE_S]){
			_transform->push(-_speed * dt);

			if (keyDown[SDL_SCANCODE_LSHIFT])
				_transform->push(-_speed * dt);
		}		
	}

	Component* clone(){
		return new Input;
	}
};