#pragma once

#include <Base\HelperComponent.hpp>
#include <Component\Transform.hpp>
#include <SDL.h>

class Input : public HelperComponent{
	Transform* _transform = 0;
	float _speed = 0.01f;

public:
	void load(){
		_transform = _getComponent<Transform>();
	}

	void update(long dt){
		int mouseRX, mouseRY;

		SDL_GetRelativeMouseState(&mouseRX, &mouseRY);

		// FPS controls here

		const Uint8* keyDown = SDL_GetKeyboardState(0);

		if (keyDown[SDL_SCANCODE_A])
			_transform->translate(Vector3f(_speed, 0.f, 0.f));

		if (keyDown[SDL_SCANCODE_D])
			_transform->translate(Vector3f(-_speed, 0.f, 0.f));

		if (keyDown[SDL_SCANCODE_W])
			_transform->translate(Vector3f(0.f, 0.f, _speed));

		if (keyDown[SDL_SCANCODE_S])
			_transform->translate(Vector3f(0.f, 0.f, -_speed));
	}

	Component* clone(){
		return new Input;
	}
};