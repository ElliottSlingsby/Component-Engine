#include "Noclip.hpp"

#include <glm\gtc\quaternion.hpp>
#include <SDL.h>

Noclip::Noclip(float speed, float sensitivity){
	_speed = speed;
	_sensitivity = sensitivity;
}

void Noclip::load(){
	_transform = getComponent<Transform>();
}

void Noclip::update(double dt){
	int mouseRX, mouseRY;

	SDL_GetRelativeMouseState(&mouseRX, &mouseRY);

	glm::quat lookX(glm::vec3(0.f, -(float)(mouseRX * _sensitivity * dt), 0.f));
	glm::quat lookY(glm::vec3(-(float)(mouseRY * _sensitivity * dt), 0.f, 0.f));

	_transform->rotate(lookX);
	_transform->localRotate(lookY);

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

void Noclip::left(double dt){
	_transform->localTranslate(glm::vec3((float)(_speed * dt), 0, 0));
}

void Noclip::right(double dt){
	_transform->localTranslate(glm::vec3(-(float)(_speed * dt), 0, 0));
}

void Noclip::forward(double dt){
	_transform->localTranslate(glm::vec3(0, 0, (float)(_speed * dt)));
}

void Noclip::back(double dt){
	_transform->localTranslate(glm::vec3(0, 0, -(float)(_speed * dt)));
}

void Noclip::up(double dt){
	_transform->translate(glm::vec3(0.f, -(float)(_speed * dt), 0.f));
}

void Noclip::down(double dt){
	_transform->translate(glm::vec3(0.f, (float)(_speed * dt), 0.f));
}

void Noclip::setSpeed(float speed){
	_speed = speed;
}

void Noclip::setSensitivity(float sensitivity){
	_sensitivity = sensitivity;
}