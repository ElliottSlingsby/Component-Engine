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

	void lateUpdate(double dt){
		if (EntityManager::nameBank().getName(id()) != "player")
			return;

		Entity* other = EntityManager::getEntity("circle");

		if (!other)
			return;

		Circle2d* circle = other->getComponent<Circle2d>();

		if (!circle)
			return;

		if (isColliding(circle))
			message_out(".");
	}
};