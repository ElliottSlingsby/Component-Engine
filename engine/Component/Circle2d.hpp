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

	void setRadius(float radius);
	float radius();

	/*void lateUpdate(double dt){
		if (EntityManager::nameBank().getName(id()) != "player")
			return;


		EntityVector computers;
		EntityVector food;

		EntityManager::getEntities("computer", computers);
		EntityManager::getEntities("food", food);

		EntityVector all;
		all.reserve(computers.size() + food.size());

		all.insert(all.end(), computers.begin(), computers.end());
		all.insert(all.end(), food.begin(), food.end());
		


		for (Entity* other : all){
			if (!other)
				return;

			Circle2d* circle = other->getComponent<Circle2d>();

			if (!circle)
				return;

			if (isColliding(circle))
				message_out(".");
		}
	}*/
};