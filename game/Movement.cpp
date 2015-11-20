#include "Movement.hpp"

#include <glm\gtc\quaternion.hpp>
#include <SDL.h>
#include <Component\Camera.hpp>
#include "Input.hpp"

Movement::Movement(float speed, float sensitivity){
	_speed = speed;
	_sensitivity = sensitivity;
}

void Movement::load(){
	_transform = getComponent<Transform>();
	_velocity = getComponent<Velocity>();
}

void Movement::lateLoad(){
	Entity* camera = EntityManager::getEntity("camera");

	if (camera)
		_follow = camera->getComponent<Follow>();
}

void Movement::update(double dt){
	if (!_2d){
		int mouseRX, mouseRY;

		SDL_GetRelativeMouseState(&mouseRX, &mouseRY);

		glm::quat lookX(glm::vec3(0.f, glm::radians(-(float)(mouseRX * _sensitivity)), 0.f));
		glm::quat lookY(glm::vec3(glm::radians(-(float)(mouseRY * _sensitivity)), 0.f, 0.f));

		_transform->localRotate(lookX);
		_transform->localRotate(lookY);
	}

	Entity* entity = EntityManager::getEntity("main");

	if (!entity)
		return;

	Input* input = entity->getComponent<Input>();

	if (!input)
		return;

	if (input->isDown("e")){
		_transform->localRotate(glm::quat(glm::vec3(0.f, glm::radians(-(float)((_speed / 512) * dt)), 0.f)));

		if (input->isDown("shift"))
			_transform->localRotate(glm::quat(glm::vec3(0.f, glm::radians(-(float)((_speed / 512) * dt)), 0.f)));
	}

	if (input->isDown("q")){
		_transform->localRotate(glm::quat(glm::vec3(0.f, glm::radians((float)((_speed / 512) * dt)), 0.f)));

		if (input->isDown("shift"))
			_transform->localRotate(glm::quat(glm::vec3(0.f, glm::radians((float)((_speed / 512) * dt)), 0.f)));
	}

	if (input->isDown("a")){
		left();

		if (input->isDown("shift"))
			left();
	}

	if (input->isDown("d")){
		right();

		if (input->isDown("shift"))
			right();
	}

	if (!_2d){
		if (_follow && input->isDown("down"))
			_follow->zoom((float)((_speed / 500.0) * dt));

		if (_follow && input->isDown("up"))
			_follow->zoom((float)(-(_speed / 500.0) * dt));

		if (input->isDown("w")){
			forward();

			if (input->isDown("shift"))
				forward();
		}

		if (input->isDown("s")){
			back();

			if (input->isDown("shift"))
				back();
		}
	}
	else{
		if (input->isDown("up")){
			up();

			if (input->isDown("shift"))
				up();
		}

		if (input->isDown("down")){
			down();

			if (input->isDown("shift"))
				down();
		}

		if (input->isDown("up")){
			_zoom *= 0.995f;

			Entity* entity = EntityManager::getEntity("player");

			if (entity){
				Camera* camera = entity->getComponent<Camera>();

				if (camera)
					camera->setZoom(_zoom);
			}
		}

		if (input->isDown("down")){
			_zoom /= 0.995f;

			Entity* entity = EntityManager::getEntity("player");

			if (entity){
				Camera* camera = entity->getComponent<Camera>();

				if (camera)
					camera->setZoom(_zoom);
			}
		}

		if (input->isDown("w")){
			forward();

			if (input->isDown("shift"))
				forward();
		}

		if (input->isDown("s")){
			back();

			if (input->isDown("shift"))
				back();
		}
	}
}

void Movement::forward(){
	if (_velocity)
		_velocity->localPush(glm::vec3(0.f, 0.f, -_speed / 50.f));
}

void Movement::back(){
	if (_velocity)
		_velocity->localPush(glm::vec3(0.f, 0.f, _speed / 50.f));
}

void Movement::up(){
	if (_velocity)
		_velocity->localPush(glm::vec3(0.f, _speed / 50.f, 0.f));
}

void Movement::down(){
	if (_velocity)
		_velocity->localPush(glm::vec3(0.f, -_speed / 50.f, 0.f));
}

void Movement::left(){
	if (_velocity)
		_velocity->localPush(glm::vec3(-_speed / 50.f, 0.f, 0.f));
}

void Movement::right(){
	if (_velocity)
		_velocity->localPush(glm::vec3(_speed / 50.f, 0.f, 0.f));
}

void Movement::set2d(bool mode){
	_2d = mode;
}

void Movement::setSpeed(float speed){
	_speed = speed;
}

void Movement::setSensitivity(float sensitivity){
	_sensitivity = sensitivity;
}