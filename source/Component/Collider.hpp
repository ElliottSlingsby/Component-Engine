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

	glm::vec3 position(){
		return _transform->position();
	}

	virtual bool isColliding(Collider* other) = 0;

	void load(){
		_transform = getComponent<Transform>();
	}
};

class Sphere : public Collider{
	float _radius;
	glm::vec3 _offset;

	glm::vec3 _position(){
		return _transform->position() - _offset;
	}

public:
	Sphere(float radius, bool inverted = false, glm::vec3 offset = glm::vec3(0.f, 0.f, 0.f)) : Collider(COLLIDER_SPHERE, inverted){
		_radius = radius;
		_offset = _offset;
	}

	bool isColliding(Collider* other);

	void setRadius(float radius){
		_radius = radius;
	}

	void setOffset(glm::vec3 offset){
		_offset = offset;
	}
};

class Box : public Collider{
	glm::vec3 _size;
	glm::vec3 _offset;

	glm::vec3 _min(){
		return _transform->position() - _offset;
	}

	glm::vec3 _max(){
		return (_transform->position() + _size) - _offset;
	}

public:
	Box(glm::vec3 size, bool inverted = false, glm::vec3 offset = glm::vec3(0.f, 0.f, 0.f)) : Collider(COLLIDER_BOX, inverted){
		_offset = _offset;
	}
	
	bool isColliding(Collider* Collider);

	void setSize(glm::vec3 size){
		_size = size;
	}

	void setOffset(glm::vec3 offset){
		_offset = offset;
	}
};