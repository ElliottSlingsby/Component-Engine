#include "Spin.hpp"

Spin::Spin(float speed){
	_speed = speed;
}

void Spin::load(){
	_transform = getComponent<Transform>();
}

void Spin::update(double dt){
	_transform->localRotate(glm::quat(glm::vec3(0, 0, (float)(_speed * dt))));
}