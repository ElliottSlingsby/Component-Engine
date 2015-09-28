#include "Input.hpp"

#include <glm\gtc\quaternion.hpp>
#include <SDL.h>

Input::Input(float speed, float sensitivity){
	_speed = speed;
	_sensitivity = sensitivity;
}

void Input::load(){
	_transform = getComponent<Transform>();
	_velocity = getComponent<Velocity>();
}

void Input::lateLoad(){
	_follow = EntityManager::getEntity("camera")->getComponent<Follow>();
}

void Input::update(double dt){
	int mouseRX, mouseRY;

	SDL_GetRelativeMouseState(&mouseRX, &mouseRY);

	glm::quat lookX(glm::vec3(0.f, glm::radians(-(float)(mouseRX * _sensitivity)), 0.f));
	glm::quat lookY(glm::vec3(glm::radians(-(float)(mouseRY * _sensitivity)), 0.f, 0.f));

	_transform->localRotate(lookX);
	_transform->localRotate(lookY);

	const Uint8* keyDown = SDL_GetKeyboardState(0);

	if (keyDown[SDL_SCANCODE_DOWN])
		_follow->zoom((float)(100.0 * dt));

	if (keyDown[SDL_SCANCODE_UP])
		_follow->zoom((float)(-100.0 * dt));

	if (keyDown[SDL_SCANCODE_Q])
		_transform->localRotate(glm::quat(glm::vec3(0.f, 0.f, glm::radians((float)(_speed / 100.f)))));

	if (keyDown[SDL_SCANCODE_E])
		_transform->localRotate(glm::quat(glm::vec3(0.f, 0.f, glm::radians(-(float)(_speed / 100.f)))));

	if (keyDown[SDL_SCANCODE_W]){
		forward();

		if (keyDown[SDL_SCANCODE_LSHIFT])
			forward();
	}

	if (keyDown[SDL_SCANCODE_S]){
		back();

		if (keyDown[SDL_SCANCODE_LSHIFT])
			back();
	}
}

void Input::forward(){
	_velocity->localPush(glm::vec3(0.f, 0.f, _speed / 50.f));
}

void Input::back(){
	_velocity->localPush(glm::vec3(0.f, 0.f, -_speed / 50.f));
}

void Input::setSpeed(float speed){
	_speed = speed;
}

void Input::setSensitivity(float sensitivity){
	_sensitivity = sensitivity;
}