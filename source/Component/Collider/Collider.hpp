#pragma once

#include "Entity\HelperComponent.hpp"

enum ColliderType{
	COLLIDER_SPHERE,
	COLLIDER_BOX
};

class Collider : public HelperComponent{
protected:
	Transform* _transform = 0;

	bool _inverted = false;

public:
	const ColliderType type;

	Collider(ColliderType type, bool inverted = false) : type(type){
		EntityManager::registerToSystem(this);
		_inverted = inverted;
	}

	~Collider(){
		EntityManager::unregisterFromSystem(this);
	}

	Vector3f position(){
		return _transform->position();
	}

	virtual bool isColliding(Collider* other) = 0;

	void load(){
		_transform = getComponent<Transform>();
	}
};

class Sphere : public Collider{
	float _radius;
	Vector3f _offset;

	Vector3f _position(){
		return _transform->position() - _offset;
	}

public:
	Sphere(float radius, bool inverted = false, Vector3f offset = Vector3f(0.f, 0.f, 0.f)) : Collider(COLLIDER_SPHERE, inverted){
		_radius = radius;
		_offset = _offset;
	}

	bool isColliding(Collider* other);

	void setRadius(float radius){
		_radius = radius;
	}

	void setOffset(Vector3f offset){
		_offset = offset;
	}
};

class Box : public Collider{
	Vector3f _size;
	Vector3f _offset;

	Vector3f _min(){
		return _transform->position() - _offset;
	}

	Vector3f _max(){
		return (_transform->position() + _size) - _offset;
	}

public:
	Box(Vector3f size, bool inverted = false, Vector3f offset = Vector3f(0.f, 0.f, 0.f)) : Collider(COLLIDER_BOX, inverted){
		_offset = _offset;
	}
	
	bool isColliding(Collider* Collider);

	void setSize(Vector3f size){
		_size = size;
	}

	void setOffset(Vector3f offset){
		_offset = offset;
	}
};