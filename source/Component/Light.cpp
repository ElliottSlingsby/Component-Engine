#include "Light.hpp"

#include <GL\glew.h>
#include <Static\DebugOutput.hpp>

static const uint16_t GL_LIGHTS[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };

void Light::load(){
	_transform = getComponent<Transform>();

	glEnable(GL_LIGHTS[_light]);

	GLfloat ambient[] = { _ambient.w, _ambient.x, _ambient.y, _ambient.z };
	glLightfv(GL_LIGHTS[_light], GL_AMBIENT, ambient);

	GLfloat diffuse[] = { _diffuse.w, _diffuse.x, _diffuse.y, _diffuse.z };
	glLightfv(GL_LIGHTS[_light], GL_DIFFUSE, diffuse);

	GLfloat specular[] = { _specular.w, _specular.x, _specular.y, _specular.z };
	glLightfv(GL_LIGHTS[_light], GL_SPECULAR, specular);

	if (_spot){
		glLightf(GL_LIGHTS[_light], GL_SPOT_CUTOFF, _cutoff);
		glLightf(GL_LIGHTS[_light], GL_SPOT_EXPONENT, _exponent);
	}

	//glLightf(GL_LIGHTS[_light], GL_CONSTANT_ATTENUATION, _constant);
	//glLightf(GL_LIGHTS[_light], GL_LINEAR_ATTENUATION, _linear);
	//glLightf(GL_LIGHTS[_light], GL_QUADRATIC_ATTENUATION, _quadratic);
}

void Light::render(){
	//GLfloat rotation[] = { -_transform->lookingAt().x, -_transform->lookingAt().y, -_transform->lookingAt().z }; // Rotation
	//glLightfv(GL_LIGHTS[_light], GL_SPOT_DIRECTION, rotation);

	GLfloat position[] = { -_transform->position().x, -_transform->position().y, -_transform->position().z, 1.f }; // Position
	glLightfv(GL_LIGHTS[_light], GL_POSITION, position);
}

// Setters

void Light::setSpot(bool spot){
	_spot = spot;
}

void Light::setAmbient(const glm::vec4& ambient){
	_ambient = ambient;
}

void Light::setDiffuse(const glm::vec4& diffuse){
	_diffuse = diffuse;
}

void Light::setSpecular(const glm::vec4& specular){
	_specular = specular;
}

void Light::setCutoff(float cutoff){
	_cutoff = cutoff;
}

void Light::setExponent(float exponent){
	_exponent = exponent;
}