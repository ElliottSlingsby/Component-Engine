#pragma once

#include "Identifier.hpp"
#include <SDL.h>

struct Component : public Identifier{
	Component(){}
	virtual ~Component(){}

	virtual void load(){} // Called once before game starts
	virtual void enable(){} // Called once when entity is enabled
	virtual void update(float dt){} // Called every frame
	virtual void render(){} // Called every frame after update

	// Pure virtual for RTTI
	// Should always be implemented to return new derived class
	virtual Component* clone() = 0;
};