#pragma once

#include <Entity\HelperComponent.hpp>
#include <glm\vec4.hpp>

class Light : public HelperComponent{
	Transform* _transform = 0;
	unsigned int _light = 0;

	glm::vec4 _ambient = glm::vec4(0.f, 0.f, 0.f, 1.f);
	glm::vec4 _diffuse = glm::vec4(1.f, 1.f, 1.f, 1.f);
	glm::vec4 _specular = glm::vec4(1.f, 1.f, 1.f, 1.f);
	
	bool _spot = false;

	float _cutoff = 25.f;
	float _exponent = 75.f;

	float _constant = 2.f;
	float _linear = 1.f;
	float _quadratic = 0.5f;

public:
	Light();
	~Light();

	void load();
	void render();

	// Setters
	void setSpot(bool spot);
	void setAmbient(const glm::vec4& ambient);
	void setDiffuse(const glm::vec4& diffuse);
	void setSpecular(const glm::vec4& specular);
	void setCutoff(float cutoff);
	void setExponent(float exponent);
};