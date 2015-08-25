#pragma once

#include "Entity\HelperComponent.hpp"
#include <stdint.h>
#include "Math\Vector4.hpp"

static const uint16_t GL_LIGHTS[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };

class Light : public HelperComponent{
	Transform* _transform = 0;
	unsigned int _light = 0;

	Vector4f _ambient = Vector4f(0.f, 0.f, 0.f, 1.f);
	Vector4f _diffuse = Vector4f(1.f, 1.f, 1.f, 1.f);
	Vector4f _specular = Vector4f(1.f, 1.f, 1.f, 1.f);
	
	bool _spot = true;

	float _cutoff = 25.f;
	float _exponent = 75.f;

	float _constant = 2.f;
	float _linear = 1.f;
	float _quadratic = 0.5f;

public:
	Light(){
		static unsigned int count = 0;

		if (count >= 8){
			printf("%s!\n", "Max GL lights reached");
			return;
		}

		_light = count;
		count++;
	}

	void load(){
		_transform = getComponent<Transform>();

		glEnable(GL_LIGHTS[_light]);

		GLfloat ambient[] = { _ambient.w(), _ambient.x(), _ambient.y(), _ambient.z() };
		glLightfv(GL_LIGHTS[_light], GL_AMBIENT, ambient);

		GLfloat diffuse[] = { _diffuse.w(), _diffuse.x(), _diffuse.y(), _diffuse.z() };
		glLightfv(GL_LIGHTS[_light], GL_DIFFUSE, diffuse);

		GLfloat specular[] = { _specular.w(), _specular.x(), _specular.y(), _specular.z() };
		glLightfv(GL_LIGHTS[_light], GL_SPECULAR, specular);

		if (_spot){
			glLightf(GL_LIGHTS[_light], GL_SPOT_CUTOFF, _cutoff);
			glLightf(GL_LIGHTS[_light], GL_SPOT_EXPONENT, _exponent);
		}

		//glLightf(GL_LIGHTS[_light], GL_CONSTANT_ATTENUATION, _constant);
		//glLightf(GL_LIGHTS[_light], GL_LINEAR_ATTENUATION, _linear);
		//glLightf(GL_LIGHTS[_light], GL_QUADRATIC_ATTENUATION, _quadratic);
	}

	void render(){
		//GLfloat rotation[] = { -_transform->lookingAt().x(), -_transform->lookingAt().y(), -_transform->lookingAt().z() }; // Rotation
		//glLightfv(GL_LIGHTS[_light], GL_SPOT_DIRECTION, rotation);

		GLfloat position[] = { -_transform->position().x(), -_transform->position().y(), -_transform->position().z(), 1.f }; // Position
		glLightfv(GL_LIGHTS[_light], GL_POSITION, position);
	}

	// Setters

	void setSpot(bool spot){
		_spot = spot;
	}

	void setAmbient(Vector4f ambient){
		_ambient = ambient;
	}

	void setDiffuse(Vector4f diffuse){
		_diffuse = diffuse;
	}

	void setSpecular(Vector4f specular){
		_specular = specular;
	}

	void setCutoff(float cutoff){
		_cutoff = cutoff;
	}

	void setExponent(float exponent){
		_exponent = exponent;
	}
};