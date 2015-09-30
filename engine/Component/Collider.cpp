#include "Sphere.hpp"

#include <Static\DebugOutput.hpp>

Collider::Collider(ColliderType type, bool inverted) : type(type){
	EntityManager::SystemHandler().registerToSystem(this);
	_inverted = inverted;
}

Collider::~Collider(){
	EntityManager::SystemHandler().unregisterFromSystem(this);
}

glm::vec3 Collider::position(){
	return _transform->position();
}

void Collider::load(){
	_transform = getComponent<Transform>();
}