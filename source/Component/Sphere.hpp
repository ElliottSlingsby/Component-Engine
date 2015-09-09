#pragma once

#include "Collider.hpp"

class Sphere : public Collider{
	float _radius;
	glm::vec3 _offset;

	glm::vec3 _position();

public:
	Sphere(
		float radius, 
		bool inverted = false, 
		const glm::vec3& offset = glm::vec3(0.f, 0.f, 0.f)
	);

	// On collision event
	bool isColliding(Collider* other);

	// Setters
	void setRadius(float radius);
	void setOffset(const glm::vec3& offset);
};