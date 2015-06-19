#pragma once

#include "Base.hpp"

class Light : public Component{

public:
	Light(){

	}

	Component* clone(){
		return new Light;
	}

	void render(){

	}
};