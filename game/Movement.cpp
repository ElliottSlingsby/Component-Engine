#include "Movement.hpp"

#include <glm\gtc\quaternion.hpp>
#include <SDL.h>
#include <Component\Camera.hpp>

Movement::Movement(float speed){
	_speed = speed;
}

void Movement::load(){
	_transform = getComponent<Transform>();
}

void Movement::update(double dt){
	_input = getComponent<Input>();

	if (!_input)
		return;

	_velocity = getComponent<Velocity>();

	if (_input->isDown("w")){
		forward();

		if (_input->isDown("shift"))
			forward();
	}

	if (_input->isDown("s")){
		back();

		if (_input->isDown("shift"))
			back();
	}
	
	if (_input->isDown("a"))
		left();	

	if (_input->isDown("d"))
		right();
}

void Movement::forward(){
	if (_velocity)
		_velocity->localPush(glm::vec3(0.f, 0.f, -_speed / 25.f));
}

void Movement::back(){
	if (_velocity)
		_velocity->localPush(glm::vec3(0.f, 0.f, _speed / 25.f));
}

void Movement::left(){
	if (_velocity)
		_velocity->localTorque(glm::quat(glm::vec3(0.f, glm::radians(_speed * 0.0000005), 0.f)));
}

void Movement::right(){
	if (_velocity)
		_velocity->localTorque(glm::quat(glm::vec3(0.f, glm::radians(-_speed * 0.0000005), 0.f)));
}

void Movement::setSpeed(float speed){
	_speed = speed;
}