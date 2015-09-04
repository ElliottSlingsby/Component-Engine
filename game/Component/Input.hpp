#pragma once

#include <Entity\HelperComponent.hpp>
#include <SDL.h>

#include "Component\Model.hpp"
#include "Component\Collider.hpp"
#include <glm\gtc\quaternion.hpp>

class Input : public HelperComponent{
	Transform* _transform = 0;

	float _speed = 20.f;
	float _sensitivity = 1.f;

public:
	Input(float speed, float sensitivity){
		_speed = speed;
		_sensitivity = sensitivity;
	}

	void load(){
		_transform = getComponent<Transform>();
	}

	void left(double dt){
		_transform->relativePush((float)(_speed * dt), glm::quat(glm::vec3(0.f, glm::radians(90.f), 0.f)));
	}

	void right(double dt){
		_transform->relativePush((float)(_speed * dt), glm::quat(glm::vec3(0.f, glm::radians(-90.f), 0.f)));
	}

	void forward(double dt){
		_transform->relativePush((float)(_speed * dt));
	}

	void back(double dt){
		_transform->relativePush((float)(_speed * dt), glm::quat(glm::vec3(0.f, glm::radians(180.f), 0.f)));
	}

	void up(double dt){
		_transform->translate(glm::vec3(0.f, -(float)(_speed * dt), 0.f));
	}

	void down(double dt){
		_transform->translate(glm::vec3(0.f, (float)(_speed * dt), 0.f));
	}

	void update(double dt){
		int mouseRX, mouseRY;

		SDL_GetRelativeMouseState(&mouseRX, &mouseRY);

		glm::quat lookX(glm::vec3(0.f, -(float)(mouseRX * _sensitivity * dt), 0.f));
		_transform->rotate(lookX);

		glm::quat lookY(glm::vec3(-(float)(mouseRY * _sensitivity * dt), 0.f, 0.f));
		_transform->relativeRotate(lookY);
		
		const Uint8* keyDown = SDL_GetKeyboardState(0);
		
		if (keyDown[SDL_SCANCODE_A]){
			left(dt);

			if (keyDown[SDL_SCANCODE_LSHIFT])
				left(dt);
		}

		if (keyDown[SDL_SCANCODE_D]){
			right(dt);

			if (keyDown[SDL_SCANCODE_LSHIFT])
				right(dt);
		}

		if (keyDown[SDL_SCANCODE_W]){
			forward(dt);

			if (keyDown[SDL_SCANCODE_LSHIFT])
				forward(dt);
		}

		if (keyDown[SDL_SCANCODE_S]){
			back(dt);

			if (keyDown[SDL_SCANCODE_LSHIFT])
				back(dt);
		}

		if (keyDown[SDL_SCANCODE_SPACE]){
			up(dt);

			if (keyDown[SDL_SCANCODE_LSHIFT])
				up(dt);
		}

		if (keyDown[SDL_SCANCODE_LCTRL]){
			down(dt);

			if (keyDown[SDL_SCANCODE_LSHIFT])
				down(dt);
		}
	}

	void setSpeed(float speed){
		_speed = speed;
	}

	void setSensitivity(float sensitivity){
		_sensitivity = sensitivity;
	}
};