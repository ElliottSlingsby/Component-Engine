#pragma once

#include "Base\HelperComponent.hpp"

class Box : public HelperComponent{
	Transform* _transform = 0;

	Vector3f _size;
	Vector3f _offset;

	Vector3f _min(){
		return _transform->position() - _offset;
	}

	Vector3f _max(){
		return (_transform->position() + _size) - _offset;
	}

public:
	Box(Vector3f size, Vector3f offset = Vector3f(0.f, 0.f, 0.f)){
		_offset = _offset;
	}

	void load(){
		_transform = _getComponent<Transform>();
	}

	bool isColliding(Box* other){
		if (_min().x() >= other->_max().x()) return false;
		if (_min().y() >= other->_max().y()) return false;
		if (_min().z() >= other->_max().z()) return false;
		if (_max().x() <= other->_min().x()) return false;
		if (_max().y() <= other->_min().y()) return false;
		if (_max().z() <= other->_min().z()) return false;
		
		return true;
	}

	void setSize(Vector3f size){
		_size = size;
	}

	void setOffset(Vector3f offset){
		_offset = offset;
	}

	Component* clone(){
		return new Box(_size, _offset);
	}
};