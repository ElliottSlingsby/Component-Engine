#pragma once

#include "Collider.hpp"

#include <glm\vec2.hpp>

class Box2d : public Collider{
	Transform* _transform = 0;

	// Width / Height
	glm::vec2 _size;

	// Runtime updated variables
	glm::vec2 _corners[4];
	glm::vec2 _axes[2];
	glm::vec2 _magnitudes[4];

	bool _testColliding = false;

public:
	Box2d(float width, float height);

	void load();
	void lateUpdate(double dt);
	void render();

	bool overlapping(const glm::vec2& first, const glm::vec2& second);

	bool isCollidingSystem(Collider* other);
	bool isColliding(Box2d* other, bool recurse = true);
};