#include "Noclip.hpp"

#include <glm\gtc\quaternion.hpp>
#include <SDL.h>

Noclip::Noclip(float speed, float sensitivity){
	_speed = speed;
	_sensitivity = sensitivity;
}

void Noclip::load(){
	_transform = getComponent<Transform>();
	_input = getComponent<Input>();
}

void Noclip::update(double dt){
	int mouseRX, mouseRY;

	SDL_GetRelativeMouseState(&mouseRX, &mouseRY);

	glm::quat lookX(glm::vec3(0.f, 0.f, glm::radians(-(float)(mouseRX * _sensitivity))));
	glm::quat lookY(glm::vec3(glm::radians((float)(mouseRY * _sensitivity)), 0.f, 0.f));

	_transform->rotate(lookX);
	_transform->localRotate(lookY);

	if (_input->isDown("a")){
		left(dt);

		if (_input->isDown("shift"))
			left(dt);
	}

	if (_input->isDown("d")){
		right(dt);

		if (_input->isDown("shift"))
			right(dt);
	}

	if (_input->isDown("w")){
		if (_input->isDown("space") || _input->isDown("ctrl"))
			globalForward(dt);
		else
			forward(dt);

		if (_input->isDown("shift")){
			if (_input->isDown("space") || _input->isDown("ctrl"))
				globalForward(dt);
			else
				forward(dt);
		}
	}

	if (_input->isDown("s")){
		if (_input->isDown("space") || _input->isDown("ctrl"))
			globalBack(dt);
		else
			back(dt);

		if (_input->isDown("shift")){
			if (_input->isDown("space") || _input->isDown("ctrl"))
				globalBack(dt);
			else
				back(dt);
		}
	}

	if (_input->isDown("space")){
		up(dt);

		if (_input->isDown("shift"))
			up(dt);
	}

	if (_input->isDown("ctrl")){
		down(dt);

		if (_input->isDown("shift"))
			down(dt);
	}
}

void Noclip::left(double dt){
	_transform->localTranslate(glm::vec3(-(float)(_speed * dt), 0, 0));
}

void Noclip::right(double dt){
	_transform->localTranslate(glm::vec3((float)(_speed * dt), 0, 0));
}

void Noclip::forward(double dt){
	_transform->localTranslate(glm::vec3(0, (float)(_speed * dt), 0));
}

void Noclip::back(double dt){
	_transform->localTranslate(glm::vec3(0, -(float)(_speed * dt), 0));
}

void Noclip::globalForward(double dt){
	float z = glm::eulerAngles(_transform->rotation()).z;

	_transform->translate(glm::vec3(0, (float)(_speed * dt), 0) * glm::inverse(glm::quat(glm::vec3(0, 0, z))));
}

void Noclip::globalBack(double dt){
	float z = glm::eulerAngles(_transform->rotation()).z;

	_transform->translate(glm::vec3(0, -(float)(_speed * dt), 0) * glm::inverse(glm::quat(glm::vec3(0, 0, z))));
}

void Noclip::up(double dt){
	_transform->translate(glm::vec3(0, 0, -(float)(_speed * dt)));
}

void Noclip::down(double dt){
	_transform->translate(glm::vec3(0, 0, (float)(_speed * dt)));
}

void Noclip::setSpeed(float speed){
	_speed = speed;
}

void Noclip::setSensitivity(float sensitivity){
	_sensitivity = sensitivity;
}