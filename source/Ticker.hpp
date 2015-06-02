#pragma once

#include "Component.hpp"

struct Ticker : public Component{
	int i = 0;

	void update(long dt){
		printf("%d, ", i);
		i++;
	}

	Component* clone(){
		return new Ticker;
	}
};