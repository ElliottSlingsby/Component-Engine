#pragma once

#include "Collider.hpp"

#include <Maths\Vec2.hpp>

class Box2d : public Collider{
	Transform* _transform = 0;

	// Width / Height
	Vec2 _size;

	// Runtime updated variables
	Vec2 _corners[4];
	Vec2 _axes[2];
	Vec2 _magnitudes[4];

	bool _testColliding = false;

	void _update();

public:
	Box2d(float width, float height);

	void load();
	void render();

	bool overlapping(const Vec2& first, const Vec2& second);

	bool isCollidingSystem(Collider* other);
	bool isColliding(Box2d* other, bool recurse = true);

	void onCollision(int id);
};