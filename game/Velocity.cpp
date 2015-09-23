#include "Velocity.hpp"

Velocity::Velocity(float friction, float tolerance){
	_friction = friction;
	_tolerance = tolerance;
}

void Velocity::load(){
	_transform = getComponent<Transform>();
}

void Velocity::update(double dt){
	_velocity *= 1.f - _friction;

	if (glm::length(_velocity) > _tolerance)
		_transform->translate(_velocity);
}

void Velocity::localPush(const glm::vec3& push){
	_velocity = glm::mix(_velocity, _transform->rotation() * push, _friction);
}