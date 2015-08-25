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
		for (ColliderSet::iterator i = _colliders.begin(); i != _colliders.end(); i++){
			(*i)->parent()->invoke(&Component::onCollision, (*i)->ID());
		}
	};
};