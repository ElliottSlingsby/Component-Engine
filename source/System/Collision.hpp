#pragma once

#include "Static\EntityManager.hpp"
#include "Component\Collider\Collider.hpp"
#include <set>

class Collision : public System{
	std::set<Collider*> _colliders;

public:
	Collision() : System(&typeid(Collider)){}
	
	void registerComponent(Component* component){
		_colliders.insert(dynamic_cast<Collider*>(component));
	}

	void unregisterComponent(Component* component){
		_colliders.erase(dynamic_cast<Collider*>(component));
	}

	void update(){
		// Collision goes here!
	};
};