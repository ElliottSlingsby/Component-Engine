#include "Sphere.hpp"

#include <Static\DebugPrint.hpp>

Collider::Collider(ColliderType type, bool inverted) : type(type){
	EntityManager::Systems().registerToSystem(this);
	_inverted = inverted;
}

Collider::~Collider(){
	EntityManager::Systems().unregisterFromSystem(this);
}

glm::vec3 Collider::position(){
	return _transform->position();
}

void Collider::load(){
	_transform = getComponent<Transform>();
}