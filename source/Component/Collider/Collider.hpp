#pragma once

#include "Entity\HelperComponent.hpp"

enum ColliderType{
	COLLIDER_SPHERE,
	COLLIDER_BOX
};

class Collider : public HelperComponent{
protected:


public:
	const ColliderType type;

	Collider(ColliderType type) : type(type){}

	virtual bool isColliding(Collider* other) = 0;
};