#pragma once

#include "Identifier.hpp"
#include <SDL.h>

struct Component : public Identifier{
	Component(){}
	virtual ~Component(){}

	virtual void load(){}
	virtual void enable(){}
	virtual void update(long dt){}
	virtual void render(){}

	// Pure virtual for RTTI / required
	virtual Component* clone() = 0;
};