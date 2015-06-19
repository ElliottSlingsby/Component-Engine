#pragma once

#include "Base.hpp"
#include "Math\Vector3.hpp"

class Transform : public Component{
	Vector3f _position;
	Vector3f _euler;

public:
	Transform(){
		_position = Vector3f(0.f, 0.f, 0.f);
		_euler = Vector3f(0.f, 0.f, 0.f);
	}

	Component* clone(){
		Transform* transform = new Transform();
		transform->_position = _position;
		transform->_euler = _euler;
		return transform;
	}
};