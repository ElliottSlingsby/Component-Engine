#pragma once

#include "Static\EntityManager.hpp"
#include "Collider.hpp"
#include <set>

class CollisionSystem : public System{
	typedef std::set<Collider*> ColliderSet;
	ColliderSet _colliders;

public:
	CollisionSystem();

	void registerComponent(Component* component);
	void unregisterComponent(Component* component);

	void update(double dt);
	void lateUpdate(double dt);
};