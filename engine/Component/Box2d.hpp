#pragma once

#include <Entity\HelperComponent.hpp>
#include <glm\vec2.hpp>

class Box2d : public HelperComponent{
	Transform* _transform = 0;

	// Width / Height
	glm::vec2 _size;

	// Runtime updated variables
	glm::vec2 _corners[4];
	glm::vec2 _axes[2];
	glm::vec2 _magnitudes[4];

	bool _overlapping(const glm::vec2& first, const glm::vec2& second);
	void _updateValues();

public:
	Box2d(float width, float height);

	void load();
	void render();

	bool isColliding(Box2d* other, bool recurse = true);
};