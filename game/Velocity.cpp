#include "Velocity.hpp"

Velocity::Velocity(float friction){
	_friction = friction;
}

void Velocity::load(){
	_transform = getComponent<Transform>();
}

void Velocity::update(double dt){
	_velocity *= 1.f - _friction;
	_transform->translate(_velocity);
}

void Velocity::localPush(const glm::vec3& push){
	_velocity = glm::mix(_velocity, _transform->rotation() * push, _friction);
}