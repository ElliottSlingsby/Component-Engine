#pragma once

#include <Entity\HelperComponent.hpp>

class Physics : public HelperComponent{
	Transform* _transform = 0;

	Vector3f _rotation;
	Vector3f _rotationForce = Vector3f(0.f, 0.f, 0.f);

	float _pushForce = 0;
	float _pushFriction;

public:
	Physics(float friction){
		_pushFriction = friction;
	}

	void load(){
		_transform = getComponent<Transform>();
		_rotation = _transform->rotation();
	}

	void update(long double dt){
		_pushForce -= (float)(_pushFriction * dt);

		if (_pushForce < 0.f)
			_pushForce = 0.f;

		_transform->push((float)(_pushForce * dt));
		_transform->setRotation(_rotation);
	}

	void pushForce(float pushForce){
		_pushForce += (pushForce - _pushForce) * 0.01f;
	}

	void rotationForce(Vector3f rotationForce){
		float x = _rotationForce.x();
		x += (rotationForce.x() - x) * 0.01f;

		float y = _rotationForce.y();
		y += (rotationForce.y() - y) * 0.01f;

		float z = _rotationForce.z();
		z += (rotationForce.z() - z) * 0.01f;

		_rotationForce = Vector3f(x, y, z);
		
		_rotation += _rotationForce;
	}
};