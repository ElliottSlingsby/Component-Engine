#include "Movement.hpp"

#include <glm\gtc\quaternion.hpp>
#include <SDL.h>
#include <Component\Camera.hpp>

Movement::Movement(float speed, bool player){
	_speed = speed;
	_player = player;
}

void Movement::load(){
	_transform = getComponent<Transform>();
	_velocity = getComponent<Velocity>();
	_input = getComponent<Input>();
}

void Movement::update(double dt){
	if (!_player)
		return;

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
	
	if (_input->isDown("a")){
		turn(-1.f);

		if (_input->isDown("shift"))
			turn(-1.f);
	}

	if (_input->isDown("d")){
		turn(1.f);

		if (_input->isDown("shift"))
			turn(1.f);
	}
}

void Movement::forward(float scalar){
	if (_velocity)
		_velocity->localPush(glm::vec3(0.f, 0.f, (-_speed / 25.f) * scalar));
}

void Movement::back(float scalar){
	if (_velocity)
		_velocity->localPush(glm::vec3(0.f, 0.f, (_speed / 25.f) * scalar));
}

void Movement::left(float scalar){
	if (_velocity)
		_velocity->localTorque(glm::quat(glm::vec3(0.f, glm::radians(_speed * 0.000002) * scalar, 0.f)));
}

void Movement::right(float scalar){
	if (_velocity)
		_velocity->localTorque(glm::quat(glm::vec3(0.f, glm::radians(-_speed * 0.000002) * scalar, 0.f)));
}

void Movement::turn(float scalar){
	if (_velocity)
		_velocity->localTorque(glm::quat(glm::vec3(0.f, glm::radians(-_speed * 0.000002) * scalar, 0.f)));
}

void Movement::setSpeed(float speed){
	_speed = speed;
}