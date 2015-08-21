#pragma once

#include "Collider.hpp"

class Sphere : public Collider{
	Transform* _transform = 0;

	float _radius;
	Vector3f _offset;

	Vector3f _position(){
		return _transform->position() - _offset;
	}

public:
	Sphere(float radius, Vector3f offset = Vector3f(0.f, 0.f, 0.f)){
		_radius = radius;
		_offset = _offset;
	}

	void load(){
		_transform = _getComponent<Transform>();
	}

	bool isColliding(Sphere* other){
		float distance = (_position() - other->_position()).length();
		
		if (distance <= _radius + other->_radius) return true;

		return false;
	}

	void setRadius(float radius){
		_radius = radius;
	}

	void setOffset(Vector3f offset){
		_offset = offset;
	}
};