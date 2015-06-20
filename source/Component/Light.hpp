#pragma once

#include "Helper.hpp"

class Light : public HelperComponent{

public:
	Light(){

	}

	Component* clone(){
		return new Light;
	}

	void render(){

	}
};