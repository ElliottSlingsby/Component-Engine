#pragma once

#include <Entity\HelperComponent.hpp>
#include <SDL.h>

#include "Model\Model.hpp"
#include "Movement.hpp"
#include "Collider\Collider.hpp"

class Input : public HelperComponent{
	Transform* _transform = 0;
	float _speed = 20.f; // Movement speed
	float _sensitivity = 0.2f; // Mouse sensitivity

	bool _fired = false;

public:
	void load(){
		_transform = getComponent<Transform>();
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

		// S = Left
		if (keyDown[SDL_SCANCODE_A]){
			_transform->push(-_speed * dt, 0, -90);

			if (keyDown[SDL_SCANCODE_LSHIFT])
				_transform->push(-_speed * dt, 0, -90);
		}

		// D = Right
		if (keyDown[SDL_SCANCODE_D]){
			_transform->push(-_speed * dt, 0, 90);

			if (keyDown[SDL_SCANCODE_LSHIFT])
				_transform->push(-_speed * dt, 0, 90);
		}

		// Space = Rise
		if (keyDown[SDL_SCANCODE_SPACE]){
			_transform->setPosition(_transform->position() + Vector3f(0.f, -_speed * dt, 0.f));

			if (keyDown[SDL_SCANCODE_LSHIFT])
				_transform->setPosition(_transform->position() + Vector3f(0.f, -_speed * dt, 0.f));
		}

		// Control = Lower
		if (keyDown[SDL_SCANCODE_LCTRL]){
			_transform->setPosition(_transform->position() + Vector3f(0.f, _speed * dt, 0.f));

			if (keyDown[SDL_SCANCODE_LSHIFT])
				_transform->setPosition(_transform->position() + Vector3f(0.f, _speed * dt, 0.f));
		}

		// Left Mouse = Fire bullet
		if (SDL_GetMouseState(0, 0) & SDL_BUTTON(SDL_BUTTON_LEFT) && !_fired){
			Entity* bullet = EntityManager::createEntity("bullet");

			bullet->getComponent<Transform>()->setPosition(_transform->position());
			bullet->getComponent<Transform>()->setRotation(_transform->rotation());
			bullet->getComponent<Transform>()->setScale(Vector3f(0.25f, 0.25f, 0.25f));
			bullet->getComponent<Transform>()->push(-0.5f);
			bullet->addComponent(new Movement(100.f));
			bullet->addComponent(new Model("sphere.obj"));
			bullet->addComponent(new Sphere(10.f));

			bullet->invoke(&Component::load);
			//bullet->load();

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