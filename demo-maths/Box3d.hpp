#pragma once

#include "Collider.hpp"

#include <Maths\Vec2.hpp>

class Box3d : public Collider{
	Transform* _transform = 0;

	// Width / Height
	Vec3 _size;

	// Runtime updated variables
	Vec3 _cornersTop[4];
	Vec3 _cornersBottom[4];

	// 0 - 3	= Top
	// 4 - 7	= Bottom (+4)
	Vec3 _corners[8];
	
	Vec3 _axes[3];
	
	Vec2 _magnitudes[6];

	// Edge values only updated on one side per onCollision
	Vec3 _edgeAxes[9];
	Vec2 _edgeMagnitudes[18];
	
	bool _testColliding = false;

	void _update();

public:
	Box3d(float width, float height, float depth);

	void load();
	void render();

	bool overlapping(const Vec2& first, const Vec2& second);

	bool isCollidingSystem(Collider* other);
	bool isColliding(Box3d* other, bool recurse = true);

	void onCollision(int id);
};