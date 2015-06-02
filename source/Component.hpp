#pragma once

#include "Identifier.hpp"
#include "Renderer.hpp"

class Component : public Identifier{
public:
	Component(){}
	virtual ~Component(){}

	virtual void enable(){}
	virtual void update(long dt){}
	virtual void render(Renderer* renderer){}

	// Pure virtual for RTTI / required
	virtual Component* clone() = 0;
};