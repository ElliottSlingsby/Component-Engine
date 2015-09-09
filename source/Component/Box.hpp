#pragma once

#include "Collider.hpp"

class Box : public Collider{
	glm::vec3 _size;
	glm::vec3 _offset;

	glm::vec3 _min();
	glm::vec3 _max();

public:
	Box(
		const glm::vec3& size, 
		bool inverted = false, 
		const glm::vec3& offset = glm::vec3(0.f, 0.f, 0.f)
	);

	// On collision event
	bool isColliding(Collider* Collider);

	// Setters
	void setSize(const glm::vec3& size);
	void setOffset(const glm::vec3& offset);
};