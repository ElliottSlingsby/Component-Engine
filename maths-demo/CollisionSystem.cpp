#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem() : System(&typeid(Collider)){

}

void CollisionSystem::registerComponent(Component* component){
	_colliders.insert(static_cast<Collider*>(component));
}

void CollisionSystem::unregisterComponent(Component* component){
	_colliders.erase(static_cast<Collider*>(component));
}

void CollisionSystem::update(double dt){
	// Stupid-style collision detection
	for (ColliderSet::iterator x = _colliders.begin(); x != _colliders.end(); x++){
		if (!(*x)->owner()->loaded())
			continue;

		for (ColliderSet::iterator y = _colliders.begin(); y != _colliders.end(); y++){
			if (!(*y)->owner()->loaded())
				continue;

			if ((*x) != (*y) && (*x)->isCollidingSystem(*y))
				(*x)->owner()->invoke(&Component::onCollision, (*y)->id());
		}
	}
};

void CollisionSystem::lateUpdate(double dt){

}