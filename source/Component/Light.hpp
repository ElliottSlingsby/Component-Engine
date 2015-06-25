#pragma once

#include "Base\HelperComponent.hpp"
#include <stdint.h>
#include "Math\Vector4.hpp"

static const uint16_t GL_LIGHTS[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };

class Light : public HelperComponent{
	Transform* _transform = 0;
	unsigned int _light = 0;

	Vector4f _ambient;
	Vector4f _diffuse;
	Vector4f _specular;

	bool _spot = false;

	float _exponent = 0.f;
	float _cutoff = 0.f;

	float _constant = 0.f;
	float _linear = 0.f;
	float _quadratic = 0.f;
	
public:
	void load(){
		_transform = _getComponent<Transform>();

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

	void render(){
		GLfloat position[] = { _transform->glPosition().x(), _transform->glPosition().y(), _transform->glPosition().z(), 1 }; // Position
		glLightfv(GL_LIGHTS[_light], GL_POSITION, position);
	}
};