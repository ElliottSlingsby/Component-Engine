#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include "Identifier.hpp"

class Component : public Identifier{
public:
	Component(){}
	virtual ~Component(){};

	virtual void enable(){};
	virtual void update(long dt){};
	virtual void render(SDL_GLContext* context){};
	virtual void render(SDL_Renderer* renderer){};

	virtual Component* clone() = 0;
};