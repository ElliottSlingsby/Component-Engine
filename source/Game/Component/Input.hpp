#pragma once

#include <Entity\HelperComponent.hpp>
#include <SDL.h>

#include "Component\Model.hpp"
#include "Movement.hpp"
#include "Component\Collider.hpp"
#include "Component\Physics.hpp"

#include "..\Prefab\Bullet.hpp"

class Input : public HelperComponent{
	Transform* _transform = 0;
	Physics* _physics = 0;

	float _pushSpeed = 20.f;
	float _sensitivity = 0.2f; // Mouse sensitivity

	bool _fired = false;

	float _fireTimer = 0.f;

public:
	Input(float speed = 20.f){
		_pushSpeed = speed;
	}

	void load(){
		_transform = getComponent<Transform>();
		_physics = getComponent<Physics>();
	}

	void update(float dt){
		_fireTimer -= dt;

		if (_fireTimer < 0.f)
			_fireTimer = 0.f;

		int mouseRX, mouseRY;

		SDL_GetRelativeMouseState(&mouseRX, &mouseRY);

		// Rotate camera FPS style
		_physics->rotationForce(Vector3f((float)mouseRY * _sensitivity, (float)mouseRX * _sensitivity, 0.f));

		const Uint8* keyDown = SDL_GetKeyboardState(0);

		// W = forward
		if (keyDown[SDL_SCANCODE_W])
			_physics->pushForce(_pushSpeed);

		if (keyDown[SDL_SCANCODE_S])
			_physics->pushForce(-_pushSpeed / 100);

		// Left Mouse = Fire bullet
		if (SDL_GetMouseState(0, 0) & SDL_BUTTON(SDL_BUTTON_LEFT) && !_fired && !_fireTimer){
			Entity* bullet = EntityManager::createEntity<Bullet>("bullet", ID());
			bullet->invoke(&Component::load);
			_fireTimer = 0.5f;
			_fired = true;
		}
		else if (!SDL_GetMouseState(0, 0) & SDL_BUTTON(SDL_BUTTON_LEFT) && _fired){
			_fired = false;
		}		
	}

	void setSpeed(float speed){
		_pushSpeed = speed;
	}

	void setSensitivity(float sensitivity){
		_sensitivity = sensitivity;
	}
};