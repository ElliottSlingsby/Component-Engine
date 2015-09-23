#include "Collision.hpp"

Collision::Collision() : System(&typeid(Collider)){}

void Collision::update(){
	// Stupid-style collision detection
	for (ColliderSet::iterator x = _colliders.begin(); x != _colliders.end(); x++){
		for (ColliderSet::iterator y = _colliders.begin(); y != _colliders.end(); y++){
			if ((*x) != (*y) && (*x)->isColliding(*y))
				(*x)->owner()->invoke(&Component::onCollision, (*y)->ID());
		}
	}
}

void Collision::registerComponent(Component* component){
	_colliders.insert(static_cast<Collider*>(component));
}

void Collision::unregisterComponent(Component* component){
	_colliders.erase(static_cast<Collider*>(component));
}