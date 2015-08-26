#pragma once

#include "Static\EntityManager.hpp"
#include "Component\Collider\Collider.hpp"
#include <set>

class Collision : public System{
	typedef std::set<Collider*> ColliderSet;
	ColliderSet _colliders;

public:
	Collision() : System(&typeid(Collider)){}
	
	void registerComponent(Component* component){
		_colliders.insert(dynamic_cast<Collider*>(component));
	}

	void unregisterComponent(Component* component){
		_colliders.erase(dynamic_cast<Collider*>(component));
	}

	void update(){
		// Stupid-style collision detection
		for (ColliderSet::iterator x = _colliders.begin(); x != _colliders.end(); x++){
			for (ColliderSet::iterator y = _colliders.begin(); y != _colliders.end(); y++){
				if ((*x) != (*y) && (*x)->isColliding(*y))
					(*x)->parent()->invoke(&Component::onCollision, (*y)->ID());
			}
		}
	};
};