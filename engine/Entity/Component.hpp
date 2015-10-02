#pragma once

#include "Identifier.hpp"

struct Component : public Identifier{
	Component(){}
	virtual ~Component(){}

	bool active = true;

	virtual void load(){} // Called once before game starts
	virtual void enable(){} // Called once when entity is enabled
	virtual void update(double dt){} // Called every frame
	virtual void render(){} // Called every frame after update
	virtual void lateLoad(){}
	virtual void lateUpdate(double dt){}
	virtual void preRender(){}
	virtual void onCollision(int id){}
};