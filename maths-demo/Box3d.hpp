#pragma once

#include "Collider.hpp"

#include <glm\vec2.hpp>

class Box3d : public Collider{
	Transform* _transform = 0;

	// Width / Height
	glm::vec3 _size;

	// Runtime updated variables
	glm::vec3 _cornersTop[4];
	glm::vec3 _cornersBottom[4];

	// 0 - 3	= Top
	// 4 - 7	= Bottom (+4)
	glm::vec3 _corners[8];
	
	glm::vec3 _axes[3];
	
	glm::vec2 _magnitudes[6];

	// Edge values only updated on one side per onCollision
	glm::vec3 _edgeAxes[9];
	glm::vec2 _edgeMagnitudes[18];
	
	bool _testColliding = false;

	void _update();

public:
	Box3d(float width, float height, float depth);

	void load();
	void render();

	bool overlapping(const glm::vec2& first, const glm::vec2& second);

	bool isCollidingSystem(Collider* other);
	bool isColliding(Box3d* other, bool recurse = true);

	void onCollision(int id);
};