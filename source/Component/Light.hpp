#pragma once

#include "Helper.hpp"
#include <stdint.h>

static const uint16_t GL_LIGHTS[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };

class Light : public HelperComponent{
	unsigned int _light = 0;

public:
	void load(){
		static unsigned int count = 0;

		if (count >= 8){
			printf("%s!\n", "Max GL lights reached");
			return;
		}

		_light = count;

		glEnable(GL_LIGHTS[_light]);
		count++;
	}

	Component* clone(){
		return new Light;
	}
};