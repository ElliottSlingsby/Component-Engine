#pragma once

#include <Entity\HelperComponent.hpp>
#include <glm\vec2.hpp>

class Box2d : public HelperComponent{
	Transform* _transform = 0;

	glm::vec2 _size;

	glm::vec2 _corners[4];
	glm::vec2 _axes[2];
	glm::vec2 _magnitudes[4];

	bool _testColliding = false;

public:
	Box2d(float width = 0.5f, float height = 0.5f);

	void load();

	void update(double dt);

	void render();

	bool overlapping(const glm::vec2& first, const glm::vec2& second);
	bool isColliding(Box2d* other, bool recurse = true);
};