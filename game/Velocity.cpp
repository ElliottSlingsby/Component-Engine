#include "Velocity.hpp"

Velocity::Velocity(float friction, float tolerance){
	_friction = friction;
	_tolerance = tolerance;
}

void Velocity::load(){
	_transform = getComponent<Transform>();
}

void Velocity::update(double dt){
	_velocity = glm::mix(_velocity, _transform->localRotation() * _push, (float)dt);

	_push = glm::vec3(0, 0, 0);

	_velocity *= (1.0 - _friction * (float)dt);

	if (glm::length(_velocity) > _tolerance)
		_transform->translate(_velocity * (float)dt);




	_torque = glm::mix(_torque, glm::quat(), (float)dt);

	_transform->localRotate(_torque);
}

void Velocity::localPush(const glm::vec3& push){
	_push += push;
}

void Velocity::localTorque(const glm::quat& torque){
	_torque *= torque;
}