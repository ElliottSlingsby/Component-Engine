#pragma once

#include <Entity\HelperComponent.hpp>

class Collider : public HelperComponent{
public:
	enum Type{
		BOX2D,
		BOX3D,
		CIRCLE2D,
		CIRCLE3D
	};

	const Type type;

	Collider(Type type) : type(type){
		EntityManager::systemHandler().registerToSystem(this);
	}

	virtual ~Collider(){
		EntityManager::systemHandler().unregisterFromSystem(this);
	}

	virtual bool isCollidingSystem(Collider* other){
		return false;
	}
};