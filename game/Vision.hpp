#pragma once

#include <Entity\HelperComponent.hpp>
#include "Feeder.hpp"

struct Vision : public HelperComponent{
	Transform* _transform = 0;
	Feeder* _feeder = 0;

	glm::vec2 _size;
	glm::ivec2 _resolution;

	std::vector<float> _array;

	void _clear();
	void _plot(float x, float y, float value);
	void _print();

public:
	Vision(glm::vec2 size, glm::vec2 resolution);

	void load();
	void update(double dt);

	unsigned int length();
	const float* begin();
};