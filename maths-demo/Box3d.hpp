#pragma once

#include "Collider.hpp"

#include <glm\vec2.hpp>

class Box3d : public Collider{
	Transform* _transform = 0;

	// Width / Height
	glm::vec3 _size;

	// Runtime updated variables
	glm::vec3 _corners[8];
	glm::vec3 _axes[15];
	glm::vec3 _magnitudes[15];

	bool _testColliding = false;

	void _update();

public:
	Box3d(float width, float height);

	void load();
	void render();

	bool overlapping(const glm::vec2& first, const glm::vec2& second);

	bool isCollidingSystem(Collider* other);
	bool isColliding(Box3d* other, bool recurse = true);

	void onCollision(int id);
};