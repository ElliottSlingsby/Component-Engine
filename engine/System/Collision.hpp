#pragma once

#include <Static\EntityManager.hpp>
#include <Component\Collider.hpp>
#include <set>

class Collision : public System{
	typedef std::set<Collider*> ColliderSet;
	ColliderSet _colliders;

public:
	Collision();
	
	void update();

	void registerComponent(Component* component);
	void unregisterComponent(Component* component);
};