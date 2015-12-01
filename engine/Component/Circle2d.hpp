#pragma once

#include <Entity\HelperComponent.hpp>
#include <glm\vec2.hpp>

class Circle2d : public HelperComponent{
	Transform* _transform = 0;

	float _radius;

public:
	Circle2d(float radius);

	void load();
	void render();

	bool isColliding(Circle2d* other);
};