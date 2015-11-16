#include "Input.hpp"

#include <glm\gtc\quaternion.hpp>
#include <SDL.h>
#include <Component\Camera.hpp>

Input::Input(float speed, float sensitivity){
	_speed = speed;
	_sensitivity = sensitivity;
}

void Input::load(){
	_transform = getComponent<Transform>();
	_velocity = getComponent<Velocity>();
}

void Input::lateLoad(){
	Entity* camera = EntityManager::getEntity("camera");

	if (camera)
		_follow = camera->getComponent<Follow>();
}

void Input::update(double dt){
	const Uint8* keyDown = SDL_GetKeyboardState(0);

	if (keyDown[SDL_SCANCODE_Q])
		_transform->localRotate(glm::quat(glm::vec3(0.f, 0.f, glm::radians((float)((_speed / 200.0) * dt)))));

	if (keyDown[SDL_SCANCODE_E])
		_transform->localRotate(glm::quat(glm::vec3(0.f, 0.f, glm::radians(-(float)((_speed / 200) * dt)))));

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

	if (!_2d){
		int mouseRX, mouseRY;

		SDL_GetRelativeMouseState(&mouseRX, &mouseRY);

		glm::quat lookX(glm::vec3(0.f, glm::radians(-(float)(mouseRX * _sensitivity)), 0.f));
		glm::quat lookY(glm::vec3(glm::radians(-(float)(mouseRY * _sensitivity)), 0.f, 0.f));

		_transform->localRotate(lookX);
		_transform->localRotate(lookY);

		if (_follow && keyDown[SDL_SCANCODE_DOWN])
			_follow->zoom((float)((_speed / 500.0) * dt));

		if (_follow && keyDown[SDL_SCANCODE_UP])
			_follow->zoom((float)(-(_speed / 500.0) * dt));

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
	else{
		if (keyDown[SDL_SCANCODE_UP]){
			_zoom -= 0.01f;
			Entity* entity = EntityManager::getEntity("player");

			if (entity)
				entity->getComponent<Camera>()->setZoom(_zoom);
		}

		if (keyDown[SDL_SCANCODE_DOWN]){
			_zoom += 0.01f;
			Entity* entity = EntityManager::getEntity("player");

			if (entity)
				entity->getComponent<Camera>()->setZoom(_zoom);
		}

		if (keyDown[SDL_SCANCODE_W]){
			up(dt);

			if (keyDown[SDL_SCANCODE_LSHIFT])
				up(dt);
		}

		if (keyDown[SDL_SCANCODE_S]){
			down(dt);

			if (keyDown[SDL_SCANCODE_LSHIFT])
				down(dt);
		}
	}
}

void Input::forward(){
	if (_velocity)
		_velocity->localPush(glm::vec3(0.f, 0.f, _speed / 50.f));
}

void Input::back(){
	if (_velocity)
		_velocity->localPush(glm::vec3(0.f, 0.f, -_speed / 50.f));
}

void Input::up(double dt){
	_velocity->localPush(glm::vec3(0.f, -_speed / 50.f, 0.f));
}

void Input::down(double dt){
	_velocity->localPush(glm::vec3(0.f, _speed / 50.f, 0.f));
}

void Input::left(double dt){
	_velocity->localPush(glm::vec3(_speed / 50.f, 0.f, 0.f));
}

void Input::right(double dt){
	_velocity->localPush(glm::vec3(-_speed / 50.f, 0.f, 0.f));
}

void Input::set2d(bool mode){
	_2d = mode;
}

void Input::setSpeed(float speed){
	_speed = speed;
}

void Input::setSensitivity(float sensitivity){
	_sensitivity = sensitivity;
}