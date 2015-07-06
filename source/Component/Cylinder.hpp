#pragma once

#include "Base\HelperComponent.hpp"

class Cylinder : public HelperComponent{
	Transform* _transform = 0;

	float _radius;
	Vector3f _offset;

	Vector3f _position(){
		return _transform->position() - _offset;
	}

public:
	Cylinder(float radius, Vector3f offset = Vector3f(0.f, 0.f, 0.f)){
		_radius = radius;
		_offset = _offset;
	}

	void load(){
		_transform = _getComponent<Transform>();
	}

	bool colliding(Cylinder& other){
		Vector3f dif = _position() - other._position();
		
		if (dif.length() > _radius + other._radius)
			return true;

		return false;
	}

	void radius(float radius){
		_radius = radius;
	}

	void offset(Vector3f offset){
		_offset = offset;
	}

	Component* clone(){
		return new Cylinder(_radius, _offset);
	}
};