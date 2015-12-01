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
}

void Movement::update(double dt){
	if (!_player)
		return;

	Input* input = getComponent<Input>();

	if (!input)
		return;

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
}

void Movement::forward(float scalar){
	Velocity* velocity = getComponent<Velocity>();

	if (velocity)
		velocity->localPush(glm::vec3(0.f, 0.f, (-_speed / 25.f) * scalar));
}

void Movement::back(float scalar){
	Velocity* velocity = getComponent<Velocity>();

	if (velocity)
		velocity->localPush(glm::vec3(0.f, 0.f, (_speed / 25.f) * scalar));
}

void Movement::left(float scalar){
	Velocity* velocity = getComponent<Velocity>();

	if (velocity)
		velocity->localTorque(glm::quat(glm::vec3(0.f, glm::radians(_speed * 0.000002) * scalar, 0.f)));
}

void Movement::right(float scalar){
	Velocity* velocity = getComponent<Velocity>();

	if (velocity)
		velocity->localTorque(glm::quat(glm::vec3(0.f, glm::radians(-_speed * 0.000002) * scalar, 0.f)));
}

void Movement::setSpeed(float speed){
	_speed = speed;
}