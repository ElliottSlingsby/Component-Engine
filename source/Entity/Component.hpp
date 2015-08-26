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
	virtual void lateLoad(){}
	virtual void lateUpdate(){}
	virtual void onCollision(int id){}
};