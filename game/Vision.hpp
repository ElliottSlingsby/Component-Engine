#pragma once

#include <Entity\HelperComponent.hpp>
#include "Feeder.hpp"

typedef std::vector<float> FloatVector;

class Vision : public HelperComponent{
	Transform* _transform = 0;
	Feeder* _feeder = 0;

	glm::vec2 _size;
	glm::ivec2 _resolution;

	FloatVector _array;

	void _clear();
	void _plot(float x, float y, float value, bool overdraw = false);
	
public:
	Vision(glm::vec2 size, glm::vec2 resolution);

	void load();
	void update(double dt);

	unsigned int length();
	void get(FloatVector& vector);

	void print();
};