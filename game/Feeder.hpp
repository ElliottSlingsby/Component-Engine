#pragma once

#include <Entity\HelperComponent.hpp>

#include <Component\Circle2d.hpp>

typedef std::vector<glm::vec3> Vec3Vector;


class Feeder : public HelperComponent{
	Transform* _transform = 0;
	Circle2d* _circle = 0;

	Feeder* _predator = 0;
	Circle2d* _eating = 0;

	float _speed = 75.f;
	float _decay = 5.f;
	float _nutrition = 10.f;
	float _max = 200.f;
	float _death = 10.f;

	float _capacity = 100.f;

	bool _beingEaten;

	bool _active = true;

	int _lastPredator = NULL_ID;

public:
	Feeder(float decay, float nutrition, float max);
	void load();
	void update(double dt);
	void onCollision(int id);

	glm::vec3 nearestFood(Vec3Vector& vector);
	glm::vec3 nearestThreat(Vec3Vector& vector);

	bool eating();
	float capacity();
	bool active();
	Entity* beingEaten();
	float maxCapacity();
};