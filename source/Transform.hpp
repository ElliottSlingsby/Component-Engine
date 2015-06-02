#pragma once

#include "Component.hpp"

struct Transform : public Component{
	int x;
	int y;

	Transform(int x = 0, int y = 0){
		this->x = x;
		this->y = y;
	}

	Component* clone(){
		return new Transform(x, y);
	}
};