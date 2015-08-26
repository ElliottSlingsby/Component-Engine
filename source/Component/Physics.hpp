#pragma once

#include <Entity\HelperComponent.hpp>

class Physics : public HelperComponent{
	Transform* _transform = 0;

	Vector3f _rotation;
	Vector3f _force = Vector3f(0.f, 0.f, 0.f);

	float _velocity = 0;
	float _friction;

public:
	Physics(float friction){
		_friction = friction;
	}

	void load(){
		_transform = getComponent<Transform>();
		_rotation = _transform->rotation();
	}

	void update(float dt){
		_velocity -= _friction;

		if (_velocity < 0.f)
			_velocity = 0.f;

		_transform->push(_velocity * dt);
		_transform->setRotation(_rotation);
	}
	
	void setVelocity(float velocity){
		_velocity = velocity;
	}

	void pushForce(float force){
		_velocity += (force - _velocity) * 0.01f;
	}

	void rotationForce(Vector3f force){
		float x = _force.x();
		x += (force.x() - x) * 0.01f;

		float y = _force.y();
		y += (force.y() - y) * 0.01f;

		float z = _force.z();
		z += (force.z() - z) * 0.01f;

		_force = Vector3f(x, y, z);
		
		_rotation += _force;
	}
};