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

	//bool _spot = false;

	//float _exponent = 0.f;
	//float _cutoff = 0.f;

	//float _constant = 2.f;
	//float _linear = 1.f;
	//float _quadratic = 0.5f;
	
public:
	Light(){
		_ambient = Vector4f(0.f, 0.f, 0.f, 1.f);
		_diffuse = Vector4f(1.f, 1.f, 1.f, 1.f);
		_specular = Vector4f(1.f, 1.f, 1.f, 1.f);
	}

	void load(){
		_transform = _getComponent<Transform>();

		static unsigned int count = 0;

		if (count >= 8){
			printf("%s!\n", "Max GL lights reached");
			return;
		}

		_light = count;
		count++;

		glEnable(GL_LIGHTS[_light]);

		//glLightf(GL_LIGHTS[_light], GL_CONSTANT_ATTENUATION, _constant);
		//glLightf(GL_LIGHTS[_light], GL_LINEAR_ATTENUATION, _linear);
		//glLightf(GL_LIGHTS[_light], GL_QUADRATIC_ATTENUATION, _quadratic);
		
		GLfloat ambient[] = { _ambient.w(), _ambient.x(), _ambient.y(), _ambient.z() };
		glLightfv(GL_LIGHTS[_light], GL_AMBIENT, ambient);

		GLfloat diffuse[] = { _diffuse.w(), _diffuse.x(), _diffuse.y(), _diffuse.z() };
		glLightfv(GL_LIGHTS[_light], GL_DIFFUSE, diffuse);

		GLfloat specular[] = { _specular.w(), _specular.x(), _specular.y(), _specular.z() };
		glLightfv(GL_LIGHTS[_light], GL_SPECULAR, specular);
	}

	Component* clone(){
		return new Light;
	}

	void render(){
		GLfloat position[] = { -_transform->position().x(), _transform->position().y(), -_transform->position().z(), 1.f }; // Position
		glLightfv(GL_LIGHTS[_light], GL_POSITION, position);
	}
};