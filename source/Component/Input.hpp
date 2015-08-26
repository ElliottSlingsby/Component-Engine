#pragma once

#include <Entity\HelperComponent.hpp>
#include <SDL.h>

#include "Model\Model.hpp"
#include "Movement.hpp"
#include "Collider\Collider.hpp"
#include "Physics.hpp"

#include "Prefab\Bullet.hpp"

class Input : public HelperComponent{
	Transform* _transform = 0;
	Physics* _physics = 0;

	float _speed = 20.f;
	float _sensitivity = 0.2f; // Mouse sensitivity

	bool _fired = false;

public:
	Input(float speed = 20.f){
		_speed = speed;
	}

	void load(){
		_transform = getComponent<Transform>();
		_physics = getComponent<Physics>();
	}

	void update(float dt){
		int mouseRX, mouseRY;

		SDL_GetRelativeMouseState(&mouseRX, &mouseRY);

		// Rotate camera FPS style
		_physics->rotationForce(Vector3f((float)mouseRY * _sensitivity, (float)mouseRX * _sensitivity, 0.f));

		const Uint8* keyDown = SDL_GetKeyboardState(0);

		// W = forward
		if (keyDown[SDL_SCANCODE_W]){
			_physics->pushForce(_speed);
		}

		if (keyDown[SDL_SCANCODE_S]){
			_physics->pushForce(-_speed / 100);
		}

		// Left Mouse = Fire bullet
		if (SDL_GetMouseState(0, 0) & SDL_BUTTON(SDL_BUTTON_LEFT) && !_fired){
			Entity* bullet = EntityManager::createEntity<Bullet>("bullet", ID());
			bullet->invoke(&Component::load);

			_fired = true;
		}
		else if (!SDL_GetMouseState(0, 0) & SDL_BUTTON(SDL_BUTTON_LEFT) && _fired){
			_fired = false;
		}		
	}

	void setSpeed(float speed){
		_speed = speed;
	}

	void setSensitivity(float sensitivity){
		_sensitivity = sensitivity;
	}
};