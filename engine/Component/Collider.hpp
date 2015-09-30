#pragma once

#include <Entity\HelperComponent.hpp>

enum ColliderType{
	COLLIDER_SPHERE,
	COLLIDER_BOX
};

// Base collider
class Collider : public HelperComponent{
protected:
	Transform* _transform = 0;

	bool _inverted = false;

public:
	// Sphere or box
	const ColliderType type;

	Collider(ColliderType type, bool inverted = false);
	~Collider();

	// On collision event
	virtual bool isColliding(Collider* other) = 0;

	void load();

	// Getters
	glm::vec3 position();
};